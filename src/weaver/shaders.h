/*465:*/
#line 10189 "./cweb/weaver.w"

#ifndef _shaders_h_
#define _shaders_h_
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
#line 10196 "./cweb/weaver.w"

/*473:*/
#line 10299 "./cweb/weaver.w"

extern char _vertex_interface[];
extern char _fragment_interface[];
struct _shader _default_interface_shader;
/*:473*//*475:*/
#line 10316 "./cweb/weaver.w"

GLuint _compile_shader(char*source,bool vertex);
#define _compile_vertex_shader(source) _compile_shader(source, true)
#define _compile_fragment_shader(source) _compile_shader(source, false)
/*:475*//*477:*/
#line 10363 "./cweb/weaver.w"

GLuint _link_and_clean_shaders(GLuint vertex,GLuint fragment);
/*:477*//*482:*/
#line 10477 "./cweb/weaver.w"

struct _shader{
bool initialized;
GLuint program_shader;
char name[128];

GLint _uniform_object_color,_uniform_model_view,_uniform_object_size;
GLint _uniform_time,_uniform_texture1,_uniform_integer;

GLint _attribute_vertex_position;
char*vertex_source,*fragment_source;
#if W_TARGET == W_ELF


ino_t vertex_inode,fragment_inode;
#endif
};

#if W_TARGET == W_ELF


struct _shader*_shader_list;
#else


#include "../../.hidden_code/shader.h"
#endif
/*:482*//*487:*/
#line 10719 "./cweb/weaver.w"

void _compile_and_insert_new_shader(char*dir,int position);
/*:487*//*517:*/
#line 11510 "./cweb/weaver.w"

extern char _vertex_interface_texture[];
extern char _fragment_interface_texture[];
struct _shader _framebuffer_shader;
GLfloat _framebuffer_matrix[16];
/*:517*//*523:*/
#line 11694 "./cweb/weaver.w"

void _change_resolution(int resolution_x,int resolution_y);
/*:523*//*528:*/
#line 11790 "./cweb/weaver.w"

void _change_final_shader(int type);
/*:528*//*684:*/
#line 15333 "./cweb/weaver.w"

extern char _vertex_image_interface[];
extern char _fragment_image_interface[];
struct _shader _image_interface_shader;
/*:684*/
#line 10197 "./cweb/weaver.w"

#ifdef __cplusplus
}
#endif
#endif
/*:465*/
