/*237:*/
#line 5515 "cweb/weaver.w"

/*66:*/
#line 1928 "cweb/weaver.w"

#include "conf_begin.h"
#include "../../conf/conf.h"
#include "conf_end.h"
/*:66*/
#line 5516 "cweb/weaver.w"





extern int make_iso_compilers_happy;
#if W_TARGET == W_ELF
#include "window.h"
#ifdef W_MULTITHREAD
pthread_mutex_t _window_mutex;
#endif
/*240:*/
#line 5575 "cweb/weaver.w"

Display*_dpy;
/*:240*//*243:*/
#line 5611 "cweb/weaver.w"

int _screen;
/*:243*//*246:*/
#line 5634 "cweb/weaver.w"

static int depth;
/*:246*//*248:*/
#line 5653 "cweb/weaver.w"

Window _window;
/*:248*//*251:*/
#line 5726 "cweb/weaver.w"

static XSetWindowAttributes at;
/*:251*//*256:*/
#line 5837 "cweb/weaver.w"

GLXContext _context;
/*:256*//*258:*/
#line 5850 "cweb/weaver.w"

static GLXFBConfig*fbConfigs;
/*:258*/
#line 5527 "cweb/weaver.w"

void _initialize_window(void){
/*242:*/
#line 5592 "cweb/weaver.w"

_dpy= XOpenDisplay(NULL);
if(_dpy==NULL){
fprintf(stderr,
"ERROR: Couldn't connect with the X Server. Are you running a "
"graphical interface?\n");
exit(1);
}
/*:242*//*245:*/
#line 5625 "cweb/weaver.w"

_screen= DefaultScreen(_dpy);
/*:245*//*247:*/
#line 5643 "cweb/weaver.w"

depth= DisplayPlanes(_dpy,_screen);
#if W_DEBUG_LEVEL>=3
printf("WARNING (3): Color depth: %d\n",depth);
#endif
/*:247*//*250:*/
#line 5666 "cweb/weaver.w"


W.resolution_x= DisplayWidth(_dpy,_screen);
W.resolution_y= DisplayHeight(_dpy,_screen);
#if W_WIDTH >  0
W.width= W_WIDTH;
#else
W.width= W.resolution_x;
#endif
#if W_HEIGHT >  0 
W.height= W_HEIGHT;
#else
W.height= W.resolution_y;
#endif

W.x= W.width/2;
W.y= W.resolution_y-W.height/2;
{
XRRScreenConfiguration*conf= XRRGetScreenInfo(_dpy,RootWindow(_dpy,0));
W.framerate= XRRConfigCurrentRate(conf);
XRRFreeScreenConfigInfo(conf);
}
_window= XCreateSimpleWindow(_dpy,
DefaultRootWindow(_dpy),

W.x-W.width/2,
W.resolution_y-W.y-W.height/2,
W.width,
W.height,
0,0,
0);
/*:250*//*252:*/
#line 5730 "cweb/weaver.w"

{
#if W_WIDTH == 0 && W_HEIGHT == 0
at.override_redirect= True;
#endif



at.event_mask= ButtonPressMask|ButtonReleaseMask|KeyPressMask|
KeyReleaseMask|PointerMotionMask|ExposureMask|StructureNotifyMask|
FocusChangeMask;
XChangeWindowAttributes(_dpy,_window,CWOverrideRedirect,&at);
XSelectInput(_dpy,_window,StructureNotifyMask|KeyPressMask|
KeyReleaseMask|ButtonPressMask|ButtonReleaseMask|
PointerMotionMask|ExposureMask|StructureNotifyMask|
FocusChangeMask);
}
/*:252*//*253:*/
#line 5760 "cweb/weaver.w"

XMapWindow(_dpy,_window);
{
XEvent e;
XNextEvent(_dpy,&e);
while(e.type!=MapNotify){
XNextEvent(_dpy,&e);
}
}
XSetInputFocus(_dpy,_window,RevertToParent,CurrentTime);
{

int x_return,y_return;
unsigned int width_return,height_return,dummy_border,dummy_depth;
Window dummy_window;
XGetGeometry(_dpy,_window,&dummy_window,&x_return,&y_return,&width_return,
&height_return,&dummy_border,&dummy_depth);
W.width= width_return;
W.height= height_return;
W.x= x_return+W.width/2;
W.y= W.resolution_y-y_return-W.height/2;
}
#ifdef W_PROGRAM_NAME
XStoreName(_dpy,_window,W_PROGRAM_NAME);
#else
XStoreName(_dpy,_window,W_PROG);
#endif
#ifdef W_MULTITHREAD
XInitThreads();
#endif
/*:253*//*254:*/
#line 5797 "cweb/weaver.w"

{
XSizeHints*hints= XAllocSizeHints();
hints->flags= PMinSize|PMaxSize;
hints->min_width= hints->max_width= W.width;
hints->min_height= hints->max_height= W.height;
XSetWMNormalHints(_dpy,_window,hints);
XFree(hints);
}
/*:254*//*255:*/
#line 5814 "cweb/weaver.w"

{
int glx_major,glx_minor,gl_major= 0,gl_minor= 0;
Bool ret;
glGetIntegerv(GL_MAJOR_VERSION,&gl_major);
glGetIntegerv(GL_MINOR_VERSION,&gl_minor);
ret= glXQueryVersion(_dpy,&glx_major,&glx_minor);
if(!ret||((glx_major==1)&&(glx_minor<3))||glx_major<1){
fprintf(stderr,
"ERROR: GLX is version %d.%d, but should be at least 1.3.\n",
glx_major,glx_minor);
exit(1);
}
#if W_DEBUG_LEVEL >= 3
printf("WARNING (3): GLX Version: %d.%d\n",glx_major,glx_minor);
#endif
}
/*:255*//*259:*/
#line 5857 "cweb/weaver.w"

{
int return_value;
int doubleBufferAttributes[]= {
GLX_DRAWABLE_TYPE,GLX_WINDOW_BIT,
GLX_RENDER_TYPE,GLX_RGBA_BIT,
GLX_DOUBLEBUFFER,True,
GLX_RED_SIZE,1,
GLX_GREEN_SIZE,1,
GLX_BLUE_SIZE,1,
GLX_ALPHA_SIZE,1,
GLX_DEPTH_SIZE,1,
None
};
fbConfigs= glXChooseFBConfig(_dpy,_screen,doubleBufferAttributes,
&return_value);
if(fbConfigs==NULL){
fprintf(stderr,
"ERROR: Not possible to choose our minimal OpenGL configuration.\n");
exit(1);
}
}
/*:259*//*261:*/
#line 5898 "cweb/weaver.w"

{
int context_attribs[]= 
{
GLX_CONTEXT_MAJOR_VERSION_ARB,2,
GLX_CONTEXT_MINOR_VERSION_ARB,0,
None
};
glXCreateContextAttribsARBProc glXCreateContextAttribsARB= 0;
{

const char*glxExts= glXQueryExtensionsString(_dpy,_screen);
if(strstr(glxExts,"GLX_ARB_create_context")==NULL){
fprintf(stderr,"ERROR: Can't create an OpenGL 2.0 ES context.\n");
exit(1);
}
}


glXCreateContextAttribsARB= (glXCreateContextAttribsARBProc)
glXGetProcAddressARB((const GLubyte*)"glXCreateContextAttribsARB");
_context= glXCreateContextAttribsARB(_dpy,*fbConfigs,NULL,GL_TRUE,
context_attribs);
if(_context==NULL){
fprintf(stderr,"ERROR: Couldn't create an OpenGL 2.0 ES context.\n");
exit(1);
}





glXMakeCurrent(_dpy,_window,_context);
}
/*:261*/
#line 5529 "cweb/weaver.w"

}
void _finalize_window(void){
/*262:*/
#line 5941 "cweb/weaver.w"

glXMakeCurrent(_dpy,None,NULL);
glXDestroyContext(_dpy,_context);
XDestroyWindow(_dpy,_window);
XCloseDisplay(_dpy);
/*:262*/
#line 5532 "cweb/weaver.w"

}
/*273:*/
#line 6152 "cweb/weaver.w"

