/*623:*/
#line 13318 "./cweb/weaver.w"

#ifndef _gif_h_
#define _gif_h_
#ifdef __cplusplus
extern"C"{
#endif
#include "weaver.h"
/*66:*/
#line 1950 "./cweb/weaver.w"

#include "conf_begin.h"
#include "../../conf/conf.h"
#include "conf_end.h"
/*:66*/
#line 13325 "./cweb/weaver.w"

/*627:*/
#line 13346 "./cweb/weaver.w"

GLuint*_extract_gif(char*,unsigned*,unsigned**,int*,bool*);
/*:627*//*644:*/
#line 14078 "./cweb/weaver.w"

struct _image_list{
unsigned char*rgba_image;
unsigned delay_time;
unsigned x_offset,y_offset,width,height;
int disposal_method;

struct _image_list*next,*prev;
};
/*:644*/
#line 13326 "./cweb/weaver.w"

#ifdef __cplusplus
}
#endif
#endif
/*:623*/
