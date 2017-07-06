/*72:*/
#line 2019 "cweb/weaver.w"

#include "weaver.h"
/*76:*/
#line 2080 "cweb/weaver.w"

struct _weaver_struct W;
/*:76*//*82:*/
#line 2148 "cweb/weaver.w"

unsigned long _update_time(void){
int nsec;
unsigned long result;
struct timeval _current_time;
gettimeofday(&_current_time,NULL);

if(_current_time.tv_usec<_last_time.tv_usec){
nsec= (_last_time.tv_usec-_current_time.tv_usec)/1000000+1;
_last_time.tv_usec-= 1000000*nsec;
_last_time.tv_sec+= nsec;
}
if(_current_time.tv_usec-_last_time.tv_usec> 1000000){
nsec= (_current_time.tv_usec-_last_time.tv_usec)/1000000;
_last_time.tv_usec+= 1000000*nsec;
_last_time.tv_sec-= nsec;
}
if(_current_time.tv_sec<_last_time.tv_sec){

result= (_current_time.tv_sec-_last_time.tv_sec)*(-1000000);
result+= (_current_time.tv_usec-_last_time.tv_usec);
}
else{
result= (_current_time.tv_sec-_last_time.tv_sec)*1000000;
result+= (_current_time.tv_usec-_last_time.tv_usec);
}
_last_time.tv_sec= _current_time.tv_sec;
_last_time.tv_usec= _current_time.tv_usec;
return result;
}
/*:82*//*172:*/
#line 4182 "cweb/weaver.w"

void Wloop(void(*f)(void)){
if(_first_loop)
_first_loop= false;
else{
#if W_TARGET == W_WEB
emscripten_cancel_main_loop();
#endif
Wtrash();
}
Wbreakpoint();
_loop_begin= 1;
/*180:*/
#line 4344 "cweb/weaver.w"

_lag= 0;
/*:180*//*287:*/
#line 6438 "cweb/weaver.w"

W.flush_input();
/*:287*//*354:*/
#line 7971 "cweb/weaver.w"

#if W_TARGET == W_ELF
W.reload_all_plugins();
#endif
/*:354*/
#line 4194 "cweb/weaver.w"

/*365:*/
#line 8123 "cweb/weaver.w"

{
int i;
#ifdef W_MULTITHREAD
pthread_mutex_lock(&_scheduler_mutex);
#endif
for(i= 0;i<W_MAX_SCHEDULING;i++)
_scheduled_functions[_number_of_loops][i].f= NULL;
#ifdef W_MULTITHREAD
pthread_mutex_unlock(&_scheduler_mutex);
#endif
}
/*:365*//*396:*/
#line 8712 "cweb/weaver.w"

_flush_interfaces();
/*:396*//*468:*/
#line 10398 "cweb/weaver.w"

_clean_interface_queue();
/*:468*//*541:*/
#line 11568 "cweb/weaver.w"

while(W.pending_files){
#if W_TARGET == W_ELF
struct timespec tim;

tim.tv_sec= 0;
tim.tv_nsec= 100000000L;
nanosleep(&tim,NULL);
#else
emscripten_sleep(1);
#endif
}
/*:541*/
#line 4195 "cweb/weaver.w"

_loop_stack[_number_of_loops]= f;
_running_loop= true;
_update_time();
#if W_TARGET == W_WEB
while(1)
emscripten_set_main_loop(f,0,1);
#else
while(1)
f();
#endif
}
/*:172*//*174:*/
#line 4220 "cweb/weaver.w"

void _exit_loop(void){
#if W_DEBUG_LEVEL >= 1
if(_first_loop){
fprintf(stderr,"ERROR (1): Using Wexit_loop outside a game loop.\n");
Wexit();
}
#endif
Wtrash();
if(_number_of_loops==0)
Wexit();
else{
/*366:*/
#line 8141 "cweb/weaver.w"

{
int i;
#ifdef W_MULTITHREAD
pthread_mutex_lock(&_scheduler_mutex);
#endif
for(i= 0;i<W_MAX_SCHEDULING;i++)
_scheduled_functions[_number_of_loops][i].f= NULL;
#ifdef W_MULTITHREAD
pthread_mutex_unlock(&_scheduler_mutex);
#endif
}
/*:366*//*397:*/
#line 8719 "cweb/weaver.w"

_flush_interfaces();
/*:397*//*469:*/
#line 10405 "cweb/weaver.w"

_clean_interface_queue();
/*:469*//*542:*/
#line 11585 "cweb/weaver.w"

while(W.pending_files){
#if W_TARGET == W_ELF
struct timespec tim;

tim.tv_sec= 0;
tim.tv_nsec= 100000000L;
nanosleep(&tim,NULL);
#else
emscripten_sleep(1);
#endif
}
/*:542*/
#line 4232 "cweb/weaver.w"

_number_of_loops--;
/*180:*/
#line 4344 "cweb/weaver.w"

_lag= 0;
/*:180*//*287:*/
#line 6438 "cweb/weaver.w"

W.flush_input();
/*:287*//*354:*/
#line 7971 "cweb/weaver.w"

#if W_TARGET == W_ELF
W.reload_all_plugins();
#endif
/*:354*/
#line 4234 "cweb/weaver.w"

_running_loop= true;
_update_time();
#if W_TARGET == W_WEB
emscripten_cancel_main_loop();
while(1)
emscripten_set_main_loop(_loop_stack[_number_of_loops],0,1);
#else
while(1)
_loop_stack[_number_of_loops]();
#endif
}
}
/*:174*//*176:*/
#line 4270 "cweb/weaver.w"

void Wsubloop(void(*f)(void)){
#if W_TARGET == W_WEB
emscripten_cancel_main_loop();
#endif
Wbreakpoint();
_loop_begin= 1;
_number_of_loops++;
/*180:*/
#line 4344 "cweb/weaver.w"

_lag= 0;
/*:180*//*287:*/
#line 6438 "cweb/weaver.w"

W.flush_input();
/*:287*//*354:*/
#line 7971 "cweb/weaver.w"

#if W_TARGET == W_ELF
W.reload_all_plugins();
#endif
/*:354*/
#line 4278 "cweb/weaver.w"

#if W_DEBUG_LEVEL >= 1
if(_number_of_loops>=W_MAX_SUBLOOP){
fprintf(stderr,"Error (1): Max number of subloops achieved.\n");
fprintf(stderr,"Please, increase W_MAX_SUBLOOP in conf/conf.h.\n");
}
#endif
_loop_stack[_number_of_loops]= f;
_running_loop= true;
_update_time();
#if W_TARGET == W_WEB
while(1)
emscripten_set_main_loop(f,0,1);
#else
while(1)
f();
#endif
}
/*:176*//*268:*/
#line 5968 "cweb/weaver.w"

#if W_TARGET == W_ELF
static struct _k_translate{
unsigned original_symbol,new_symbol;
}_key_translate[100];
#endif


static unsigned _pressed_keys[20];
static unsigned _released_keys[20];

static unsigned _pressed_buttons[5];
static unsigned _released_buttons[5];
/*:268*//*273:*/
#line 6055 "cweb/weaver.w"

#if W_TARGET == W_ELF
static unsigned _translate_key(unsigned symbol){
int i;
for(i= 0;i<100;i++){
if(_key_translate[i].original_symbol==0)
return symbol%0xffff;
if(_key_translate[i].original_symbol==symbol)
return _key_translate[i].new_symbol%0xffff;
}
#if W_DEBUG_LEVEL >= 2
if(symbol>=0xffff)
fprintf(stderr,"WARNING (2): Key with unknown code pressed: %lu",
(unsigned long)symbol);
#endif
return symbol%0xffff;
}
#endif
/*:273*//*275:*/
#line 6087 "cweb/weaver.w"

