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
  // P
  if(coordinate.x > 0.4 && coordinate.x < 0.413 &&
     coordinate.y < 0.9 && coordinate.y > 0.8){
    color = vec4(1.0, 1.0, 1.0, 1.0);
  }
  else if(coordinate.x >= 0.413 && coordinate.x < 0.426 &&
          coordinate.y < 0.9 && coordinate.y > 0.88){
    color = vec4(1.0, 1.0, 1.0, 1.0);
  }
  else if(coordinate.x >= 0.413 && coordinate.x < 0.426 &&
          coordinate.y < 0.86 && coordinate.y > 0.84){
    color = vec4(1.0, 1.0, 1.0, 1.0);
  }
  else if(coordinate.x >= 0.426 && coordinate.x < 0.439 &&
          coordinate.y < 0.88 && coordinate.y > 0.86){
    color = vec4(1.0, 1.0, 1.0, 1.0);
  }
  // O
  else if(coordinate.x >= 0.452 && coordinate.x < 0.465 &&
     coordinate.y < 0.9 && coordinate.y > 0.8){
    color = vec4(1.0, 1.0, 1.0, 1.0);
  }
  else if(coordinate.x >= 0.465 && coordinate.x < 0.478 &&
          coordinate.y < 0.9 && coordinate.y > 0.88){
    color = vec4(1.0, 1.0, 1.0, 1.0);
  }
  else if(coordinate.x >= 0.465 && coordinate.x < 0.478 &&
          coordinate.y < 0.82 && coordinate.y > 0.8){
    color = vec4(1.0, 1.0, 1.0, 1.0);
  }
  else if(coordinate.x >= 0.478 && coordinate.x < 0.491 &&
          coordinate.y < 0.9 && coordinate.y > 0.8){
    color = vec4(1.0, 1.0, 1.0, 1.0);
  }
  else{
    color = vec4(0.0, 0.0, 0.0, 0.0);
  }
  //if(coordinate.x > 0.4 && coordinate.x < 0.6 &&
  //   coordinate.y < 0.9 && coordinate.y > 0.8)
  //  color = vec4(1.0, 1.0, 1.0, 1.0);
  //else
  //  color = vec4(0.0, 0.0, 0.0, 0.0);
  gl_FragData[0] = color;
}
 
