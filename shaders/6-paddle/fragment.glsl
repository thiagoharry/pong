#version 100

precision highp float;
precision highp int;
precision lowp sampler2D;
precision lowp samplerCube;

uniform vec4 object_color;

uniform float time;
uniform vec2 object_size;

uniform int integer;

uniform sampler2D texture1;

varying vec2 position;

#define TAU 6.28318530718
#define MAX_ITER 3

void main( void ) {
  float dist = distance(position, vec2(0.0, 0.0));
  float x_pos, y_pos;
  //for(x_pos = position.x + 0.5; x_pos > 0.0; x_pos -= 0.05);
  //for(y_pos = position.y + 0.5; y_pos > 0.0; y_pos -= 0.02);
  x_pos = position.x - 0.05 * float(int((position.x + 0.5) / 0.05));
  y_pos = position.y - 0.02 * float(int((position.y + 0.5) / 0.02)); 
  if((integer == 1 || integer == 11) &&
     abs(-0.05 - x_pos) > (0.05 * (40.0 / object_size.x))){
    gl_FragColor = vec4(0.0, 0.0, 0.0, 0.0);
  }
  else if((integer == 1 || integer == 11) &&
          abs(-0.02 - y_pos) > (0.05 * (80.0 / object_size.y))){
    gl_FragColor = vec4(0.0, 0.0, 0.0, 0.0);
  }
  else if(integer < 10)
    gl_FragColor =  vec4(1.0, 1.0, 1.0, 1.0);
  else if(dist > 0.502){
    gl_FragColor =  vec4(0.0, 0.0, 0.0, 0.0);
  }
  else if(dist > 0.48 || position.y > 0.3 || position.y < -0.3){
    float c = max((position.x + 0.2)*0.4, 0.125);
    gl_FragColor =  vec4(c, c, c, 1.0);
  }
  else{
    float gtime = time * .5+23.0;
    // uv should be the 0-1 uv of texture...
    vec2 uv = position;
    vec2 p = mod(uv*TAU, TAU)-250.0;
    vec2 i = vec2(p);
    float c = 1.0;
    float inten = .005;
    
    for (int n = 0; n < MAX_ITER; n++) {
      float t = gtime * (0.0 - (3.0 / float(n+1)));
      i = p + vec2(cos(t - i.x) + sin(t + i.y), sin(t - i.y) + cos(t + i.x));
      c += 1.0/length(vec2(p.x / (sin(i.x+t)/inten),p.y / (cos(i.y+t)/inten)));
    }
    c /= float(MAX_ITER);
    c = 1.17-pow(c, 1.4);
    vec3 colour = vec3(pow(abs(c), 8.0));
    colour = clamp(colour + vec3(object_color), 0.0, 1.0);
    
    gl_FragColor = vec4(colour, 1.0);
  }
}


//void main(){
//  mainImage(gl_FragColor, gl_FragCoord.xy);
//}
 
