/*440:*/
#line 9555 "cweb/weaver.w"


#version 100

#if GL_FRAGMENT_PRECISION_HIGH == 1
precision highp float;
precision highp int;
#else
precision mediump float;
precision mediump int;
#endif
precision lowp sampler2D;
precision lowp samplerCube;

/*442:*/
#line 9605 "cweb/weaver.w"

attribute vec3 vertex_position;
/*:442*/
#line 9569 "cweb/weaver.w"



/*443:*/
#line 9612 "cweb/weaver.w"

uniform vec4 object_color;
uniform mat4 model_view_matrix;
uniform vec2 object_size;
uniform float time;
uniform sampler2D texture1;
uniform int integer;
/*:443*/
#line 9572 "cweb/weaver.w"

void main(){

gl_Position= model_view_matrix*vec4(vertex_position,1.0);
}
/*:440*/