int _Wkey_translate(unsigned old_value,unsigned new_value){
#if W_TARGET == W_ELF
int i;
#ifdef W_MULTITHREAD
pthread_mutex_lock(&_input_mutex);
#endif
for(i= 0;i<100;i++){
if(_key_translate[i].original_symbol==0||
_key_translate[i].original_symbol==old_value){
_key_translate[i].original_symbol= old_value;
_key_translate[i].new_symbol= new_value;
#ifdef W_MULTITHREAD
pthread_mutex_unlock(&_input_mutex);
#endif
return 1;
}
}
#ifdef W_MULTITHREAD
pthread_mutex_unlock(&_input_mutex);
#endif
#else


old_value= new_value;
new_value= old_value;
#endif
return 0;
}

void _Werase_key_translations(void){
#if W_TARGET == W_ELF
int i;
#ifdef W_MULTITHREAD
pthread_mutex_lock(&_input_mutex);
#endif
for(i= 0;i<100;i++){
_key_translate[i].original_symbol= 0;
_key_translate[i].new_symbol= 0;
}
#ifdef W_MULTITHREAD
pthread_mutex_unlock(&_input_mutex);
#endif
#endif
}
/*:275*//*284:*/
#line 6401 "cweb/weaver.w"

void _Wflush_input(void){
#ifdef W_MULTITHREAD
pthread_mutex_lock(&_input_mutex);
#endif
{

int i,key;
for(i= 0;i<20;i++){
key= _pressed_keys[i];
_pressed_keys[i]= 0;
W.keyboard[key]= 0;
key= _released_keys[i];
_released_keys[i]= 0;
W.keyboard[key]= 0;
}
}
/*313:*/
#line 6951 "cweb/weaver.w"

{
int i;
for(i= 0;i<5;i++){
_released_buttons[i]= 0;
_pressed_buttons[i]= 0;
}
for(i= 0;i<7;i++)
W.mouse.buttons[i]= 0;
W.mouse.dx= 0;
W.mouse.dy= 0;
}
/*:313*/
#line 6418 "cweb/weaver.w"

#ifdef W_MULTITHREAD
pthread_mutex_unlock(&_input_mutex);
#endif
}
/*:284*//*307:*/
#line 6882 "cweb/weaver.w"

static int old_dx,old_dy;
/*:307*//*317:*/
#line 6983 "cweb/weaver.w"

#if W_TARGET == W_ELF
void _Whide_cursor(void){
Colormap cmap;
Cursor no_ptr;
XColor black,dummy;
static char bm_no_data[]= {0,0,0,0,0,0,0,0};
Pixmap bm_no;
cmap= DefaultColormap(_dpy,DefaultScreen(_dpy));
XAllocNamedColor(_dpy,cmap,"black",&black,&dummy);
bm_no= XCreateBitmapFromData(_dpy,_window,bm_no_data,8,8);
no_ptr= XCreatePixmapCursor(_dpy,bm_no,bm_no,&black,&black,0,0);
XDefineCursor(_dpy,_window,no_ptr);
XFreeCursor(_dpy,no_ptr);
if(bm_no!=None)
XFreePixmap(_dpy,bm_no);
XFreeColors(_dpy,cmap,&black.pixel,1,0);
_using_original_cursor= false;
}
#endif
/*:317*//*318:*/
#line 7029 "cweb/weaver.w"

#if W_TARGET == W_WEB
void _Whide_cursor(void){
SDL_ShowCursor(0);
emscripten_hide_mouse();
_using_original_cursor= false;
}
#endif
/*:318*//*369:*/
#line 8215 "cweb/weaver.w"

void _run_periodically(void(*f)(void),float t){
int i;
unsigned long period= (unsigned long)(t*1000000);
#ifdef W_MULTITHREAD
pthread_mutex_lock(&_scheduler_mutex);
#endif
for(i= 0;i<W_MAX_SCHEDULING;i++){
if(_scheduled_functions[_number_of_loops][i].f==NULL||
_scheduled_functions[_number_of_loops][i].f==f){
_scheduled_functions[_number_of_loops][i].f= f;
_scheduled_functions[_number_of_loops][i].period= period;
_scheduled_functions[_number_of_loops][i].periodic= true;
_scheduled_functions[_number_of_loops][i].last_execution= W.t;
break;
}
}
#ifdef W_MULTITHREAD
pthread_mutex_unlock(&_scheduler_mutex);
#endif
if(i==W_MAX_SCHEDULING){
fprintf(stderr,"ERROR (1): Can't schedule more functions.");
fprintf(stderr,"Please, define W_MAX_SCHEDULING in conf/conf.h "
"with a value bigger than the current %d.\n",
W_MAX_SCHEDULING);
}
}
/*:369*//*370:*/
#line 8248 "cweb/weaver.w"

void _run_futurelly(void(*f)(void),float t){
int i;
unsigned long period= (unsigned long)(t*1000000);
#ifdef W_MULTITHREAD
pthread_mutex_lock(&_scheduler_mutex);
#endif
for(i= 0;i<W_MAX_SCHEDULING;i++){
if(_scheduled_functions[_number_of_loops][i].f==NULL||
_scheduled_functions[_number_of_loops][i].f==f){
_scheduled_functions[_number_of_loops][i].f= f;
_scheduled_functions[_number_of_loops][i].period= period;
_scheduled_functions[_number_of_loops][i].periodic= false;
_scheduled_functions[_number_of_loops][i].last_execution= W.t;
break;
}
}
#ifdef W_MULTITHREAD
pthread_mutex_unlock(&_scheduler_mutex);
#endif
if(i==W_MAX_SCHEDULING){
fprintf(stderr,"ERROR (1): Can't schedule more functions.");
fprintf(stderr,"Please, define W_MAX_SCHEDULING in conf/conf.h "
"with a value bigger than the current %d.\n",
W_MAX_SCHEDULING);
}
}
/*:370*//*371:*/
#line 8281 "cweb/weaver.w"

void _cancel(void(*f)(void)){
int i;
#ifdef W_MULTITHREAD
pthread_mutex_lock(&_scheduler_mutex);
#endif
for(i= 0;i<W_MAX_SCHEDULING;i++){
if(_scheduled_functions[_number_of_loops][i].f==f){
for(;i<W_MAX_SCHEDULING-1;i++){
_scheduled_functions[_number_of_loops][i].f= 
_scheduled_functions[_number_of_loops][i+1].f;
_scheduled_functions[_number_of_loops][i].period= 
_scheduled_functions[_number_of_loops][i+1].period;
_scheduled_functions[_number_of_loops][i].last_execution= 
_scheduled_functions[_number_of_loops][i+1].last_execution;
}
_scheduled_functions[_number_of_loops][i].f= NULL;
return;
}
}
#ifdef W_MULTITHREAD
pthread_mutex_unlock(&_scheduler_mutex);
#endif
}
/*:371*//*372:*/
#line 8313 "cweb/weaver.w"

