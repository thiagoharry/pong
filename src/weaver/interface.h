/*417:*/
#line 9225 "./cweb/weaver.w"

#ifndef _interface_h_
#define _interface_h_
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
#line 9232 "./cweb/weaver.w"

/*420:*/
#line 9263 "./cweb/weaver.w"

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
/*667:*/
#line 14933 "./cweb/weaver.w"


GLuint*_texture;
bool _loaded_texture;
bool animate;
unsigned number_of_frames;
unsigned current_frame;
unsigned*frame_duration;
unsigned long _t;
int max_repetition;
/*:667*/
#line 9277 "./cweb/weaver.w"


#ifdef W_MULTITHREAD
pthread_mutex_t _mutex;
#endif
}_interfaces[W_MAX_SUBLOOP][W_MAX_INTERFACES];
#ifdef W_MULTITHREAD


pthread_mutex_t _interface_mutex;
#endif
/*:420*//*421:*/
#line 9296 "./cweb/weaver.w"

#define W_NONE                 0
#define W_INTERFACE_SQUARE    -1
#define W_INTERFACE_PERIMETER -2
/*:421*//*424:*/
#line 9340 "./cweb/weaver.w"

void _flush_interfaces(void);
/*:424*//*429:*/
#line 9418 "./cweb/weaver.w"

GLfloat _interface_vertices[12];

GLuint _interface_VBO;

GLuint _interface_VAO;
/*:429*//*432:*/
#line 9475 "./cweb/weaver.w"

struct interface*_new_interface(int type,int x,int y,int width,
int height,...);
/*:432*//*436:*/
#line 9579 "./cweb/weaver.w"

bool _destroy_interface(struct interface*inter);
/*:436*//*440:*/
#line 9633 "./cweb/weaver.w"

struct interface*_copy_interface(struct interface*inter);
/*:440*//*445:*/
#line 9696 "./cweb/weaver.w"

void _move_interface(struct interface*,float x,float y);
/*:445*//*449:*/
#line 9788 "./cweb/weaver.w"

void _resize_interface(struct interface*inter,float size_x,float size_y);
/*:449*//*453:*/
#line 9867 "./cweb/weaver.w"

void _rotate_interface(struct interface*inter,float rotation);
/*:453*//*460:*/
#line 10089 "./cweb/weaver.w"

void _update_interface_screen_size(void);
/*:460*//*490:*/
#line 10946 "./cweb/weaver.w"

struct interface*_interface_queue[W_MAX_SUBLOOP][W_MAX_INTERFACES];
/*:490*//*492:*/
#line 10973 "./cweb/weaver.w"

void _insert_interface_queue(struct interface*inter);
/*:492*//*494:*/
#line 11021 "./cweb/weaver.w"

void _remove_interface_queue(struct interface*inter);
/*:494*//*496:*/
#line 11090 "./cweb/weaver.w"

void _clean_interface_queue(void);
/*:496*//*672:*/
#line 15002 "./cweb/weaver.w"

#define W_INTERFACE_IMAGE -3
/*:672*//*678:*/
#line 15224 "./cweb/weaver.w"

void _finalize_interface_texture(void*);
/*:678*//*694:*/
#line 15600 "./cweb/weaver.w"

#if !defined(W_DISABLE_PNG) && (W_TARGET == W_ELF)
GLuint*_extract_png(char*,unsigned*,unsigned**,int*,bool*);
#endif
/*:694*/
#line 9233 "./cweb/weaver.w"

#ifdef __cplusplus
}
#endif
#endif
/*:417*/
