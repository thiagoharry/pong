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
  float dst;
  vec4 color = vec4(0.0, 0.0, 0.0, 0.0);
  vec2 fuse = vec2(0.8, 0.725);
  int draw = 0, p = 0;
  for(float x = 0.0; x < 1.0; x += 0.05)
    for(float y = 0.0; y < 1.0 ; y += 0.05)
      if(distance(vec2(float(x), float(y)), position) <=
         1.0/object_size.x)
        draw = 1;
  if(draw == 0){
    color = vec4(0.0, 0.0, 0.0, 0.0);
  }
  else{
    dst = distance(position, vec2(0.45, 0.425));
    if(dst < 0.375)
      color = vec4(0.1294, 0.2549, 0.3529,1.0);
    if(position.y > 0.85 && position.y <= 0.9 &&
       position.x <= 0.8 && position.x > 0.75) // Line 3
      color = vec4 (0.8784313725490196, 0.03529411764705882, 0.0, 1.0);
    else if(position.y > 0.75 && position.y <= 0.85){ // Line 4 and 5
      if(position.x <= 0.75 && position.x > 0.7)
        color = vec4 (0.8823529411764706, 0.09019607843137255, 0.0, 1.0);
      else if(position.x <= 0.8 && position.x > 0.75)
        color = vec4 (1.0, 0.6588235294117647, 0.00784313725490196, 1.0);
      else if(position.x <= 0.85 && position.x > 0.8)
        color = vec4 (0.8941176470588236, 0.1450980392156863, 0.0, 1.0);
    }
    else if(position.y > 0.7 && position.y <= 0.75){ // Linha 6
      if(position.x <= 0.75 && position.x > 0.65)
        color = vec4 (0.6470588235294118, 0.49019607843137253, 0.23921568627450981, 1.0);
      else if(position.x <= 0.8 && position.x > 0.75)
        color = vec4 (0.9058823529411765, 0.043137254901960784, 0.0, 1.0);
    }
    else if(position.y > 0.65 && position.y <= 0.7){ // Linha 7
      if(position.x <= 0.7 && position.x > 0.6)
        color = vec4 (0.6470588235294118, 0.49019607843137253, 0.23921568627450981, 1.0);
    }
  }
  dst = distance(position, fuse);
  color /= dst + 0.25 * abs(sin(time * 2.5));
  //color.g *= 1.05 * dst;
  gl_FragData[0] = color;
}
 

 
