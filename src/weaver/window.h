/*214:*/
#line 5035 "cweb/weaver.w"

#ifndef _window_h_
#define _window_h_
#ifdef __cplusplus
extern"C"{
#endif
/*66:*/
#line 1911 "cweb/weaver.w"

#include "conf_begin.h"
#include "../../conf/conf.h"
#include "conf_end.h"
/*:66*/
#line 5041 "cweb/weaver.w"

#include "weaver.h"
#include "memory.h"
#include <signal.h> 
#include <stdio.h>  
#include <stdlib.h>  
#include <X11/Xlib.h>  




#include <GL/gl.h> 
#include <GL/glx.h>  
#include <X11/extensions/Xrandr.h>  




#include <X11/XKBlib.h>  
void _initialize_window(void);
void _finalize_window(void);
/*235:*/
#line 5411 "cweb/weaver.w"

typedef GLXContext
(*glXCreateContextAttribsARBProc)(Display*,GLXFBConfig,GLXContext,Bool,
const int*);
/*:235*//*247:*/
#line 5664 "cweb/weaver.w"

void _Wresize_window(int width,int height);
/*:247*//*253:*/
#line 5733 "cweb/weaver.w"

void _Wmove_window(int x,int y);
/*:253*/
#line 5062 "cweb/weaver.w"

#ifdef __cplusplus
}
#endif
#endif
/*:214*/
