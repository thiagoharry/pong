/*70:*/
#line 1959 "cweb/weaver.w"

#ifndef _weaver_h_
#define _weaver_h_
#ifdef __cplusplus
extern"C"{
#endif
/*66:*/
#line 1910 "cweb/weaver.w"

#include "conf_begin.h"
#include "../../conf/conf.h"
#include "conf_end.h"
/*:66*/
#line 1965 "cweb/weaver.w"

#include <stdlib.h> 
#include <stdbool.h> 
#if W_TARGET == W_WEB
#include <emscripten.h> 
#endif
/*71:*/
#line 2001 "cweb/weaver.w"

void _awake_the_weaver(void);
void _may_the_weaver_sleep(void)__attribute__((noreturn));
void _update(void);
void _render(void);
#define Winit() _awake_the_weaver()
#define Wexit() _may_the_weaver_sleep()
/*:71*//*79:*/
#line 2127 "cweb/weaver.w"

struct timeval _last_time;
/*:79*//*81:*/
#line 2144 "cweb/weaver.w"

unsigned long _update_time(void);
/*:81*//*84:*/
#line 2190 "cweb/weaver.w"

extern struct _game_struct _game;
/*:84*//*89:*/
#line 2352 "cweb/weaver.w"

#include "memory.h"
/*:89*//*162:*/
#line 3799 "cweb/weaver.w"

#include <stdio.h> 
#include <sys/time.h> 

#define W_TIMER_BEGIN() { struct timeval _begin, _end; \
gettimeofday(&_begin, NULL);
#define W_TIMER_END() gettimeofday(&_end, NULL); \
printf("%ld us\n", (1000000 * (_end.tv_sec - _begin.tv_sec) + \
_end.tv_usec - _begin.tv_usec)); \
}

/*:162*//*168:*/
#line 4115 "cweb/weaver.w"

typedef void MAIN_LOOP;







bool _loop_begin,_running_loop;
/*:168*//*169:*/
#line 4141 "cweb/weaver.w"

void Wloop(MAIN_LOOP(*f)(void))__attribute__((noreturn));
void Wsubloop(MAIN_LOOP(*f)(void))__attribute__((noreturn));
/*:169*//*170:*/
#line 4164 "cweb/weaver.w"

bool _first_loop;

int _number_of_loops;
MAIN_LOOP(*_loop_stack[W_MAX_SUBLOOP])(void);
/*:170*//*173:*/
#line 4217 "cweb/weaver.w"

void _exit_loop(void)__attribute__((noreturn));
/*:173*//*175:*/
#line 4257 "cweb/weaver.w"

#define Wexit_loop() (_running_loop =  false)
/*:175*//*178:*/
#line 4336 "cweb/weaver.w"

long _lag;
/*:178*//*181:*/
#line 4355 "cweb/weaver.w"

#define LOOP_INIT if(!_running_loop) _exit_loop(); if(!_running_loop)\
   goto _LOOP_FINALIZATION; if(!_loop_begin) goto _END_LOOP_INITIALIZATION;\
   _BEGIN_LOOP_INITIALIZATION