float _period(void(*f)(void)){
int i;
float result= -1.0;
#ifdef W_MULTITHREAD
pthread_mutex_lock(&_scheduler_mutex);
#endif
for(i= 0;i<W_MAX_SCHEDULING;i++)
if(_scheduled_functions[_number_of_loops][i].f==f){
if(_scheduled_functions[_number_of_loops][i].periodic==true)
result= (float)(_scheduled_functions[_number_of_loops][i].period)/
1000000.0;
else
result= INFINITY;
}
if(result<0.0)
result= NAN;
#ifdef W_MULTITHREAD
pthread_mutex_lock(&_scheduler_mutex);
#endif
return result;
}
/*:372*/
#line 2021 "cweb/weaver.w"

void _awake_the_weaver(void){
/*80:*/
#line 2133 "cweb/weaver.w"

W.t= 0;
gettimeofday(&_last_time,NULL);
/*:80*//*86:*/
#line 2199 "cweb/weaver.w"

W.game= &_game;
/*:86*//*117:*/
#line 3065 "cweb/weaver.w"

W.create_arena= &_Wcreate_arena;
/*:117*//*125:*/
#line 3187 "cweb/weaver.w"

W.destroy_arena= &Wdestroy_arena;
/*:125*//*130:*/
#line 3315 "cweb/weaver.w"

W.alloc_arena= &_alloc;
/*:130*//*134:*/
#line 3427 "cweb/weaver.w"

W.free= &_free;
/*:134*//*140:*/
#line 3536 "cweb/weaver.w"

W.breakpoint_arena= &_new_breakpoint;
/*:140*//*144:*/
#line 3598 "cweb/weaver.w"

W.trash_arena= &Wtrash_arena;
/*:144*//*149:*/
#line 3656 "cweb/weaver.w"

_initialize_memory();
/*:149*//*154:*/
#line 3718 "cweb/weaver.w"

W.alloc= &_Walloc;
/*:154*//*159:*/
#line 3775 "cweb/weaver.w"

W.breakpoint= &_Wbreakpoint;
W.trash= &_Wtrash;
/*:159*//*171:*/
#line 4174 "cweb/weaver.w"

_first_loop= true;
_running_loop= false;
_number_of_loops= 0;
/*:171*//*179:*/
#line 4339 "cweb/weaver.w"

W.dt= 40000;
_lag= 0;
/*:179*//*192:*/
#line 4565 "cweb/weaver.w"

_initialize_numeric_functions();
/*:192*//*193:*/
#line 4571 "cweb/weaver.w"

_finalize_numeric_functions();
/*:193*//*203:*/
#line 4828 "cweb/weaver.w"

W.random= &_random;
/*:203*//*216:*/
#line 5098 "cweb/weaver.w"

#ifdef W_MULTITHREAD
if(pthread_mutex_init(&_window_mutex,NULL)!=0){
perror(NULL);
exit(1);
}
#endif
#if W_TARGET == W_ELF
_initialize_window();
#endif
/*:216*//*242:*/
#line 5577 "cweb/weaver.w"

#if W_TARGET == W_WEB
_initialize_canvas();
#endif
/*:242*//*252:*/
#line 5722 "cweb/weaver.w"

W.resize_window= &_Wresize_window;
/*:252*//*258:*/
#line 5768 "cweb/weaver.w"

W.move_window= &_Wmove_window;
/*:258*//*262:*/
#line 5811 "cweb/weaver.w"


glClearColor(W_DEFAULT_COLOR,1.0f);

glEnable(GL_DEPTH_TEST);

glEnable(GL_CULL_FACE);

glEnable(GL_BLEND);
glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
/*:262*//*270:*/
#line 5993 "cweb/weaver.w"

{
int i;
for(i= 0;i<0xffff;i++)
W.keyboard[i]= 0;
#if W_TARGET == W_ELF
for(i= 0;i<100;i++){
_key_translate[i].original_symbol= 0;
_key_translate[i].new_symbol= 0;
}
#endif
for(i= 0;i<20;i++){
_pressed_keys[i]= 0;
_released_keys[i]= 0;
}
#ifdef W_MULTITHREAD
if(pthread_mutex_init(&_input_mutex,NULL)!=0){
perror(NULL);
exit(1);
}
#endif
}
/*:270*//*277:*/
#line 6142 "cweb/weaver.w"

W.key_translate= &_Wkey_translate;
W.erase_key_translations= &_Werase_key_translations;
/*:277*//*286:*/
#line 6431 "cweb/weaver.w"

W.flush_input= &_Wflush_input;
/*:286*//*298:*/
#line 6672 "cweb/weaver.w"

{
int i;
for(i= 0;i<5;i++)
W.mouse.buttons[i]= 0;
for(i= 0;i<5;i++){
_pressed_buttons[i]= 0;
_released_buttons[i]= 0;
}
}
/*:298*//*306:*/
#line 6851 "cweb/weaver.w"

#if W_TARGET == W_ELF
{
Window root_return,child_return;
int root_x_return,root_y_return,win_x_return,win_y_return;
unsigned mask_return;
XQueryPointer(_dpy,_window,&root_return,&child_return,&root_x_return,
&root_y_return,&win_x_return,&win_y_return,&mask_return);




W.mouse.x= root_x_return;
W.mouse.y= W.height-1-root_y_return;
}
#endif
#if W_TARGET == W_WEB
SDL_GetMouseState(&(W.mouse.x),&(W.mouse.y));
W.mouse.y= W.height-1-W.mouse.y;
#endif
W.mouse.ddx= W.mouse.ddy= W.mouse.dx= W.mouse.dy= 0;
/*:306*//*308:*/
#line 6886 "cweb/weaver.w"

old_dx= old_dy= 0;
/*:308*//*316:*/
#line 6979 "cweb/weaver.w"

_using_original_cursor= true;
/*:316*//*320:*/
#line 7045 "cweb/weaver.w"

W.hide_cursor= &_Whide_cursor;
/*:320*//*338:*/
#line 7626 "cweb/weaver.w"

W.reload_plugin= &_reload_plugin;
/*:338*//*349:*/
#line 7853 "cweb/weaver.w"

#if W_TARGET == W_ELF
W.get_plugin= &_Wget_plugin;
#endif
/*:349*//*353:*/
#line 7962 "cweb/weaver.w"

#if W_TARGET == W_ELF
W.reload_all_plugins= &_reload_all_plugins;
#endif
/*:353*//*363:*/
#line 8094 "cweb/weaver.w"

{
#ifdef W_MULTITHREAD
if(pthread_mutex_init(&_scheduler_mutex,NULL)!=0){
perror(NULL);
exit(1);
}
#endif
int i,j;
for(i= 0;i<W_MAX_SUBLOOP;i++)
for(j= 0;j<W_MAX_SCHEDULING;j++)
_scheduled_functions[i][j].f= NULL;
}
/*:363*//*374:*/
#line 8347 "cweb/weaver.w"

W.run_periodically= &_run_periodically;
W.run_futurelly= &_run_futurelly;
W.cancel= &_cancel;
W.period= &_period;
/*:374*//*379:*/
#line 8434 "cweb/weaver.w"

#if W_TARGET == W_ELF
W.enable_plugin= &_Wenable_plugin;
W.disable_plugin= &_Wdisable_plugin;
W.is_plugin_enabled= &_Wis_enabled;
#endif
/*:379*//*383:*/
#line 8483 "cweb/weaver.w"

#if W_TARGET == W_ELF
W.get_plugin_data= &_Wget_plugin_data;
W.set_plugin_data= &_Wset_plugin_data;
#endif
/*:383*//*392:*/
#line 8655 "cweb/weaver.w"

{
int i,j;
for(i= 0;i<W_MAX_SUBLOOP;i++)
for(j= 0;j<W_MAX_INTERFACES;j++)
_interfaces[i][j].type= W_NONE;
#ifdef W_MULTITHREAD
if(pthread_mutex_init(&_interface_mutex,NULL)!=0){
perror("Initializing interface mutex:");
exit(1);
}
#endif
}
/*:392*//*398:*/
#line 8730 "cweb/weaver.w"

{
GLenum dummy;
glewExperimental= GL_TRUE;
GLenum err= glewInit();
if(err!=GLEW_OK){
fprintf(stderr,"ERROR: GLW not supported.\n");
exit(1);
}






dummy= glGetError();
glewExperimental+= dummy;
glewExperimental-= dummy;
}
/*:398*//*400:*/
#line 8763 "cweb/weaver.w"

{
_interface_vertices[0]= -0.5;
_interface_vertices[1]= -0.5;
_interface_vertices[2]= 0.0;
_interface_vertices[3]= 0.5;
_interface_vertices[4]= -0.5;
_interface_vertices[5]= 0.0;
_interface_vertices[6]= 0.5;
_interface_vertices[7]= 0.5;
_interface_vertices[8]= 0.0;
_interface_vertices[9]= -0.5;
_interface_vertices[10]= 0.5;
_interface_vertices[11]= 0.0;

glGenBuffers(1,&_interface_VBO);

glGenVertexArrays(1,&_interface_VAO);

glBindVertexArray(_interface_VAO);

glBindBuffer(GL_ARRAY_BUFFER,_interface_VBO);

glBufferData(GL_ARRAY_BUFFER,sizeof(_interface_vertices),
_interface_vertices,GL_STATIC_DRAW);

glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,(GLvoid*)0);

glEnableVertexAttribArray(0);

glBindVertexArray(0);
}
/*:400*//*405:*/
#line 8900 "cweb/weaver.w"

