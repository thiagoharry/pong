/*215:*/
#line 5070 "cweb/weaver.w"

/*66:*/
#line 1910 "cweb/weaver.w"

#include "conf_begin.h"
#include "../../conf/conf.h"
#include "conf_end.h"
/*:66*/
#line 5071 "cweb/weaver.w"





extern int make_iso_compilers_happy;
#if W_TARGET == W_ELF
#include "window.h"
#ifdef W_MULTITHREAD
pthread_mutex_t _window_mutex;
#endif
/*218:*/
#line 5130 "cweb/weaver.w"

Display*_dpy;
/*:218*//*221:*/
#line 5166 "cweb/weaver.w"

static int screen;
/*:221*//*223:*/
#line 5182 "cweb/weaver.w"

static int depth;
/*:223*//*225:*/
#line 5201 "cweb/weaver.w"

Window _window;
/*:225*//*228:*/
#line 5274 "cweb/weaver.w"

static XSetWindowAttributes at;
/*:228*//*232:*/
#line 5364 "cweb/weaver.w"

static GLXContext context;
/*:232*//*233:*/
#line 5370 "cweb/weaver.w"

static GLXFBConfig*fbConfigs;
/*:233*/
#line 5082 "cweb/weaver.w"

void _initialize_window(void){
/*220:*/
#line 5147 "cweb/weaver.w"

_dpy= XOpenDisplay(NULL);
if(_dpy==NULL){
fprintf(stderr,
"ERROR: Couldn't connect with the X Server. Are you running a "
"graphical interface?\n");
exit(1);
}
/*:220*//*222:*/
#line 5173 "cweb/weaver.w"

screen= DefaultScreen(_dpy);
/*:222*//*224:*/
#line 5191 "cweb/weaver.w"

depth= DisplayPlanes(_dpy,screen);
#if W_DEBUG_LEVEL>=3
printf("WARNING (3): Color depth: %d\n",depth);
#endif
/*:224*//*227:*/
#line 5214 "cweb/weaver.w"


W.resolution_x= DisplayWidth(_dpy,screen);
W.resolution_y= DisplayHeight(_dpy,screen);
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
/*:227*//*229:*/
#line 5278 "cweb/weaver.w"

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
/*:229*//*230:*/
#line 5308 "cweb/weaver.w"

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
/*:230*//*231:*/
#line 5346 "cweb/weaver.w"

{
int glx_major,glx_minor;
Bool ret;
ret= glXQueryVersion(_dpy,&glx_major,&glx_minor);
if(!ret||((glx_major==1)&&(glx_minor<3))||glx_major<1){
fprintf(stderr,
"ERROR: GLX is version %d.%d, but should be at least 1.3.\n",
glx_major,glx_minor);
exit(1);
}
}
/*:231*//*234:*/
#line 5377 "cweb/weaver.w"

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
fbConfigs= glXChooseFBConfig(_dpy,screen,doubleBufferAttributes,
&return_value);
if(fbConfigs==NULL){
fprintf(stderr,
"ERROR: Not possible to choose our minimal OpenGL configuration.\n");
exit(1);
}
}
/*:234*//*236:*/
#line 5418 "cweb/weaver.w"

{
int context_attribs[]= 
{
GLX_CONTEXT_MAJOR_VERSION_ARB,3,
GLX_CONTEXT_MINOR_VERSION_ARB,3,
None
};
glXCreateContextAttribsARBProc glXCreateContextAttribsARB= 0;
{

const char*glxExts= glXQueryExtensionsString(_dpy,screen);
if(strstr(glxExts,"GLX_ARB_create_context")==NULL){
fprintf(stderr,"ERROR: Can't create an OpenGL 3.0 context.\n");
exit(1);
}
}


glXCreateContextAttribsARB= (glXCreateContextAttribsARBProc)
glXGetProcAddressARB((const GLubyte*)"glXCreateContextAttribsARB");
context= glXCreateContextAttribsARB(_dpy,*fbConfigs,NULL,GL_TRUE,
context_attribs);
if(context==NULL){
fprintf(stderr,"ERROR: Couldn't create an OpenGL 3.0 context.\n");
exit(1);
}





glXMakeCurrent(_dpy,_window,context);
}
/*:236*/
#line 5084 "cweb/weaver.w"

}
void _finalize_window(void){
/*237:*/
#line 5461 "cweb/weaver.w"

glXMakeCurrent(_dpy,None,NULL);
glXDestroyContext(_dpy,context);
XDestroyWindow(_dpy,_window);
XCloseDisplay(_dpy);
/*:237*/
#line 5087 "cweb/weaver.w"

}
/*248:*/
#line 5666 "cweb/weaver.w"

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
/*433:*/
#line 9464 "cweb/weaver.w"

_update_interface_screen_size();
/*:433*//*475:*/
#line 10517 "cweb/weaver.w"

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
if(_interfaces[i][j].stretch_x)
new_width= _interfaces[i][j].width*
((float)width/(float)old_width);
else new_width= _interfaces[i][j].width;
if(_interfaces[i][j].stretch_y)
new_height= _interfaces[i][j].height*
((float)height/(float)old_height);
else new_height= _interfaces[i][j].height;
W.resize_interface(&_interfaces[i][j],new_width,new_height);
}
}
/*:475*/
#line 5678 "cweb/weaver.w"

#ifdef W_MULTITHREAD
pthread_mutex_unlock(&_window_mutex);
#endif
}
/*:248*//*254:*/
#line 5735 "cweb/weaver.w"

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
/*:254*/
#line 5089 "cweb/weaver.w"

#endif
/*:215*/
