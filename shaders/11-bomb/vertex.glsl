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
  gl_Position = model_view_matrix * vec4(vertex_position, 1.0);
  position = vec2(vertex_position) + vec2(0.5, 0.5);
}