W.new_interface= &_new_interface;
/*:405*//*409:*/
#line 8947 "cweb/weaver.w"

W.destroy_interface= &_destroy_interface;
/*:409*//*413:*/
#line 9013 "cweb/weaver.w"

W.copy_interface= &_copy_interface;
/*:413*//*418:*/
#line 9112 "cweb/weaver.w"

W.move_interface= &_move_interface;
/*:418*//*422:*/
#line 9191 "cweb/weaver.w"

W.resize_interface= &_resize_interface;
/*:422*//*426:*/
#line 9271 "cweb/weaver.w"

W.rotate_interface= &_rotate_interface;
/*:426*//*449:*/
#line 9719 "cweb/weaver.w"

{
GLuint vertex,fragment;
vertex= _compile_vertex_shader(_vertex_interface);
fragment= _compile_fragment_shader(_fragment_interface);


_default_interface_shader.program_shader= 
_link_and_clean_shaders(vertex,fragment);
_default_interface_shader._uniform_object_color= 
glGetUniformLocation(_default_interface_shader.program_shader,
"object_color");
_default_interface_shader._uniform_model_view= 
glGetUniformLocation(_default_interface_shader.program_shader,
"model_view_matrix");
_default_interface_shader._uniform_object_size= 
glGetUniformLocation(_default_interface_shader.program_shader,
"object_size");
_default_interface_shader._uniform_integer= 
glGetUniformLocation(_default_interface_shader.program_shader,
"integer");
_default_interface_shader._uniform_time= 
glGetUniformLocation(_default_interface_shader.program_shader,
"time");
_default_interface_shader._attribute_vertex_position= 
glGetAttribLocation(_default_interface_shader.program_shader,
"vertex_position");
}
/*:449*//*453:*/
#line 9851 "cweb/weaver.w"

#if W_TARGET == W_ELF
{
int number_of_shaders= 0;
char shader_directory[256];
DIR*d;
shader_directory[0]= '\0';
#if W_DEBUG_LEVEL == 0
strcat(shader_directory,W_INSTALL_DATA);
#endif
strcat(shader_directory,"shaders/");


d= opendir(shader_directory);
if(d){
struct dirent*dir;


while((dir= readdir(d))!=NULL){
if(dir->d_name[0]=='.')continue;
if(atoi(dir->d_name)==0){
fprintf(stderr,"WARNING (0): Shader being ignored. "
"%s%s should start with number different than zero.\n",
shader_directory,dir->d_name);
continue;
}
#if (defined(__linux__) || defined(_BSD_SOURCE)) && defined(DT_DIR)
if(dir->d_type!=DT_DIR)continue;
#else
{

struct stat s;
int err;
err= stat(file,&s);
if(err==-1)continue;
if(!S_ISDIR(s.st_mode))continue;
}
#endif
number_of_shaders++;
}
}
#endif

/*:453*//*454:*/
#line 9899 "cweb/weaver.w"

#if W_TARGET == W_ELF

_shader_list= (struct _shader*)_iWalloc(sizeof(struct _shader)*
number_of_shaders);
if(_shader_list==NULL){
fprintf(stderr,"ERROR (0): Not enough memory to compile shaders. "
"Please, increase the value of W_INTERNAL_MEMORY "
"at conf/conf.h.");
exit(1);
}
{
int i;
for(i= 0;i<number_of_shaders;i++)
_shader_list[i].initialized= false;
}

#endif
/*:454*//*455:*/
#line 9925 "cweb/weaver.w"

#if W_TARGET == W_ELF

if(d)closedir(d);
d= opendir(shader_directory);
if(d){
struct dirent*dir;


while((dir= readdir(d))!=NULL){
if(dir->d_name[0]=='.')continue;
if(!isdigit(dir->d_name[0])||dir->d_name[0]=='0')
continue;
#if (defined(__linux__) || defined(_BSD_SOURCE)) && defined(DT_DIR)
if(dir->d_type!=DT_DIR)continue;
#else
{

struct stat s;
int err;
err= stat(file,&s);
if(err==-1)continue;
if(!S_ISDIR(s.st_mode))continue;
}
#endif


{
int shader_number= atoi(dir->d_name);
if(shader_number> number_of_shaders){
#if W_DEBUG_LEVEL >= 1
fprintf(stderr,"WARNING (1): Non-sequential shader "
"enumeration at %s.\n",shader_directory);
#endif
continue;
}
if(_shader_list[shader_number-1].initialized==true){
#if W_DEBUG_LEVEL >= 1
fprintf(stderr,"WARNING (1): Two shaders enumerated "
"with number %d at %s.\n",shader_number,
shader_directory);
#endif
continue;
}



{
char path[256];
strcpy(path,shader_directory);
strcat(path,dir->d_name);
path[255]= '\0';
_compile_and_insert_new_shader(path,shader_number-1);
}
}
}
}
}
#endif
/*:455*//*456:*/
#line 9991 "cweb/weaver.w"

#if W_TARGET == W_WEB
#include "../../.hidden_code/initialize_shader.c"
#endif
/*:456*//*461:*/
#line 10244 "cweb/weaver.w"

{
int i,j;
for(i= 0;i<W_MAX_SUBLOOP;i++)
for(j= 0;j<W_MAX_INTERFACES;j++)
_interface_queue[i][j]= NULL;
}
/*:461*//*478:*/
#line 10635 "cweb/weaver.w"

{


_use_non_default_render= false;


glGenFramebuffers(1,&_framebuffer);


glBindFramebuffer(GL_FRAMEBUFFER,_framebuffer);
}
/*:478*//*481:*/
#line 10666 "cweb/weaver.w"

{

glGenTextures(1,&_texture);
glBindTexture(GL_TEXTURE_2D,_texture);
glTexImage2D(
GL_TEXTURE_2D,
0,
GL_RGB,
W.width,
W.height,
0,
GL_RGB,GL_UNSIGNED_BYTE,
NULL);


glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);


glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,
GL_TEXTURE_2D,_texture,0);
}
/*:481*//*483:*/
#line 10703 "cweb/weaver.w"

{
glGenRenderbuffers(1,&_depth_stencil);
glBindRenderbuffer(GL_RENDERBUFFER,_depth_stencil);
glRenderbufferStorage(GL_RENDERBUFFER,GL_DEPTH24_STENCIL8,
W.width,W.height);

glFramebufferRenderbuffer(GL_FRAMEBUFFER,GL_DEPTH_STENCIL_ATTACHMENT,
GL_RENDERBUFFER,_depth_stencil);
glBindFramebuffer(GL_FRAMEBUFFER,0);
}
/*:483*//*490:*/
#line 10810 "cweb/weaver.w"

{
GLuint vertex,fragment;


_custom_final_shader= 0;
vertex= _compile_vertex_shader(_vertex_interface_texture);
fragment= _compile_fragment_shader(_fragment_interface_texture);

_framebuffer_shader.program_shader= 
_link_and_clean_shaders(vertex,fragment);
_framebuffer_shader._uniform_texture1= 
glGetUniformLocation(_framebuffer_shader.program_shader,
"texture1");
_framebuffer_shader._uniform_object_color= 
glGetUniformLocation(_framebuffer_shader.program_shader,
"object_color");
_framebuffer_shader._uniform_model_view= 
glGetUniformLocation(_framebuffer_shader.program_shader,
"model_view_matrix");
_framebuffer_shader._uniform_object_size= 
glGetUniformLocation(_framebuffer_shader.program_shader,
"object_size");
_framebuffer_shader._uniform_time= 
glGetUniformLocation(_framebuffer_shader.program_shader,
"time");
_framebuffer_shader._uniform_integer= 
glGetUniformLocation(_framebuffer_shader.program_shader,
"integer");
_framebuffer_shader._attribute_vertex_position= 
glGetAttribLocation(_framebuffer_shader.program_shader,
"vertex_position");





_framebuffer_matrix[0]= _framebuffer_matrix[5]= 
_framebuffer_matrix[10]= 2.0;
_framebuffer_matrix[15]= 1.0;
_framebuffer_matrix[1]= _framebuffer_matrix[2]= 
_framebuffer_matrix[3]= _framebuffer_matrix[4]= 
_framebuffer_matrix[6]= _framebuffer_matrix[7]= 
_framebuffer_matrix[8]= _framebuffer_matrix[9]= 
_framebuffer_matrix[11]= _framebuffer_matrix[12]= 
_framebuffer_matrix[13]= _framebuffer_matrix[14]= 0.0;
}
/*:490*//*495:*/
#line 11000 "cweb/weaver.w"

W.change_resolution= &_change_resolution;
/*:495*//*500:*/
#line 11034 "cweb/weaver.w"

W.change_final_shader= &_change_final_shader;
/*:500*//*502:*/
#line 11049 "cweb/weaver.w"

W.final_shader_integer= 0;
/*:502*//*515:*/
#line 11212 "cweb/weaver.w"

{
_initialize_sound();
}
/*:515*//*526:*/
#line 11344 "cweb/weaver.w"

W.select_sound_device= &_select_sound_device;
/*:526*//*530:*/
#line 11377 "cweb/weaver.w"

W.current_sound_device= &_current_sound_device;
/*:530*//*539:*/
#line 11550 "cweb/weaver.w"

W.pending_files= 0;
#ifdef W_MULTITHREAD
if(pthread_mutex_init(&(W._pending_files_mutex),NULL)!=0){
fprintf(stderr,"ERROR (0): Can't initialize mutex for file loading.\n");
exit(1);
}
#endif
/*:539*//*564:*/
#line 12158 "cweb/weaver.w"

W.new_sound= &_new_sound;
/*:564*//*568:*/
#line 12190 "cweb/weaver.w"

W.play_sound= &_play_sound;
/*:568*//*572:*/
#line 12234 "cweb/weaver.w"

W.destroy_sound= &_destroy_sound;
/*:572*//*576:*/
#line 12306 "cweb/weaver.w"

#if defined(W_MULTITHREAD) && W_TARGET == W_ELF && W_THREAD_POOL >  0
{
int i;
for(i= 0;i<W_THREAD_POOL;i++){
_file_list[i].valid_info= false;
_file_list[i]._kill_switch= false;
if(pthread_mutex_init(&(_file_list[i].mutex),NULL)!=0){
fprintf(stderr,"ERROR: Failed to create mutex for file list.\n");
exit(1);
}
if(pthread_mutex_init(&(_file_list[i].struct_mutex),NULL)!=0){
fprintf(stderr,"ERROR: Failed to create mutex for file list.\n");
exit(1);
}
if(pthread_cond_init(&(_file_list[i].condition),NULL)!=0){
fprintf(stderr,"ERROR: Failed to create condition variable for thread "
"synchronization.\n");
exit(1);
}
}

if(pthread_mutex_init(&(_file_list_count_mutex),NULL)!=0){
fprintf(stderr,"ERROR: Failed to create mutex for file list.\n");
exit(1);
}


_file_list_count= 0;
}
#endif
/*:576*//*580:*/
#line 12396 "cweb/weaver.w"

#if defined(W_MULTITHREAD) && W_TARGET == W_ELF && W_THREAD_POOL >  0
{
int i;
for(i= 0;i<W_THREAD_POOL;i++){
pthread_create(&(_thread_list[i]),NULL,&_file_list_thread,
(void*)&(_file_list[i]));
}
}
#endif
/*:580*/
#line 2023 "cweb/weaver.w"

/*342:*/
#line 7679 "cweb/weaver.w"

#if W_TARGET == W_ELF
{
int i= 0;
if(strcmp(W_PLUGIN_PATH,"")){
char*begin= W_PLUGIN_PATH,*end= W_PLUGIN_PATH;
char dir[256];
DIR*directory;
struct dirent*dp;
_max_number_of_plugins= 0;
while(*end!='\0'){
end++;
while(*end!=':'&&*end!='\0')end++;

if(end-begin> 255){
fprintf(stderr,"ERROR: Path too big in W_PLUGIN_PATH.\n");
begin= end+1;
continue;
}
strncpy(dir,begin,(size_t)(end-begin));
dir[(end-begin)]= '\0';

directory= opendir(dir);
if(directory==NULL){
#if W_DEBUG_LEVEL >= 2
fprintf(stderr,"WARNING (2): Trying to access plugin directory %s: "
"%s\n",dir,strerror(errno));
#endif


begin= end+1;
continue;
}

while((dp= readdir(directory))!=NULL){
if(dp->d_name[0]!='.'&&dp->d_type==DT_REG)
_max_number_of_plugins++;

}

begin= end+1;
}

/*343:*/
#line 7732 "cweb/weaver.w"

{
_max_number_of_plugins+= 25;
#if W_DEBUG_LEVEL >= 3
printf("WARNING (3): Supporting maximum of %d plugins.\n",
_max_number_of_plugins);
#endif
_plugins= (struct _plugin_data*)_iWalloc(sizeof(struct _plugin_data)*
(_max_number_of_plugins));
if(_plugins==NULL){
fprintf(stderr,"ERROR (0): Too many plugins. Not enough memory!\n");
Wexit();
}
for(i= 0;i<_max_number_of_plugins;i++){
_plugins[i].defined= false;
}
#ifdef W_MULTITHREAD
if(pthread_mutex_init(&_plugin_mutex,NULL)!=0){
perror("Initializing plugin mutex:");
Wexit();
}
#endif
}
/*:343*//*344:*/
#line 7761 "cweb/weaver.w"

{
begin= end= W_PLUGIN_PATH;
i= 0;
while(*end!='\0'){
end++;
while(*end!=':'&&*end!='\0')end++;

if(end-begin> 255){


begin= end+1;
continue;
}
strncpy(dir,begin,(size_t)(end-begin));
dir[(end-begin)]= '\0';

directory= opendir(dir);
if(directory==NULL){




begin= end+1;
continue;
}

while((dp= readdir(directory))!=NULL){
if(dp->d_name[0]!='.'&&dp->d_type==DT_REG){
if(strlen(dir)+1+strlen(dp->d_name)> 255){
fprintf(stderr,"Ignoring plugin with too long path: %s/%s.\n",
dir,dp->d_name);
continue;
}
if(i>=_max_number_of_plugins){
fprintf(stderr,"Ignoring plugin %s/%s, not prepared for so much "
"new plugins being added.\n",dir,dp->d_name);
continue;
}
strcat(dir,"/");
strcat(dir,dp->d_name);
_initialize_plugin(&(_plugins[i]),dir);
i++;
}
}

begin= end+1;
}
}
/*:344*/
#line 7722 "cweb/weaver.w"

}
}
#endif
/*:342*//*358:*/
#line 8021 "cweb/weaver.w"