void _Wresize_window(int width,int height){
int old_width,old_height;
#ifdef W_MULTITHREAD
pthread_mutex_lock(&_window_mutex);
#endif
XResizeWindow(_dpy,_window,width,height);
old_width= W.width;
old_height= W.height;
W.width= width;
W.height= height;
glViewport(0,0,W.width,W.height);
/*458:*/
#line 9977 "cweb/weaver.w"

_update_interface_screen_size();
/*:458*//*500:*/
#line 11054 "cweb/weaver.w"

{


int i,j;


float new_width,new_height;
for(i= 0;i<W_MAX_SUBLOOP;i++)
for(j= 0;j<W_MAX_INTERFACES;j++){
if(_interfaces[i][j].type==W_NONE)continue;
W.move_interface(&_interfaces[i][j],
_interfaces[i][j].x*
((float)width)/((float)old_width),
_interfaces[i][j].y*
((float)height)/((float)old_height));
new_width= _interfaces[i][j].width*
((float)width/(float)old_width);
new_height= _interfaces[i][j].height*
((float)height/(float)old_height);
W.resize_interface(&_interfaces[i][j],new_width,new_height);
}
}
/*:500*/
#line 6164 "cweb/weaver.w"

#ifdef W_MULTITHREAD
pthread_mutex_unlock(&_window_mutex);
#endif
}
/*:273*//*279:*/
#line 6221 "cweb/weaver.w"

void _Wmove_window(int x,int y){
#ifdef W_MULTITHREAD
pthread_mutex_lock(&_window_mutex);
#endif
XMoveWindow(_dpy,_window,x-W.width/2,W.resolution_y-y-W.height/2);
W.x= x;
W.y= y;
#ifdef W_MULTITHREAD
pthread_mutex_unlock(&_window_mutex);
#endif
}
/*:279*/
#line 5534 "cweb/weaver.w"

#endif
/*:237*/
