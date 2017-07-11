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

varying mediump vec2 coordinate;

void main(){
  vec4 color;
  if(coordinate.y > 0.8){
    if(coordinate.x < 0.2)
      color = vec4(1.0, 1.0, 1.0, 1.0);
    else if(coordinate.x < 0.266)
      color = vec4(0.0, 0.0, 0.0, 0.0);
    else if(coordinate.x < 0.333)
      color = vec4(1.0, 1.0, 1.0, 1.0);
    else if(coordinate.x < 0.399)
      color = vec4(0.0, 0.0, 0.0, 0.0);
    else if(coordinate.x < 0.466)
      color = vec4(1.0, 1.0, 1.0, 1.0);
    else if(coordinate.x < 0.599)
      color = vec4(0.0, 0.0, 0.0, 0.0);
    else if(coordinate.x < 0.666)
      color = vec4(1.0, 1.0, 1.0, 1.0);
    else if(coordinate.x < 0.799)
      color = vec4(0.0, 0.0, 0.0, 0.0);
    else
      color = vec4(1.0, 1.0, 1.0, 1.0);
  }
  else if(coordinate.y > 0.6){
    if(coordinate.x < 0.066)
      color = vec4(1.0, 1.0, 1.0, 1.0);
    else if(coordinate.x < 0.333)
      color = vec4(0.0, 0.0, 0.0, 0.0);
    else if(coordinate.x < 0.399)
      color = vec4(1.0, 1.0, 1.0, 1.0);
    else if(coordinate.x < 0.599)
      color = vec4(0.0, 0.0, 0.0, 0.0);
    else if(coordinate.x < 0.666)
      color = vec4(1.0, 1.0, 1.0, 1.0);
    else if(coordinate.x < 0.866)
      color = vec4(0.0, 0.0, 0.0, 0.0);
    else if(coordinate.x < 0.933)
      color = vec4(1.0, 1.0, 1.0, 1.0);
    else
      color = vec4(0.0, 0.0, 0.0, 0.0);
  }
  else if(coordinate.y > 0.4){
    if(coordinate.x < 0.133)
      color = vec4(1.0, 1.0, 1.0, 1.0);
    else if(coordinate.x < 0.333)
      color = vec4(0.0, 0.0, 0.0, 0.0);
    else if(coordinate.x < 0.399)
      color = vec4(1.0, 1.0, 1.0, 1.0);
    else if(coordinate.x < 0.599)
      color = vec4(0.0, 0.0, 0.0, 0.0);
    else if(coordinate.x < 0.666)
      color = vec4(1.0, 1.0, 1.0, 1.0);
    else if(coordinate.x < 0.866)
      color = vec4(0.0, 0.0, 0.0, 0.0);
    else if(coordinate.x < 0.933)
      color = vec4(1.0, 1.0, 1.0, 1.0);
    else
      color = vec4(0.0, 0.0, 0.0, 0.0);
  }
  else if(coordinate.y > 0.2){
    if(coordinate.x < 0.066)
      color = vec4(1.0, 1.0, 1.0, 1.0);
    else if(coordinate.x < 0.266)
      color = vec4(0.0, 0.0, 0.0, 0.0);
    else if(coordinate.x < 0.333)
      color = vec4(1.0, 1.0, 1.0, 1.0);
    else if(coordinate.x < 0.399)
      color = vec4(0.0, 0.0, 0.0, 0.0);
    else if(coordinate.x < 0.466)
      color = vec4(1.0, 1.0, 1.0, 1.0);
    else if(coordinate.x < 0.599)
      color = vec4(0.0, 0.0, 0.0, 0.0);
    else if(coordinate.x < 0.666)
      color = vec4(1.0, 1.0, 1.0, 1.0);
    else if(coordinate.x < 0.866)
      color = vec4(0.0, 0.0, 0.0, 0.0);
    else if(coordinate.x < 0.933)
      color = vec4(1.0, 1.0, 1.0, 1.0);
    else
      color = vec4(0.0, 0.0, 0.0, 0.0);
  }
  else{
    if(coordinate.x < 0.199)
      color = vec4(1.0, 1.0, 1.0, 1.0);
    else if(coordinate.x < 0.266)
      color = vec4(0.0, 0.0, 0.0, 0.0);
    else if(coordinate.x < 0.333)
      color = vec4(1.0, 1.0, 1.0, 1.0);
    else if(coordinate.x < 0.399)
      color = vec4(0.0, 0.0, 0.0, 0.0);
    else if(coordinate.x < 0.466)
      color = vec4(1.0, 1.0, 1.0, 1.0);
    else if(coordinate.x < 0.599)
      color = vec4(0.0, 0.0, 0.0, 0.0);
    else if(coordinate.x < 0.666)
      color = vec4(1.0, 1.0, 1.0, 1.0);
    else if(coordinate.x < 0.866)
      color = vec4(0.0, 0.0, 0.0, 0.0);
    else if(coordinate.x < 0.933)
      color = vec4(1.0, 1.0, 1.0, 1.0);
    else
      color = vec4(0.0, 0.0, 0.0, 0.0);
  }
  gl_FragData[0] = color;
}
 