#define LOOP_BODY _loop_begin =  false; if(_loop_begin)\
   goto _BEGIN_LOOP_INITIALIZATION; _END_LOOP_INITIALIZATION:\
   _lag +=  _update_time(); while(_lag >= 40000){ _update(); _LABEL_0
#define LOOP_END _lag -=  40000; W.t +=  40000; } \
   _render(); if(_running_loop) return; if(W.t == 0) goto _LABEL_0;\
   _LOOP_FINALIZATION
/*:181*//*187:*/
#line 4490 "cweb/weaver.w"

#include "numeric.h"
/*:187*//*207:*/
#line 4928 "cweb/weaver.w"

#include <GL/glew.h> 
/*:207*//*211:*/
#line 5009 "cweb/weaver.w"

#ifdef W_MULTITHREAD
extern pthread_mutex_t _window_mutex;
#endif
/*:211*//*213:*/
#line 5026 "cweb/weaver.w"

#if W_TARGET == W_ELF
#include "window.h"
#endif
/*:213*//*219:*/
#line 5135 "cweb/weaver.w"

#if W_TARGET == W_ELF
#include <X11/Xlib.h> 
extern Display*_dpy;
#endif
/*:219*//*226:*/
#line 5206 "cweb/weaver.w"

#if W_TARGET == W_ELF
#include <X11/Xlib.h> 
extern Window _window;
#endif
/*:226*//*239:*/
#line 5477 "cweb/weaver.w"

#if W_TARGET == W_WEB
#include "canvas.h"
#endif
/*:239*//*269:*/
#line 5984 "cweb/weaver.w"

#ifdef W_MULTITHREAD
pthread_mutex_t _input_mutex;
#endif

/*:269*//*272:*/
#line 6045 "cweb/weaver.w"

#define W_SHIFT 2 
#define W_CTRL  3 
#define W_ALT   4 
#define W_ANY   6 
/*:272*//*274:*/
#line 6082 "cweb/weaver.w"

int _Wkey_translate(unsigned old_value,unsigned new_value);
void _Werase_key_translations(void);
/*:274*//*282:*/
#line 6306 "cweb/weaver.w"

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
/*:282*//*283:*/
#line 6398 "cweb/weaver.w"

void _Wflush_input(void);
/*:283*//*288:*/
#line 6451 "cweb/weaver.w"

#if W_TARGET == W_WEB
#include <SDL/SDL.h> 
#endif
/*:288*//*291:*/
#line 6519 "cweb/weaver.w"

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
/*:291*//*295:*/
#line 6635 "cweb/weaver.w"

struct _mouse{


long buttons[7];
int x,y,dx,dy,ddx,ddy;
};
/*:295*//*297:*/
#line 6653 "cweb/weaver.w"

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
/*:297*//*315:*/
#line 6975 "cweb/weaver.w"

bool _using_original_cursor;
void _Whide_cursor(void);
/*:315*//*363:*/
#line 8088 "cweb/weaver.w"

#ifdef W_MULTITHREAD
pthread_mutex_t _scheduler_mutex;
#endif
struct{
bool periodic;
unsigned long last_execution;
unsigned long period;
void(*f)(void);
}_scheduled_functions[W_MAX_SUBLOOP][W_MAX_SCHEDULING];
/*:363*//*369:*/
#line 8209 "cweb/weaver.w"

void _run_periodically(void(*f)(void),float t);
void _run_futurelly(void(*f)(void),float t);
void _cancel(void(*f)(void));
float _period(void(*f)(void));
/*:369*//*390:*/
#line 8602 "cweb/weaver.w"

#include "interface.h"
/*:390*//*438:*/
#line 9537 "cweb/weaver.w"

#include <ctype.h>  
#include "shaders.h"
/*:438*//*478:*/
#line 10638 "cweb/weaver.w"



bool _use_non_default_render;

GLuint _framebuffer;
/*:478*//*481:*/
#line 10671 "cweb/weaver.w"



GLuint _texture;
/*:481*//*483:*/
#line 10709 "cweb/weaver.w"


GLuint _depth_stencil;
/*:483*//*509:*/
#line 11166 "cweb/weaver.w"

#include "sound.h"
/*:509*/
#line 1971 "cweb/weaver.w"


/*75:*/
#line 2071 "cweb/weaver.w"



extern struct _weaver_struct{
/*78:*/
#line 2121 "cweb/weaver.w"


unsigned long long t;
unsigned long dt;
/*:78*//*85:*/
#line 2194 "cweb/weaver.w"


struct _game_struct*game;
/*:85*//*208:*/
#line 4937 "cweb/weaver.w"


int resolution_x,resolution_y,framerate;
/*:208*//*210:*/
#line 5000 "cweb/weaver.w"


int width,height,x,y;
/*:210*//*267:*/
#line 5964 "cweb/weaver.w"


long keyboard[0xffff];
/*:267*//*296:*/
#line 6644 "cweb/weaver.w"


struct _mouse mouse;
/*:296*//*502:*/
#line 11055 "cweb/weaver.w"


int final_shader_integer;
/*:502*//*519:*/
#line 11246 "cweb/weaver.w"


int number_of_sound_devices;
char**sound_device_name;
/*:519*//*539:*/
#line 11557 "cweb/weaver.w"

unsigned pending_files;
#ifdef W_MULTITHREAD
pthread_mutex_t _pending_files_mutex;
#endif
/*:539*/
#line 2075 "cweb/weaver.w"

/*116:*/
#line 3056 "cweb/weaver.w"


#if W_DEBUG_LEVEL >= 1
void*(*create_arena)(size_t,char*,unsigned long);
#else
void*(*create_arena)(size_t);
#endif
/*:116*//*124:*/
#line 3182 "cweb/weaver.w"


int(*destroy_arena)(void*);
/*:124*//*129:*/
#line 3306 "cweb/weaver.w"


#if W_DEBUG_LEVEL >= 1
void*(*alloc_arena)(void*,size_t,char*,unsigned long);
#else
void*(*alloc_arena)(void*,size_t);
#endif
/*:129*//*133:*/
#line 3418 "cweb/weaver.w"


#if W_DEBUG_LEVEL >= 2 && !defined(W_MULTITHREAD)
void(*free)(void*,char*,unsigned long);
#else
void(*free)(void*);
#endif
/*:133*//*139:*/
#line 3527 "cweb/weaver.w"


#if W_DEBUG_LEVEL >= 1
int(*breakpoint_arena)(void*,char*,unsigned long);
#else
int(*breakpoint_arena)(void*);
#endif
/*:139*//*143:*/
#line 3593 "cweb/weaver.w"


void(*trash_arena)(void*);
/*:143*//*153:*/
#line 3710 "cweb/weaver.w"


#if W_DEBUG_LEVEL >= 1
void*(*alloc)(size_t,char*,unsigned long);
#else
void*(*alloc)(size_t);
#endif
/*:153*//*158:*/
#line 3766 "cweb/weaver.w"


#if W_DEBUG_LEVEL >= 1
int(*breakpoint)(char*,unsigned long);
#else
int(*breakpoint)(void);
#endif
void(*trash)(void);
/*:158*//*202:*/
#line 4824 "cweb/weaver.w"


unsigned long(*random)(void);
/*:202*//*251:*/
#line 5719 "cweb/weaver.w"

void(*resize_window)(int,int);
/*:251*//*257:*/
#line 5765 "cweb/weaver.w"

void(*move_window)(int,int);
/*:257*//*276:*/
#line 6138 "cweb/weaver.w"

int(*key_translate)(unsigned,unsigned);
void(*erase_key_translations)(void);
/*:276*//*285:*/
#line 6428 "cweb/weaver.w"

void(*flush_input)(void);
/*:285*//*319:*/
#line 7042 "cweb/weaver.w"

void(*hide_cursor)(void);
/*:319*//*337:*/
#line 7623 "cweb/weaver.w"

bool(*reload_plugin)(int);
/*:337*//*348:*/
#line 7850 "cweb/weaver.w"

int(*get_plugin)(char*);
/*:348*//*352:*/
#line 7959 "cweb/weaver.w"

void(*reload_all_plugins)(void);
/*:352*//*374:*/
#line 8348 "cweb/weaver.w"


void(*run_periodically)(void(*f)(void),float);
void(*run_futurelly)(void(*f)(void),float);
void(*cancel)(void(*f)(void));
float(*period)(void(*f)(void));
/*:374*//*379:*/
#line 8437 "cweb/weaver.w"

bool(*enable_plugin)(int);
bool(*disable_plugin)(int);
bool(*is_plugin_enabled)(int);
/*:379*//*383:*/
#line 8487 "cweb/weaver.w"

void*(*get_plugin_data)(int);
bool(*set_plugin_data)(int,void*);
/*:383*//*405:*/
#line 8905 "cweb/weaver.w"

struct interface*(*new_interface)(int,int,int,int,int,...);
/*:405*//*409:*/
#line 8953 "cweb/weaver.w"

bool(*destroy_interface)(struct interface*);
/*:409*//*413:*/
#line 9019 "cweb/weaver.w"

struct interface*(*copy_interface)(struct interface*);
/*:413*//*418:*/
#line 9117 "cweb/weaver.w"

void(*move_interface)(struct interface*,float,float);
/*:418*//*422:*/
#line 9196 "cweb/weaver.w"

void(*resize_interface)(struct interface*,float,float);
/*:422*//*426:*/
#line 9276 "cweb/weaver.w"

void(*rotate_interface)(struct interface*,float);
/*:426*//*495:*/
#line 11010 "cweb/weaver.w"

void(*change_resolution)(int,int);
/*:495*//*500:*/
#line 11044 "cweb/weaver.w"

void(*change_final_shader)(int);
/*:500*//*526:*/
#line 11354 "cweb/weaver.w"

bool(*select_sound_device)(int);
/*:526*//*530:*/
#line 11387 "cweb/weaver.w"

int(*current_sound_device)(void);
/*:530*//*564:*/
#line 12168 "cweb/weaver.w"

struct sound*(*new_sound)(char*);
/*:564*//*568:*/
#line 12200 "cweb/weaver.w"

void(*play_sound)(struct sound*);
/*:568*//*572:*/
#line 12244 "cweb/weaver.w"

void(*destroy_sound)(struct sound*);
/*:572*/
#line 2076 "cweb/weaver.w"

}W;
/*:75*/
#line 1973 "cweb/weaver.w"

/*327:*/
#line 7239 "cweb/weaver.w"

#include "plugins.h"
/*:327*//*360:*/
#line 8049 "cweb/weaver.w"

#if W_TARGET == W_WEB
#include "../../.hidden_code/header.h"
#endif
/*:360*/
#line 1974 "cweb/weaver.w"

/*324:*/
#line 7183 "cweb/weaver.w"


#define W_PLUGIN struct _weaver_struct *_W
#ifdef W_PLUGIN_CODE
#define W (*_W)
#endif
/*:324*/
#line 1975 "cweb/weaver.w"

#ifdef __cplusplus
}
#endif
#endif
/*:70*/
