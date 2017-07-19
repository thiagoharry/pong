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


attribute vec3 vertex_position;

uniform vec4 object_color;
uniform mat4 model_view_matrix;
uniform float time;
uniform vec2 object_size;
uniform int integer;

varying mediump vec2 coordinate;

void main(){
  mat4 size;
  if(integer == 1 || integer == 11)// Upside down screen 
    coordinate = vec2(vertex_position[0] + 0.5, 0.5 - vertex_position[1]);
  else
    coordinate = vec2(vertex_position[0] + 0.5, vertex_position[1] + 0.5);
  gl_Position = model_view_matrix * vec4(vertex_position, 1.0);

}
