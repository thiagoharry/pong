/*70:*/
#line 1977 "cweb/weaver.w"

#ifndef _weaver_h_
#define _weaver_h_
#ifdef __cplusplus
extern"C"{
#endif
/*66:*/
#line 1928 "cweb/weaver.w"

#include "conf_begin.h"
#include "../../conf/conf.h"
#include "conf_end.h"
/*:66*/
#line 1983 "cweb/weaver.w"

#include <stdlib.h> 
#include <stdbool.h> 
#if W_TARGET == W_WEB
#include <emscripten.h> 
#endif
/*71:*/
#line 2019 "cweb/weaver.w"

void _awake_the_weaver(void);
void _may_the_weaver_sleep(void)__attribute__((noreturn));
void _update(void);
void _render(void);
#define Winit() _awake_the_weaver()
#define Wexit() _may_the_weaver_sleep()
/*:71*//*79:*/
#line 2145 "cweb/weaver.w"

struct timeval _last_time;
/*:79*//*81:*/
#line 2162 "cweb/weaver.w"

unsigned long _update_time(void);
/*:81*//*84:*/
#line 2208 "cweb/weaver.w"

extern struct _game_struct _game;
/*:84*//*89:*/
#line 2370 "cweb/weaver.w"

#include "memory.h"
/*:89*//*163:*/
#line 3851 "cweb/weaver.w"

#include <stdio.h> 
#include <sys/time.h> 

#define W_TIMER_BEGIN() { struct timeval _begin, _end; \
gettimeofday(&_begin, NULL);
#define W_TIMER_END() gettimeofday(&_end, NULL); \
printf("%ld us\n", (1000000 * (_end.tv_sec - _begin.tv_sec) + \
_end.tv_usec - _begin.tv_usec)); \
}

/*:163*//*169:*/
#line 4167 "cweb/weaver.w"

typedef void MAIN_LOOP;







bool _loop_begin,_running_loop;
/*:169*//*170:*/
#line 4193 "cweb/weaver.w"

void _Wloop(MAIN_LOOP(*f)(void))__attribute__((noreturn));
void Wsubloop(MAIN_LOOP(*f)(void))__attribute__((noreturn));
#define Wloop(a) ((W.pending_files)?(false):(_Wloop(a)))
/*:170*//*171:*/
#line 4229 "cweb/weaver.w"

bool _first_loop;

int _number_of_loops;
MAIN_LOOP(*_loop_stack[W_MAX_SUBLOOP])(void);
/*:171*//*174:*/
#line 4282 "cweb/weaver.w"

void _exit_loop(void)__attribute__((noreturn));
/*:174*//*176:*/
#line 4322 "cweb/weaver.w"

#define Wexit_loop() (_running_loop =  false)
/*:176*//*179:*/
#line 4402 "cweb/weaver.w"

long _lag;
/*:179*//*182:*/
#line 4421 "cweb/weaver.w"

#define LOOP_INIT if(!_running_loop && !W.pending_files) _exit_loop();\
  if(!_running_loop)                                                    \
   goto _LOOP_FINALIZATION; if(!_loop_begin) goto _END_LOOP_INITIALIZATION;\
   _BEGIN_LOOP_INITIALIZATION
