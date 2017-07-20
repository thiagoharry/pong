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

varying vec2 position;

void main(){
  float scale = 1.0 + 0.5 * abs(sin(time * 4.0));
  mat4 size;
  size[1][1] = size[0][0] = scale;
  size[2][2] = size[3][3] = 1.0;
  size[0][1] = size[0][2] = size[0][3] = 0.0;
  size[1][0] = size[1][2] = size[1][3] = 0.0;
  size[2][0] = size[2][1] = size[2][3] = 0.0;
  size[3][0] = size[3][1] = size[3][2] = 0.0;
  gl_Position = model_view_matrix * size * vec4(vertex_position, 1.0);  
  position = vec2(vertex_position) + vec2(0.5, 0.5);
}


