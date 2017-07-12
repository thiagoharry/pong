/*436:*/
#line 9512 "cweb/weaver.w"

#ifndef _shaders_h_
#define _shaders_h_
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
#line 9519 "cweb/weaver.w"

/*444:*/
#line 9622 "cweb/weaver.w"

extern char _vertex_interface[];
extern char _fragment_interface[];
struct _shader _default_interface_shader;
/*:444*//*446:*/
#line 9639 "cweb/weaver.w"

GLuint _compile_shader(char*source,bool vertex);
#define _compile_vertex_shader(source) _compile_shader(source, true)
#define _compile_fragment_shader(source) _compile_shader(source, false)
/*:446*//*448:*/
#line 9686 "cweb/weaver.w"

GLuint _link_and_clean_shaders(GLuint vertex,GLuint fragment);
/*:448*//*453:*/
#line 9800 "cweb/weaver.w"

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
/*:453*//*458:*/
#line 10015 "cweb/weaver.w"

void _compile_and_insert_new_shader(char*dir,int position);
/*:458*//*487:*/
#line 10759 "cweb/weaver.w"

extern char _vertex_interface_texture[];
extern char _fragment_interface_texture[];
struct _shader _framebuffer_shader;
GLfloat _framebuffer_matrix[16];


int _custom_final_shader;
/*:487*//*493:*/
#line 10943 "cweb/weaver.w"

void _change_resolution(int resolution_x,int resolution_y);
/*:493*//*498:*/
#line 11031 "cweb/weaver.w"

void _change_final_shader(int type);
/*:498*/
#line 9520 "cweb/weaver.w"

#ifdef __cplusplus
}
#endif
#endif
/*:436*/
