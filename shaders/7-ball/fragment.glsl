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
  vec2 resolution = object_size;
  float dist = distance(position, vec2(0.0, 0.0));
  if(integer == 0)
    gl_FragData[0] = vec4(1.0, 1.0, 1.0, 1.0);
  else if(dist >= 0.49){
    gl_FragData[0] = vec4(0.0, 0.0, 0.0, 0.0);
  }
  else if(dist < 0.025){
    gl_FragData[0] = vec4(1.0, 1.0, 1.0, 0.25);
  }
  else{
    vec2 uv = (position*40.0)/resolution.y-vec2(-0.25, 0.0);
    float intensity = 0.;
    for (float i = 0.; i < 54.; i++) {
      float angle = i/27. * 3.14159;
      vec2 xy = uv + vec2(0.6 * cos(angle) - 0.25, 0.6 * sin(angle));
      vec2 xy2 = uv + vec2(0.4 * cos(angle) - 0.25, 0.4 * sin(angle));
      vec2 xy3 = uv + vec2(0.2 * cos(angle) - 0.25, 0.2 * sin(angle));
      intensity += pow(1000000., (0.77 - length(xy) * 1.9) * (1. + 0.275 * fract(-i / 17. - time))) / 40000.;
      intensity += pow(1000000., (0.77 - length(xy2) * 1.9) * (1. + 0.275 * fract(-i / 17. + time/1.5))) / 60000.;
      intensity += pow(1000000., (0.77 - length(xy3) * 1.9) * (1. + 0.275 * fract(-i / 17. - time))) / 80000.;
    }
    gl_FragData[0] = vec4(clamp(intensity * vec3(0.2, 0.1, 0.6), vec3(0.), vec3(1.)), 1.);
  }
}
 