#if W_TARGET == W_WEB
{
_max_number_of_plugins= _W_NUMBER_OF_PLUGINS;
_plugins= (struct _plugin_data*)Walloc(sizeof(struct _plugin_data)*
_max_number_of_plugins);
#include "../../.hidden_code/initialize_plugin.c"
}
#endif
/*:358*/
#line 2024 "cweb/weaver.w"

}
void _may_the_weaver_sleep(void){
/*73:*/
#line 2056 "cweb/weaver.w"


/*:73*//*150:*/
#line 3660 "cweb/weaver.w"


/*217:*/
#line 5109 "cweb/weaver.w"

#ifdef W_MULTITHREAD
if(pthread_mutex_destroy(&_window_mutex)!=0){
perror(NULL);
exit(1);
}
#endif
#if W_TARGET == W_ELF
_finalize_window();
#endif
/*:217*//*243:*/
#line 5583 "cweb/weaver.w"

#if W_TARGET == W_WEB
_finalize_canvas();
#endif
/*:243*//*345:*/
#line 7816 "cweb/weaver.w"

#if W_TARGET == W_ELF
{
int j;
for(j= 0;j<_max_number_of_plugins;j++)
if(_plugins[j].defined)
_finalize_plugin(&(_plugins[j]));
}
#endif
/*:345*//*360:*/
#line 8050 "cweb/weaver.w"

#if W_TARGET == W_WEB
{
int i;
for(i= 0;i<_max_number_of_plugins;i++)
_plugins[i]._fini_plugin(&W);
}
#endif
/*:360*//*516:*/
#line 11218 "cweb/weaver.w"

{
_finalize_sound();
}
/*:516*//*577:*/
#line 12341 "cweb/weaver.w"

#if defined(W_MULTITHREAD) && W_TARGET == W_ELF && W_THREAD_POOL >  0
{
int i;
for(i= 0;i<W_THREAD_POOL;i++){

pthread_mutex_lock(&(_file_list[i].struct_mutex));
_file_list[i]._kill_switch= true;
pthread_mutex_unlock(&(_file_list[i].struct_mutex));
pthread_cond_signal(&(_file_list[i].condition));
pthread_join(_thread_list[i],NULL);

pthread_mutex_destroy(&(_file_list[i].mutex));
pthread_mutex_destroy(&(_file_list[i].struct_mutex));
pthread_cond_destroy(&(_file_list[i].condition));
}
pthread_mutex_destroy(&(_file_list_count_mutex));
}
#endif
/*:577*/
#line 3662 "cweb/weaver.w"


_finalize_memory();
/*:150*//*271:*/
#line 6020 "cweb/weaver.w"

#ifdef W_MULTITHREAD
if(pthread_mutex_destroy(&_input_mutex)!=0){
perror(NULL);
exit(1);
}
#endif
/*:271*//*364:*/
#line 8111 "cweb/weaver.w"

#ifdef W_MULTITHREAD
pthread_mutex_destroy(&_scheduler_mutex);
#endif
/*:364*//*393:*/
#line 8673 "cweb/weaver.w"

#ifdef W_MULTITHREAD
if(pthread_mutex_destroy(&_interface_mutex)!=0)
perror("Finalizing interface mutex:");
#endif
/*:393*//*450:*/
#line 9751 "cweb/weaver.w"

glDeleteProgram(_default_interface_shader.program_shader);
/*:450*//*479:*/
#line 10649 "cweb/weaver.w"

glDeleteFramebuffers(1,&_framebuffer);
/*:479*//*484:*/
#line 10718 "cweb/weaver.w"

glDeleteTextures(1,&_texture);
glDeleteRenderbuffers(1,&_depth_stencil);
/*:484*//*540:*/
#line 11559 "cweb/weaver.w"

#ifdef W_MULTITHREAD
pthread_mutex_destroy(&(W._pending_files_mutex));
#endif
/*:540*/
#line 2027 "cweb/weaver.w"

exit(0);
}

