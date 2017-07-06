/*387:*/
#line 8574 "cweb/weaver.w"

#ifndef _interface_h_
#define _interface_h_
#ifdef __cplusplus
extern"C"{
#endif
#include "weaver.h"
/*66:*/
#line 1910 "cweb/weaver.w"

#include "conf_begin.h"
#include "../../conf/conf.h"
#include "conf_end.h"
/*:66*/
#line 8581 "cweb/weaver.w"

/*390:*/
#line 8606 "cweb/weaver.w"

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
/*:390*//*391:*/
#line 8640 "cweb/weaver.w"

#define W_NONE                 0
#define W_INTERFACE_SQUARE    -1
#define W_INTERFACE_PERIMETER -2
/*:391*//*394:*/
#line 8684 "cweb/weaver.w"

void _flush_interfaces(void);
/*:394*//*399:*/
#line 8756 "cweb/weaver.w"

GLfloat _interface_vertices[12];

GLuint _interface_VBO;

GLuint _interface_VAO;
/*:399*//*402:*/
#line 8813 "cweb/weaver.w"

struct interface*_new_interface(int type,int x,int y,int width,
int height,...);
/*:402*//*406:*/
#line 8911 "cweb/weaver.w"

bool _destroy_interface(struct interface*inter);
/*:406*//*410:*/
#line 8965 "cweb/weaver.w"

struct interface*_copy_interface(struct interface*inter);
/*:410*//*415:*/
#line 9028 "cweb/weaver.w"

void _move_interface(struct interface*,float x,float y);
/*:415*//*419:*/
#line 9120 "cweb/weaver.w"

void _resize_interface(struct interface*inter,float size_x,float size_y);
/*:419*//*423:*/
#line 9199 "cweb/weaver.w"

void _rotate_interface(struct interface*inter,float rotation);
/*:423*//*430:*/
#line 9421 "cweb/weaver.w"

void _update_interface_screen_size(void);
/*:430*//*460:*/
#line 10238 "cweb/weaver.w"

struct interface*_interface_queue[W_MAX_SUBLOOP][W_MAX_INTERFACES];
/*:460*//*462:*/
#line 10265 "cweb/weaver.w"

void _insert_interface_queue(struct interface*inter);
/*:462*//*464:*/
#line 10313 "cweb/weaver.w"

void _remove_interface_queue(struct interface*inter);
/*:464*//*466:*/
#line 10382 "cweb/weaver.w"

void _clean_interface_queue(void);
/*:466*/
#line 8582 "cweb/weaver.w"

#ifdef __cplusplus
}
#endif
#endif
/*:387*/
