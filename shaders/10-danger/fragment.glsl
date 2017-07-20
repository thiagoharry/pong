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
  vec4 color;
  float dst, r, g, b;
  float pos_x = position.x - 0.5;
  float pos_y = position.y - 0.5;
  vec2 focus = vec2(0.5, 0.95);
  float adj;
  dst = distance(position, focus);
  pos_x *= pos_x;
  pos_y *= pos_y;
  color = vec4(0.0, 0.0, 0.0, 0.0);
  if(pos_x /0.0756 + pos_y / 0.1225 < 1.0){ // In the skull
    color = vec4(1.0 - dst, 1.0 - dst, 1.0 - dst, 1.0);
    // Eyes:
    dst = distance(position, vec2(0.35, 0.5));
    if(dst < 0.1)
      color = vec4(0.001, 0.001, 0.01, 1.0);
    else{
      dst = distance(position, vec2(0.65, 0.5));
      if(dst < 0.1)
        color = vec4(0.001, 0.001, 0.01, 1.0);
      else{
        // Nose
        dst = distance(position, vec2(0.5, 0.35));
        if(dst < 0.075)
          color = vec4(0.001, 0.001, 0.01, 1.0);
      }
    }  
  }
  dst = distance(position, vec2(0.0, 0.0));
  if(dst < 0.45)
    color = vec4(0.0, 0.0, 0.0, 0.0);
  dst = distance(position, vec2(1.0, 0.0));
  if(dst < 0.45)
    color = vec4(0.0, 0.0, 0.0, 0.0);
  if(color.a == 0.0 && position.x > position.y - 0.1 &&
     position.x < position.y + 0.1 && position.x > 0.1 && position.x < 0.9){
    if(position.x < position.y)
      adj = position.y - position.x;
    else
      adj = position.x - position.y;
    adj *= 3.0;
    color = vec4(0.8 - adj, 0.8 - adj, 0.8 - adj, 1.0);
  }
  if(color.a == 0.0 && 1.0 - position.x > position.y - 0.1 &&
     1.0 - position.x < position.y + 0.1 && position.x < 0.9 && position.x > 0.1){
    if(1.0 - position.x < position.y)
      adj = position.y - 1.0 + position.x;
    else
      adj = 1.0 - position.x - position.y;
    adj *= 3.0;
    color = vec4(0.8 - adj, 0.8 - adj, 0.8 - adj, 1.0);
  }

  gl_FragData[0] = color;
}
 