void _update(void){
/*245:*/
#line 5597 "cweb/weaver.w"

/*280:*/
#line 6238 "cweb/weaver.w"

{
int i,key;

for(i= 0;i<20;i++){
key= _released_keys[i];











while(W.keyboard[key]> 0){
int j;
for(j= i;j<19;j++){
_released_keys[j]= _released_keys[j+1];
}
_released_keys[19]= 0;
key= _released_keys[i];
}
if(key==0)break;

if(key==W_LEFT_CTRL||key==W_RIGHT_CTRL)W.keyboard[W_CTRL]= 0;
else if(key==W_LEFT_SHIFT||key==W_RIGHT_SHIFT)
W.keyboard[W_SHIFT]= 0;
else if(key==W_LEFT_ALT||key==W_RIGHT_ALT)W.keyboard[W_ALT]= 0;

W.keyboard[key]= 0;
_released_keys[i]= 0;
}

for(i= 0;i<20;i++){
key= _pressed_keys[i];
if(key==0)break;

if(key==W_LEFT_CTRL||key==W_RIGHT_CTRL)
W.keyboard[W_CTRL]+= W.dt;
else if(key==W_LEFT_SHIFT||key==W_RIGHT_SHIFT)
W.keyboard[W_SHIFT]+= W.dt;
else if(key==W_LEFT_ALT||key==W_RIGHT_ALT)
W.keyboard[W_ALT]+= W.dt;

W.keyboard[key]+= W.dt;
}
}
/*:280*//*293:*/
#line 6606 "cweb/weaver.w"

#ifdef W_MULTITHREAD
pthread_mutex_lock(&_input_mutex);
#endif
/*:293*//*299:*/
#line 6689 "cweb/weaver.w"

{
int i,button;

for(i= 0;i<5;i++){
button= _released_buttons[i];
while(W.mouse.buttons[button]> 0){
int j;
for(j= i;j<4;j++){
_released_buttons[j]= _released_buttons[j+1];
}
_released_buttons[4]= 0;
button= _released_buttons[i];
}
if(button==0)break;
#if W_TARGET == W_ELF


if(button==W_MOUSE_LEFT)
XSetInputFocus(_dpy,_window,RevertToParent,CurrentTime);
#endif
W.mouse.buttons[button]= 0;
_released_buttons[i]= 0;
}

for(i= 0;i<5;i++){
button= _pressed_buttons[i];
if(button==0)break;
W.mouse.buttons[button]+= W.dt;
}
}
/*:299*//*309:*/
#line 6890 "cweb/weaver.w"

old_dx= W.mouse.dx;
old_dy= W.mouse.dy;
W.mouse.dx= W.mouse.dy= 0;
/*:309*/
#line 5598 "cweb/weaver.w"

#if W_TARGET == W_ELF
{
XEvent event;
while(XPending(_dpy)){
XNextEvent(_dpy,&event);

/*246:*/
#line 5635 "cweb/weaver.w"

if(event.type==ConfigureNotify){
XConfigureEvent config= event.xconfigure;
#ifdef W_MULTITHREAD
pthread_mutex_lock(&_window_mutex);
#endif
W.width= config.width;
W.height= config.height;
W.x= config.x+W.width/2;
W.y= W.resolution_y-config.y-W.height/2;
#ifdef W_MULTITHREAD
pthread_mutex_unlock(&_window_mutex);
#endif
continue;
}
/*:246*//*260:*/
#line 5790 "cweb/weaver.w"

#if W_WIDTH == 0 && W_HEIGHT == 0
if(event.type==FocusOut){
XSetInputFocus(_dpy,_window,RevertToParent,CurrentTime);
continue;
}
#endif
/*:260*//*278:*/
#line 6158 "cweb/weaver.w"

if(event.type==KeyPress){
unsigned int code= _translate_key(XkbKeycodeToKeysym(_dpy,
event.xkey.keycode,0,
0));
int i;

for(i= 0;i<20;i++){
if(_pressed_keys[i]==0||_pressed_keys[i]==code){
_pressed_keys[i]= code;
break;
}
}











if(W.keyboard[code]==0)
W.keyboard[code]= 1;
else if(W.keyboard[code]<0)
W.keyboard[code]*= -1;
continue;
}
/*:278*//*279:*/
#line 6194 "cweb/weaver.w"

if(event.type==KeyRelease){
unsigned int code= _translate_key(XkbKeycodeToKeysym(_dpy,
event.xkey.keycode,
0,0));
int i;

for(i= 0;i<20;i++){
if(_pressed_keys[i]==code){
_pressed_keys[i]= 0;
break;
}
}
for(;i<19;i++){
_pressed_keys[i]= _pressed_keys[i+1];
}
_pressed_keys[19]= 0;

for(i= 0;i<20;i++){
if(_released_keys[i]==0||_released_keys[i]==code){
_released_keys[i]= code;
break;
}
}

W.keyboard[code]*= -1;
continue;
}
/*:279*//*300:*/
#line 6726 "cweb/weaver.w"

if(event.type==ButtonPress){
unsigned int code= event.xbutton.button;
int i;

for(i= 0;i<5;i++){
if(_pressed_buttons[i]==0||_pressed_buttons[i]==code){
_pressed_buttons[i]= code;
break;
}
}




if(W.mouse.buttons[code]==0)
W.mouse.buttons[code]= 1;
else if(W.mouse.buttons[code]<0)
W.mouse.buttons[code]*= -1;
continue;
}
/*:300*//*301:*/
#line 6751 "cweb/weaver.w"

if(event.type==ButtonRelease){
unsigned int code= event.xbutton.button;
int i;

for(i= 0;i<5;i++){
if(_pressed_buttons[i]==code){
_pressed_buttons[i]= 0;
break;
}
}
for(;i<4;i++){
_pressed_buttons[i]= _pressed_buttons[i+1];
}
_pressed_buttons[4]= 0;

for(i= 0;i<5;i++){
if(_released_buttons[i]==0||_released_buttons[i]==code){
_released_buttons[i]= code;
break;
}
}

W.mouse.buttons[code]*= -1;
continue;
}
/*:301*//*311:*/
#line 6914 "cweb/weaver.w"

if(event.type==MotionNotify){
int x,y,dx,dy;
x= event.xmotion.x;
y= W.height-1-event.xmotion.y;
dx= x-W.mouse.x;
dy= y-W.mouse.y;
W.mouse.dx= ((float)dx/W.dt)*1000000;
W.mouse.dy= ((float)dy/W.dt)*1000000;
W.mouse.x= x;
W.mouse.y= y;
continue;
}
/*:311*/
#line 5605 "cweb/weaver.w"

}
}
#endif
#if W_TARGET == W_WEB
{
SDL_Event event;
while(SDL_PollEvent(&event)){

/*289:*/
#line 6460 "cweb/weaver.w"

if(event.type==SDL_KEYDOWN){
unsigned int code= event.key.keysym.sym;
int i;

for(i= 0;i<20;i++){
if(_pressed_keys[i]==0||_pressed_keys[i]==code){
_pressed_keys[i]= code;
break;
}
}





if(W.keyboard[code]==0)
W.keyboard[code]= 1;
else if(W.keyboard[code]<0)
W.keyboard[code]*= -1;
continue;
}
/*:289*//*290:*/
#line 6486 "cweb/weaver.w"

if(event.type==SDL_KEYUP){
unsigned int code= event.key.keysym.sym;
int i;

for(i= 0;i<20;i++){
if(_pressed_keys[i]==code){
_pressed_keys[i]= 0;
break;
}
}
for(;i<19;i++){
_pressed_keys[i]= _pressed_keys[i+1];
}
_pressed_keys[19]= 0;

for(i= 0;i<20;i++){
if(_released_keys[i]==0||_released_keys[i]==code){
_released_keys[i]= code;
break;
}
}

W.keyboard[code]*= -1;
continue;
}

/*:290*//*302:*/
#line 6782 "cweb/weaver.w"

if(event.type==SDL_MOUSEBUTTONDOWN){
unsigned int code= event.button.button;
int i;

for(i= 0;i<5;i++){
if(_pressed_buttons[i]==0||_pressed_buttons[i]==code){
_pressed_buttons[i]= code;
break;
}
}


if(W.mouse.buttons[code]==0)
W.mouse.buttons[code]= 1;
else if(W.mouse.buttons[code]<0)
W.mouse.buttons[code]*= -1;
continue;
}
/*:302*//*303:*/
#line 6805 "cweb/weaver.w"

if(event.type==SDL_MOUSEBUTTONUP){
unsigned int code= event.button.button;
int i;

for(i= 0;i<5;i++){
if(_pressed_buttons[i]==code){
_pressed_buttons[i]= 0;
break;
}
}
for(;i<4;i++){
_pressed_buttons[i]= _pressed_buttons[i+1];
}
_pressed_buttons[4]= 0;

for(i= 0;i<5;i++){
if(_released_buttons[i]==0||_released_buttons[i]==code){
_released_buttons[i]= code;
break;
}
}

W.mouse.buttons[code]*= -1;
continue;
}
/*:303*//*312:*/
#line 6931 "cweb/weaver.w"

if(event.type==SDL_MOUSEMOTION){
int x,y,dx,dy;
x= event.motion.x;
y= W.height-1-event.motion.y;
dx= x-W.mouse.x;
dy= y-W.mouse.y;
W.mouse.dx= ((float)dx/W.dt)*1000000;
W.mouse.dy= ((float)dy/W.dt)*1000000;
W.mouse.x= x;
W.mouse.y= y;
continue;
}
/*:312*/
#line 5614 "cweb/weaver.w"

}
}
#endif
/*310:*/
#line 6896 "cweb/weaver.w"


W.mouse.ddx= (int)((float)(W.mouse.dx-old_dx)/W.dt)*
1000000;
W.mouse.ddy= (int)((float)(W.mouse.dy-old_dy)/W.dt)*
1000000;
#ifdef W_MULTITHREAD

pthread_mutex_unlock(&_input_mutex);
#endif
/*:310*/
#line 5618 "cweb/weaver.w"

/*:245*//*263:*/
#line 5823 "cweb/weaver.w"

glClear(GL_COLOR_BUFFER_BIT);
/*:263*//*281:*/
#line 6293 "cweb/weaver.w"

#ifdef W_MULTITHREAD
pthread_mutex_lock(&_input_mutex);
#endif
W.keyboard[W_ANY]= (_pressed_keys[0]!=0);
/*:281*//*304:*/
#line 6836 "cweb/weaver.w"

W.mouse.buttons[W_ANY]= (_pressed_buttons[0]!=0);
#ifdef W_MULTITHREAD
pthread_mutex_unlock(&_input_mutex);
#endif
/*:304*//*356:*/
#line 7992 "cweb/weaver.w"

{
int i;
for(i= 0;i<_max_number_of_plugins;i++)
if(_plugins[i].defined&&_plugins[i].enabled)
_plugins[i]._run_plugin(&W);
}
/*:356*//*367:*/
#line 8159 "cweb/weaver.w"

{
int i;
#ifdef W_MULTITHREAD
pthread_mutex_lock(&_scheduler_mutex);
#endif
for(i= 0;i<W_MAX_SCHEDULING;i++){
if(_scheduled_functions[_number_of_loops][i].f==NULL)
break;
if(_scheduled_functions[_number_of_loops][i].period<
W.t-_scheduled_functions[_number_of_loops][i].last_execution){
_scheduled_functions[_number_of_loops][i].f();
_scheduled_functions[_number_of_loops][i].last_execution= W.t;
if(_scheduled_functions[_number_of_loops][i].periodic==false){
int j;
_scheduled_functions[_number_of_loops][i].f= NULL;
for(j= i+1;j<W_MAX_SCHEDULING;j++){
if(_scheduled_functions[_number_of_loops][j-1].f==NULL)
break;
_scheduled_functions[_number_of_loops][j-1].periodic= 
_scheduled_functions[_number_of_loops][j].periodic;
_scheduled_functions[_number_of_loops][j-1].last_execution= 
_scheduled_functions[_number_of_loops][j].last_execution;
_scheduled_functions[_number_of_loops][j-1].period= 
_scheduled_functions[_number_of_loops][j].period;
_scheduled_functions[_number_of_loops][j-1].f= 
_scheduled_functions[_number_of_loops][j].f;
}
_scheduled_functions[_number_of_loops][j-1].f= NULL;
i--;
}
}
}
#ifdef W_MULTITHREAD
pthread_mutex_unlock(&_scheduler_mutex);
#endif
}
/*:367*/
#line 2032 "cweb/weaver.w"

}

