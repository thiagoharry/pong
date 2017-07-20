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

uniform vec4 object_color;

uniform float time;
uniform vec2 object_size;
uniform int integer;

uniform sampler2D texture1;

varying vec2 position;

void main(){
  vec4 color = vec4(0.0, 0.0, 0.0, 0.0);
  float dst, r, g, b;
  if(position.x < 0.4 || position.x > 0.6)
    color = vec4(0.0, 0.0, 0.0, 0.0);
  else if(position.y > 0.9)
    color = vec4(0.8745, 0.4314, 0.1176, 1.0);
  else if(position.y > 0.75)
    color = vec4(0.75, 0.75, 0.75, 1.0);
  else if(position.y > 0.2)
    color = vec4(sin(time), cos(time * 0.5 + 0.25), position.x * 0.5, 1.0);
  else if(position.y > 0.1)
    color = vec4(0.9569, 0.8941, 0.8235, 1.0);
  else{
    if(position.x < 0.45 || position.x > 0.55)
      color = vec4(0.0, 0.0, 0.0, 0.0);
    else if(position.y > 0.05)
      color = vec4(0.9569, 0.8941, 0.8235, 1.0);
    else
      color = vec4(sin(time), cos(time * 0.5 + 0.25), position.x * 0.5, 1.0);
  }
    gl_FragData[0] = color;
}