#define LOOP_BODY _loop_begin =   false; if(_loop_begin)\
   goto _BEGIN_LOOP_INITIALIZATION; _END_LOOP_INITIALIZATION:\
   _lag +=   _update_time(); while(_lag >= 40000){ _update(); _LABEL_0
#define LOOP_END _lag -=   40000; W.t +=   40000; } \
   _render(); if(_running_loop || W.pending_files) return; \
   if(W.t == 0) goto _LABEL_0;\
   _LOOP_FINALIZATION
/*:182*//*189:*/
#line 4583 "cweb/weaver.w"

#include "numeric.h"
/*:189*//*215:*/
#line 5080 "cweb/weaver.w"

#include "trie.h"
/*:215*//*229:*/
#line 5372 "cweb/weaver.w"

#include <GL/glew.h> 
/*:229*//*233:*/
#line 5453 "cweb/weaver.w"

#ifdef W_MULTITHREAD
extern pthread_mutex_t _window_mutex;
#endif
/*:233*//*235:*/
#line 5470 "cweb/weaver.w"

#if W_TARGET == W_ELF
#include "window.h"
#endif
/*:235*//*241:*/
#line 5579 "cweb/weaver.w"

#if W_TARGET == W_ELF
#include <X11/Xlib.h> 
extern Display*_dpy;
#endif
/*:241*//*244:*/
#line 5615 "cweb/weaver.w"

#if W_TARGET == W_ELF
extern int _screen;
#endif
/*:244*//*249:*/
#line 5657 "cweb/weaver.w"

#if W_TARGET == W_ELF
#include <X11/Xlib.h> 
extern Window _window;
#endif
/*:249*//*257:*/
#line 5841 "cweb/weaver.w"

#if W_TARGET == W_ELF
#include <GL/glx.h> 
extern GLXContext _context;
#endif
/*:257*//*264:*/
#line 5956 "cweb/weaver.w"

#if W_TARGET == W_WEB
#include "canvas.h"
#endif
/*:264*//*294:*/
#line 6470 "cweb/weaver.w"

#ifdef W_MULTITHREAD
pthread_mutex_t _input_mutex;
#endif

/*:294*//*297:*/
#line 6531 "cweb/weaver.w"

#define W_SHIFT 2 
#define W_CTRL  3 
#define W_ALT   4 
#define W_ANY   6 
/*:297*//*299:*/
#line 6568 "cweb/weaver.w"

int _Wkey_translate(unsigned old_value,unsigned new_value);
void _Werase_key_translations(void);
/*:299*//*307:*/
#line 6792 "cweb/weaver.w"

#if W_TARGET == W_ELF
#define W_UP          XK_Up
#define W_RIGHT       XK_Right
#define W_DOWN        XK_Down
#define W_LEFT        XK_Left
#define W_PLUS        XK_KP_Add
#define W_MINUS       XK_KP_Subtract
#define W_ESC         XK_Escape
#define W_A           XK_a
#define W_S           XK_s
#define W_D           XK_d
#define W_W           XK_w
#define W_ENTER       XK_Return
#define W_SPACEBAR    XK_space
#define W_LEFT_CTRL   XK_Control_L
#define W_RIGHT_CTRL  XK_Control_R
#define W_F1          XK_F1
#define W_F2          XK_F2
#define W_F3          XK_F3
#define W_F4          XK_F4
#define W_F5          XK_F5
#define W_F6          XK_F6
#define W_F7          XK_F7
#define W_F8          XK_F8
#define W_F9          XK_F9
#define W_F10         XK_F10
#define W_F11         XK_F11
#define W_F12         XK_F12
#define W_BACKSPACE   XK_BackSpace
#define W_TAB         XK_Tab
#define W_PAUSE       XK_Pause
#define W_DELETE      XK_Delete
#define W_SCROLL_LOCK XK_Scroll_Lock
#define W_HOME        XK_Home
#define W_PAGE_UP     XK_Page_Up
#define W_PAGE_DOWN   XK_Page_Down
#define W_END         XK_End
#define W_INSERT      XK_Insert
#define W_NUM_LOCK    XK_Num_Lock
#define W_0           XK_0
#define W_1           XK_1
#define W_2           XK_2
#define W_3           XK_3
#define W_4           XK_4
#define W_5           XK_5
#define W_6           XK_6
#define W_7           XK_7
#define W_8           XK_8
#define W_9           XK_9
#define W_LEFT_SHIFT  XK_Shift_L
#define W_RIGHT_SHIFT XK_Shift_R
#define W_CAPS_LOCK   XK_Caps_Lock
#define W_LEFT_ALT    XK_Alt_L
#define W_RIGHT_ALT   XK_Alt_R
#define W_Q           XK_q
#define W_E           XK_e
#define W_R           XK_r
#define W_T           XK_t
#define W_Y           XK_y
#define W_U           XK_u
#define W_I           XK_i
#define W_O           XK_o
#define W_P           XK_p
#define W_F           XK_f
#define W_G           XK_g
#define W_H           XK_h
#define W_J           XK_j
#define W_K           XK_k
#define W_L           XK_l
#define W_Z           XK_z
#define W_X           XK_x
#define W_C           XK_c
#define W_V           XK_v
#define W_B           XK_b
#define W_N           XK_n
#define W_M           XK_m
#endif
/*:307*//*308:*/
#line 6884 "cweb/weaver.w"

void _Wflush_input(void);
/*:308*//*313:*/
#line 6937 "cweb/weaver.w"

#if W_TARGET == W_WEB
#include <SDL/SDL.h> 
#endif
/*:313*//*316:*/
#line 7005 "cweb/weaver.w"

#if W_TARGET == W_WEB
#define W_UP          SDLK_UP
#define W_RIGHT       SDLK_RIGHT
#define W_DOWN        SDLK_DOWN
#define W_LEFT        SDLK_LEFT
#define W_PLUS        SDLK_PLUS
#define W_MINUS       SDLK_MINUS
#define W_ESC         SDLK_ESCAPE
#define W_A           SDLK_a
#define W_S           SDLK_s
#define W_D           SDLK_d
#define W_W           SDLK_w
#define W_ENTER       SDLK_RETURN
#define W_SPACEBAR    SDLK_SPACE
#define W_LEFT_CTRL   SDLK_LCTRL
#define W_RIGHT_CTRL  SDLK_RCTRL
#define W_F1          SDLK_F1
#define W_F2          SDLK_F2
#define W_F3          SDLK_F3
#define W_F4          SDLK_F4
#define W_F5          SDLK_F5
#define W_F6          SDLK_F6
#define W_F7          SDLK_F7
#define W_F8          SDLK_F8
#define W_F9          SDLK_F9
#define W_F10         SDLK_F10
#define W_F11         SDLK_F11
#define W_F12         SDLK_F12
#define W_BACKSPACE   SDLK_BACKSPACE
#define W_TAB         SDLK_TAB
#define W_PAUSE       SDLK_PAUSE
#define W_DELETE      SDLK_DELETE
#define W_SCROLL_LOCK SDLK_SCROLLOCK
#define W_HOME        SDLK_HOME
#define W_PAGE_UP     SDLK_PAGEUP
#define W_PAGE_DOWN   SDLK_PAGEDOWN
#define W_END         SDLK_END
#define W_INSERT      SDLK_INSERT
#define W_NUM_LOCK    SDLK_NUMLOCK
#define W_0           SDLK_0
#define W_1           SDLK_1
#define W_2           SDLK_2
#define W_3           SDLK_3
#define W_4           SDLK_4
#define W_5           SDLK_5
#define W_6           SDLK_6
#define W_7           SDLK_7
#define W_8           SDLK_8
#define W_9           SDLK_9
#define W_LEFT_SHIFT  SDLK_LSHIFT
#define W_RIGHT_SHIFT SDLK_RSHIFT
#define W_CAPS_LOCK   SDLK_CAPSLOCK
#define W_LEFT_ALT    SDLK_LALT
#define W_RIGHT_ALT   SDLK_RALT
#define W_Q           SDLK_q
#define W_E           SDLK_e
#define W_R           SDLK_r
#define W_T           SDLK_t
#define W_Y           SDLK_y
#define W_U           SDLK_u
#define W_I           SDLK_i
#define W_O           SDLK_o
#define W_P           SDLK_p
#define W_F           SDLK_f
#define W_G           SDLK_g
#define W_H           SDLK_h
#define W_J           SDLK_j
#define W_K           SDLK_k
#define W_L           SDLK_l
#define W_Z           SDLK_z
#define W_X           SDLK_x
#define W_C           SDLK_c
#define W_V           SDLK_v
#define W_B           SDLK_b
#define W_N           SDLK_n
#define W_M           SDLK_m
#endif
/*:316*//*320:*/
#line 7121 "cweb/weaver.w"

struct _mouse{


long buttons[7];
int x,y,dx,dy,ddx,ddy;
};
/*:320*//*322:*/
#line 7139 "cweb/weaver.w"

#if W_TARGET == W_ELF
#define W_MOUSE_LEFT   Button1
#define W_MOUSE_MIDDLE Button2
#define W_MOUSE_RIGHT  Button3
#define W_MOUSE_B1     Button4
#define W_MOUSE_B2     Button5
#endif
#if W_TARGET == W_WEB
#define W_MOUSE_LEFT   SDL_BUTTON_LEFT
#define W_MOUSE_MIDDLE SDL_BUTTON_MIDDLE
#define W_MOUSE_RIGHT  SDL_BUTTON_RIGHT
#define W_MOUSE_B1     4
#define W_MOUSE_B2     5
#endif
/*:322*//*340:*/
#line 7461 "cweb/weaver.w"

bool _using_original_cursor;
void _Whide_cursor(void);
/*:340*//*388:*/
#line 8575 "cweb/weaver.w"

#ifdef W_MULTITHREAD
pthread_mutex_t _scheduler_mutex;
#endif
struct{
bool periodic;
unsigned long last_execution;
unsigned long period;
void(*f)(void);
}_scheduled_functions[W_MAX_SUBLOOP][W_MAX_SCHEDULING];
/*:388*//*394:*/
#line 8697 "cweb/weaver.w"

void _run_periodically(void(*f)(void),float t);
void _run_futurelly(void(*f)(void),float t);
float _cancel(void(*f)(void));
float _period(void(*f)(void));
/*:394*//*415:*/
#line 9109 "cweb/weaver.w"

#include "interface.h"
/*:415*//*463:*/
#line 10049 "cweb/weaver.w"

#include <ctype.h>  
#include "shaders.h"
/*:463*//*503:*/
#line 11177 "cweb/weaver.w"

#define W_NONE            0
#define W_DEFAULT_SHADER -1
/*:503*//*504:*/
#line 11182 "cweb/weaver.w"










int _final_shader[W_MAX_SUBLOOP];


bool _changed_resolution;


GLuint _framebuffer;
/*:504*//*507:*/
#line 11228 "cweb/weaver.w"



GLuint _texture;
/*:507*//*509:*/
#line 11267 "cweb/weaver.w"


GLuint _depth_stencil;
/*:509*//*533:*/
#line 11670 "cweb/weaver.w"

int _final_shader_integer[W_MAX_SUBLOOP];
/*:533*//*541:*/
#line 11775 "cweb/weaver.w"

#include "sound.h"
/*:541*//*606:*/
#line 12884 "cweb/weaver.w"

#ifdef W_MULTITHREAD
pthread_mutex_t _finalizing_mutex;
#endif
struct _finalize_element{
void*data;
void(*finalize)(void*);
struct _finalize_element*prev,*next;
};
struct _finalize_element*_finalize_list[W_MAX_SUBLOOP];
/*:606*//*609:*/
#line 12928 "cweb/weaver.w"

void _finalize_after(void*,void(*f)(void*));
/*:609*//*611:*/
#line 12970 "cweb/weaver.w"

void _finalize_all(void);
/*:611*//*615:*/
#line 13008 "cweb/weaver.w"

void _finalize_this(void*,bool);
/*:615*//*621:*/
#line 13147 "cweb/weaver.w"

#include "gif.h"
/*:621*//*664:*/
#line 14788 "cweb/weaver.w"

GLuint _empty_texture;
char _empty_image[4];
/*:664*//*712:*/
#line 15889 "cweb/weaver.w"

#include "database.h"
/*:712*//*813:*/
#line 17911 "cweb/weaver.w"

#include "metafont.h"
/*:813*/
#line 1989 "cweb/weaver.w"


/*75:*/
#line 2089 "cweb/weaver.w"



extern struct _weaver_struct{
/*78:*/
#line 2139 "cweb/weaver.w"


unsigned long long t;
unsigned long dt;
/*:78*//*85:*/
#line 2212 "cweb/weaver.w"


struct _game_struct*game;
/*:85*//*230:*/
#line 5381 "cweb/weaver.w"


int resolution_x,resolution_y,framerate;
/*:230*//*232:*/
#line 5444 "cweb/weaver.w"


int width,height,x,y;
/*:232*//*292:*/
#line 6450 "cweb/weaver.w"


long keyboard[0xffff];
/*:292*//*321:*/
#line 7130 "cweb/weaver.w"


struct _mouse mouse;
/*:321*//*528:*/
#line 11622 "cweb/weaver.w"


int final_shader_integer;
/*:528*//*551:*/
#line 11856 "cweb/weaver.w"


int number_of_sound_devices;
char**sound_device_name;
/*:551*//*571:*/
#line 12168 "cweb/weaver.w"

unsigned pending_files;
#ifdef W_MULTITHREAD
pthread_mutex_t _pending_files_mutex;
#endif
/*:571*/
#line 2093 "cweb/weaver.w"

/*116:*/
#line 3076 "cweb/weaver.w"


#if W_DEBUG_LEVEL >= 1
void*(*create_arena)(size_t,char*,unsigned long);
#else
void*(*create_arena)(size_t);
#endif
/*:116*//*124:*/
#line 3202 "cweb/weaver.w"


int(*destroy_arena)(void*);
/*:124*//*129:*/
#line 3327 "cweb/weaver.w"


#if W_DEBUG_LEVEL >= 1
void*(*alloc_arena)(void*,size_t,char*,unsigned long);
#else
void*(*alloc_arena)(void*,size_t);
#endif
/*:129*//*133:*/
#line 3439 "cweb/weaver.w"


#if W_DEBUG_LEVEL >= 2 && !defined(W_MULTITHREAD)
void(*free)(void*,char*,unsigned long);
#else
void(*free)(void*);
#endif
/*:133*//*139:*/
#line 3549 "cweb/weaver.w"


#if W_DEBUG_LEVEL >= 1
int(*breakpoint_arena)(void*,char*,unsigned long);
#else
int(*breakpoint_arena)(void*);
#endif
/*:139*//*143:*/
#line 3615 "cweb/weaver.w"


void(*trash_arena)(void*);
/*:143*//*154:*/
#line 3748 "cweb/weaver.w"


#if W_DEBUG_LEVEL >= 1
void*(*alloc)(size_t,char*,unsigned long);
#else
void*(*alloc)(size_t);
#endif
/*:154*//*159:*/
#line 3816 "cweb/weaver.w"


#if W_DEBUG_LEVEL >= 1
int(*breakpoint)(char*,unsigned long);
#else
int(*breakpoint)(void);
#endif
void(*trash)(void);
/*:159*//*205:*/
#line 4931 "cweb/weaver.w"


unsigned long(*random)(void);
/*:205*//*276:*/
#line 6204 "cweb/weaver.w"

void(*resize_window)(int,int);
/*:276*//*282:*/
#line 6250 "cweb/weaver.w"

void(*move_window)(int,int);
/*:282*//*301:*/
#line 6624 "cweb/weaver.w"

int(*key_translate)(unsigned,unsigned);
void(*erase_key_translations)(void);
/*:301*//*310:*/
#line 6914 "cweb/weaver.w"

void(*flush_input)(void);
/*:310*//*344:*/
#line 7528 "cweb/weaver.w"

void(*hide_cursor)(void);
/*:344*//*362:*/
#line 8109 "cweb/weaver.w"

bool(*reload_plugin)(int);
/*:362*//*373:*/
#line 8336 "cweb/weaver.w"

int(*get_plugin)(char*);
/*:373*//*377:*/
#line 8445 "cweb/weaver.w"

void(*reload_all_plugins)(void);
/*:377*//*399:*/
#line 8843 "cweb/weaver.w"


void(*run_periodically)(void(*f)(void),float);
void(*run_futurelly)(void(*f)(void),float);
float(*cancel)(void(*f)(void));
float(*period)(void(*f)(void));
/*:399*//*404:*/
#line 8932 "cweb/weaver.w"

bool(*enable_plugin)(int);
bool(*disable_plugin)(int);
bool(*is_plugin_enabled)(int);
/*:404*//*408:*/
#line 8982 "cweb/weaver.w"

void*(*get_plugin_data)(int);
bool(*set_plugin_data)(int,void*);
/*:408*//*430:*/
#line 9417 "cweb/weaver.w"

struct interface*(*new_interface)(int,int,int,int,int,...);
/*:430*//*434:*/
#line 9465 "cweb/weaver.w"

bool(*destroy_interface)(struct interface*);
/*:434*//*438:*/
#line 9531 "cweb/weaver.w"

struct interface*(*copy_interface)(struct interface*);
/*:438*//*443:*/
#line 9629 "cweb/weaver.w"

void(*move_interface)(struct interface*,float,float);
/*:443*//*447:*/
#line 9708 "cweb/weaver.w"

void(*resize_interface)(struct interface*,float,float);
/*:447*//*451:*/
#line 9788 "cweb/weaver.w"

void(*rotate_interface)(struct interface*,float);
/*:451*//*521:*/
#line 11578 "cweb/weaver.w"

void(*change_resolution)(int,int);
/*:521*//*526:*/
#line 11611 "cweb/weaver.w"

void(*change_final_shader)(int);
/*:526*//*558:*/
#line 11965 "cweb/weaver.w"

bool(*select_sound_device)(int);
/*:558*//*562:*/
#line 11998 "cweb/weaver.w"

int(*current_sound_device)(void);
/*:562*//*595:*/
#line 12778 "cweb/weaver.w"

struct sound*(*new_sound)(char*);
/*:595*//*599:*/
#line 12810 "cweb/weaver.w"

void(*play_sound)(struct sound*);
/*:599*//*603:*/
#line 12859 "cweb/weaver.w"

void(*destroy_sound)(struct sound*);
/*:603*//*723:*/
#line 16080 "cweb/weaver.w"

void(*write_integer)(char*,int);
/*:723*//*728:*/
#line 16152 "cweb/weaver.w"

void(*write_float)(char*,float);
/*:728*//*733:*/
#line 16220 "cweb/weaver.w"

void(*write_string)(char*,char*);
/*:733*//*739:*/
#line 16292 "cweb/weaver.w"

bool(*read_integer)(char*,int*);
bool(*read_float)(char*,float*);
bool(*read_string)(char*,char*,int);
/*:739*//*749:*/
#line 16541 "cweb/weaver.w"

void(*delete_integer)(char*);
void(*delete_float)(char*);
void(*delete_string)(char*);
void(*delete_all)(void);
/*:749*//*772:*/
#line 17057 "cweb/weaver.w"

bool(*play_music)(char*,bool);
/*:772*//*776:*/
#line 17112 "cweb/weaver.w"

bool(*pause_music)(char*);
/*:776*//*782:*/
#line 17216 "cweb/weaver.w"

bool(*stop_music)(char*);
/*:782*//*786:*/
#line 17247 "cweb/weaver.w"

float(*get_volume)(char*);
/*:786*//*790:*/
#line 17307 "cweb/weaver.w"

float(*increase_volume)(char*,float);
/*:790*/
#line 2094 "cweb/weaver.w"

}W;
/*:75*/
#line 1991 "cweb/weaver.w"

/*352:*/
#line 7725 "cweb/weaver.w"

#include "plugins.h"
/*:352*//*385:*/
#line 8535 "cweb/weaver.w"

#if W_TARGET == W_WEB
#include "../../.hidden_code/header.h"
#endif
/*:385*/
#line 1992 "cweb/weaver.w"

/*349:*/
#line 7669 "cweb/weaver.w"


#define W_PLUGIN struct _weaver_struct *_W
#ifdef W_PLUGIN_CODE
#define W (*_W)
#endif
/*:349*/
#line 1993 "cweb/weaver.w"

#ifdef __cplusplus
}
#endif
#endif
/*:70*/