void _render(void){

glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
/*485:*/
#line 10728 "cweb/weaver.w"

if(_use_non_default_render){
glBindFramebuffer(GL_FRAMEBUFFER,_framebuffer);
glViewport(0,0,W.width,W.height);
glEnable(GL_DEPTH_TEST);
glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
}
/*:485*/
#line 2038 "cweb/weaver.w"


/*472:*/
#line 10430 "cweb/weaver.w"

{


int last_type;
int i;
bool first_element= true;
struct _shader*current_shader;

glDisable(GL_DEPTH_TEST);

glBindVertexArray(_interface_VAO);



for(i= 0;i<W_MAX_INTERFACES;i++){

if(_interface_queue[_number_of_loops][i]==NULL)break;
if(!(_interface_queue[_number_of_loops][i]->visible))continue;
if(first_element||
_interface_queue[_number_of_loops][i]->type!=last_type){
last_type= _interface_queue[_number_of_loops][i]->type;
if(_interface_queue[_number_of_loops][i]->type> 0){
current_shader= 
&(_shader_list[_interface_queue[_number_of_loops][i]->
type-1]);
}
else{
current_shader= &_default_interface_shader;
}
glUseProgram(current_shader->program_shader);
first_element= false;
}


glUniform4f(current_shader->_uniform_object_color,
_interface_queue[_number_of_loops][i]->r,
_interface_queue[_number_of_loops][i]->g,
_interface_queue[_number_of_loops][i]->b,
_interface_queue[_number_of_loops][i]->a);
glUniform2f(current_shader->_uniform_object_size,
_interface_queue[_number_of_loops][i]->width,
_interface_queue[_number_of_loops][i]->height);
glUniform1f(current_shader->_uniform_time,
(float)W.t/(float)1000000);
glUniform1i(current_shader->_uniform_integer,
_interface_queue[_number_of_loops][i]->integer);
glUniformMatrix4fv(current_shader->_uniform_model_view,1,false,
_interface_queue[_number_of_loops][i]->
_transform_matrix);

glEnableVertexAttribArray(current_shader->_attribute_vertex_position);
glVertexAttribPointer(current_shader->_attribute_vertex_position,
3,GL_FLOAT,GL_FALSE,0,(void*)0);
glDrawArrays(_interface_queue[_number_of_loops][i]->_mode,0,4);
glDisableVertexAttribArray(current_shader->
_attribute_vertex_position);
}


glBindVertexArray(0);
glEnable(GL_DEPTH_TEST);
}
/*:472*/
#line 2040 "cweb/weaver.w"

/*491:*/
#line 10869 "cweb/weaver.w"

if(_use_non_default_render){
struct _shader*current_shader;
glBindFramebuffer(GL_FRAMEBUFFER,0);
glViewport(0,0,W.resolution_x,W.resolution_y);
glBindVertexArray(_interface_VAO);
glDisable(GL_DEPTH_TEST);
if(_custom_final_shader){
glUseProgram(_shader_list[_custom_final_shader-1].program_shader);
current_shader= &(_shader_list[_custom_final_shader-1]);
}
else{
glUseProgram(_framebuffer_shader.program_shader);
current_shader= &(_framebuffer_shader);
}
glActiveTexture(GL_TEXTURE0);
glBindTexture(GL_TEXTURE_2D,_texture);
glEnableVertexAttribArray(current_shader->_attribute_vertex_position);
glVertexAttribPointer(current_shader->_attribute_vertex_position,
3,GL_FLOAT,GL_FALSE,0,(void*)0);

glUniform2f(current_shader->_uniform_object_size,W.width,W.height);
glUniform4f(current_shader->_uniform_object_color,W_DEFAULT_COLOR,
1.0);
glUniform1f(current_shader->_uniform_time,
(float)W.t/(float)1000000);
glUniformMatrix4fv(current_shader->_uniform_model_view,1,false,
_framebuffer_matrix);
/*503:*/
#line 11056 "cweb/weaver.w"

glUniform1i(current_shader->_uniform_integer,
W.final_shader_integer);
/*:503*/
#line 10897 "cweb/weaver.w"

glDrawArrays(GL_TRIANGLE_FAN,0,4);
glDisableVertexAttribArray(current_shader->_attribute_vertex_position);
}
/*:491*/
#line 2041 "cweb/weaver.w"

#if W_TARGET == W_ELF
glXSwapBuffers(_dpy,_window);
#else
glFlush();
#endif
}
/*:72*/
