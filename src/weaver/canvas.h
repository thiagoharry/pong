/*240:*/
#line 5484 "cweb/weaver.w"

#ifndef _canvas_H_
#define _canvas_h_
#ifdef __cplusplus
extern"C"{
#endif
/*66:*/
#line 1910 "cweb/weaver.w"

#include "conf_begin.h"
#include "../../conf/conf.h"
#include "conf_end.h"
/*:66*/
#line 5490 "cweb/weaver.w"

#include "weaver.h"
#include <stdio.h>  
#include <stdlib.h>  
#include <SDL/SDL.h>  

void _initialize_canvas(void);
void _finalize_canvas(void);
/*249:*/
#line 5689 "cweb/weaver.w"

void _Wresize_window(int width,int height);
/*:249*//*255:*/
#line 5752 "cweb/weaver.w"

void _Wmove_window(int x,int y);
/*:255*/
#line 5498 "cweb/weaver.w"

#ifdef __cplusplus
}
#endif
#endif
/*:240*/
