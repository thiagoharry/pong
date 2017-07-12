/*388:*/
#line 8584 "cweb/weaver.w"

#ifndef _interface_h_
#define _interface_h_
#ifdef __cplusplus
extern"C"{
#endif
#include "weaver.h"
/*66:*/
#line 1911 "cweb/weaver.w"

#include "conf_begin.h"
#include "../../conf/conf.h"
#include "conf_end.h"
/*:66*/
#line 8591 "cweb/weaver.w"

/*391:*/
#line 8616 "cweb/weaver.w"

struct interface{
int type;
int integer;

float x,y;
float rotation;
float r,g,b,a;
float height,width;
bool visible;
bool stretch_x,stretch_y;


GLfloat _transform_matrix[16];

GLenum _mode;

#ifdef W_MULTITHREAD
pthread_mutex_t _mutex;
#endif
}_interfaces[W_MAX_SUBLOOP][W_MAX_INTERFACES];
#ifdef W_MULTITHREAD


pthread_mutex_t _interface_mutex;
#endif
/*:391*//*392:*/
#line 8650 "cweb/weaver.w"

#define W_NONE                 0
#define W_INTERFACE_SQUARE    -1
#define W_INTERFACE_PERIMETER -2
/*:392*//*395:*/
#line 8694 "cweb/weaver.w"

void _flush_interfaces(void);
/*:395*//*400:*/
#line 8766 "cweb/weaver.w"

GLfloat _interface_vertices[12];

GLuint _interface_VBO;

GLuint _interface_VAO;
/*:400*//*403:*/
#line 8823 "cweb/weaver.w"

struct interface*_new_interface(int type,int x,int y,int width,
int height,...);
/*:403*//*407:*/
#line 8921 "cweb/weaver.w"

bool _destroy_interface(struct interface*inter);
/*:407*//*411:*/
#line 8975 "cweb/weaver.w"

struct interface*_copy_interface(struct interface*inter);
/*:411*//*416:*/
#line 9038 "cweb/weaver.w"

void _move_interface(struct interface*,float x,float y);
/*:416*//*420:*/
#line 9130 "cweb/weaver.w"

void _resize_interface(struct interface*inter,float size_x,float size_y);
/*:420*//*424:*/
#line 9209 "cweb/weaver.w"

void _rotate_interface(struct interface*inter,float rotation);
/*:424*//*431:*/
#line 9431 "cweb/weaver.w"

void _update_interface_screen_size(void);
/*:431*//*461:*/
#line 10248 "cweb/weaver.w"

struct interface*_interface_queue[W_MAX_SUBLOOP][W_MAX_INTERFACES];
/*:461*//*463:*/
#line 10275 "cweb/weaver.w"

void _insert_interface_queue(struct interface*inter);
/*:463*//*465:*/
#line 10323 "cweb/weaver.w"

void _remove_interface_queue(struct interface*inter);
/*:465*//*467:*/
#line 10392 "cweb/weaver.w"

void _clean_interface_queue(void);
/*:467*/
#line 8592 "cweb/weaver.w"

#ifdef __cplusplus
}
#endif
#endif
/*:388*/
