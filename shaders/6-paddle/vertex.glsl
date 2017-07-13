#version 100

precision highp float;
precision highp int;
precision lowp sampler2D;
precision lowp samplerCube;

attribute vec3 vertex_position;

uniform vec4 object_color;
uniform mat4 model_view_matrix;
uniform float time;
uniform vec2 object_size;

varying vec2 position;

void main(){
  position = vec2(vertex_position);
  gl_Position = model_view_matrix * vec4(vertex_position, 1.0);
}
