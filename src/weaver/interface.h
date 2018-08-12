/*413:*/
#line 9084 "cweb/weaver.w"

#ifndef _interface_h_
#define _interface_h_
#ifdef __cplusplus
extern"C"{
#endif
#include "weaver.h"
/*66:*/
#line 1928 "cweb/weaver.w"

#include "conf_begin.h"
#include "../../conf/conf.h"
#include "conf_end.h"
/*:66*/
#line 9091 "cweb/weaver.w"

/*416:*/
#line 9122 "cweb/weaver.w"

struct interface{
int type;
int integer;

float x,y;
float rotation;
float r,g,b,a;
float height,width;
bool visible;

GLfloat _transform_matrix[16];

GLenum _mode;
/*663:*/
#line 14768 "cweb/weaver.w"


GLuint*_texture;
bool _loaded_texture;
bool animate;
unsigned number_of_frames;
unsigned current_frame;
unsigned*frame_duration;
unsigned long _t;
int max_repetition;
/*:663*/
#line 9136 "cweb/weaver.w"


#ifdef W_MULTITHREAD
pthread_mutex_t _mutex;
#endif
}_interfaces[W_MAX_SUBLOOP][W_MAX_INTERFACES];
#ifdef W_MULTITHREAD


pthread_mutex_t _interface_mutex;
#endif
/*:416*//*417:*/
#line 9155 "cweb/weaver.w"

#define W_NONE                 0
#define W_INTERFACE_SQUARE    -1
#define W_INTERFACE_PERIMETER -2
/*:417*//*420:*/
#line 9199 "cweb/weaver.w"

void _flush_interfaces(void);
/*:420*//*425:*/
#line 9271 "cweb/weaver.w"

GLfloat _interface_vertices[12];

GLuint _interface_VBO;

GLuint _interface_VAO;
/*:425*//*428:*/
#line 9328 "cweb/weaver.w"

struct interface*_new_interface(int type,int x,int y,int width,
int height,...);
/*:428*//*432:*/
#line 9432 "cweb/weaver.w"

bool _destroy_interface(struct interface*inter);
/*:432*//*436:*/
#line 9486 "cweb/weaver.w"

struct interface*_copy_interface(struct interface*inter);
/*:436*//*441:*/
#line 9549 "cweb/weaver.w"

void _move_interface(struct interface*,float x,float y);
/*:441*//*445:*/
#line 9641 "cweb/weaver.w"

void _resize_interface(struct interface*inter,float size_x,float size_y);
/*:445*//*449:*/
#line 9720 "cweb/weaver.w"

void _rotate_interface(struct interface*inter,float rotation);
/*:449*//*456:*/
#line 9942 "cweb/weaver.w"

void _update_interface_screen_size(void);
/*:456*//*486:*/
#line 10773 "cweb/weaver.w"

struct interface*_interface_queue[W_MAX_SUBLOOP][W_MAX_INTERFACES];
/*:486*//*488:*/
#line 10800 "cweb/weaver.w"

void _insert_interface_queue(struct interface*inter);
/*:488*//*490:*/
#line 10848 "cweb/weaver.w"

void _remove_interface_queue(struct interface*inter);
/*:490*//*492:*/
#line 10917 "cweb/weaver.w"

void _clean_interface_queue(void);
/*:492*//*668:*/
#line 14837 "cweb/weaver.w"

#define W_INTERFACE_IMAGE -3
/*:668*//*674:*/
#line 15059 "cweb/weaver.w"

void _finalize_interface_texture(void*);
/*:674*//*690:*/
#line 15435 "cweb/weaver.w"

#if !defined(W_DISABLE_PNG) && (W_TARGET == W_ELF)
GLuint*_extract_png(char*,unsigned*,unsigned**,int*,bool*);
#endif
/*:690*/
#line 9092 "cweb/weaver.w"

#ifdef __cplusplus
}
#endif
#endif
/*:413*/
