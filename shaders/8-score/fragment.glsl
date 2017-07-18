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

varying vec2 position;

uniform sampler2D texture1;

const float D0 = float(0x00ff);
const float D1 = float(0x0081);
const float D2 = float(0x1177);
const float D3 = float(0x11e7);
const float D4 = float(0x1189);
const float D5 = float(0x11ee);
const float D6 = float(0x11fe);
const float D7 = float(0x008f);
const float D8 = float(0x11ff);
const float D9 = float(0x11ef);

float digit(float t){
  if(t == 0.0) {
    return D0;
  }
  else if(t == 1.0) {
    return D1;
  }
  else if(t == 2.0) {
    return D2;
  }
  else if(t == 3.0) {
    return D3;
  }
  else if(t == 4.0) {
    return D4;
  }
  else if(t == 5.0) {
    return D5;
  }
  else
    return 0.0;
}

//Checks if bit 'b' is set in number 'n'
bool bit(float n, float b){
  return mod(floor(n / exp2(floor(b))), 2.0) != 0.0;
}

//Distance to line p0,p1 at uv
float dseg(vec2 p0,vec2 p1,vec2 uv){
  vec2 dir = normalize(p1 - p0);
  uv = (uv - p0) * mat2(dir.x, dir.y,-dir.y, dir.x);
  return distance(uv, clamp(uv, vec2(0), vec2(distance(p0, p1), 0)));   
}

//Distance to the character defined in 'bits'
float dchar(float bits, vec2 uv){
  float d = 1e6;	
  float n = floor(bits);
  if(bits != 0.0){
    //Segment layout and checking.
    d = bit(n,  0.0) ? min(d, dseg(vec2( 0.500,  0.063), vec2( 0.500,  0.937), uv)) : d;
    d = bit(n,  1.0) ? min(d, dseg(vec2( 0.438,  1.000), vec2( 0.063,  1.000), uv)) : d;
    d = bit(n,  2.0) ? min(d, dseg(vec2(-0.063,  1.000), vec2(-0.438,  1.000), uv)) : d;
    d = bit(n,  3.0) ? min(d, dseg(vec2(-0.500,  0.937), vec2(-0.500,  0.062), uv)) : d;
    d = bit(n,  4.0) ? min(d, dseg(vec2(-0.500, -0.063), vec2(-0.500, -0.938), uv)) : d;
    d = bit(n,  5.0) ? min(d, dseg(vec2(-0.438, -1.000), vec2(-0.063, -1.000), uv)) : d;
    d = bit(n,  6.0) ? min(d, dseg(vec2( 0.063, -1.000), vec2( 0.438, -1.000), uv)) : d;
    d = bit(n,  7.0) ? min(d, dseg(vec2( 0.500, -0.938), vec2( 0.500, -0.063), uv)) : d;
    d = bit(n,  8.0) ? min(d, dseg(vec2( 0.063,  0.000), vec2( 0.438, -0.000), uv)) : d;
    d = bit(n,  9.0) ? min(d, dseg(vec2( 0.063,  0.063), vec2( 0.438,  0.938), uv)) : d;
    d = bit(n, 10.0) ? min(d, dseg(vec2( 0.000,  0.063), vec2( 0.000,  0.937), uv)) : d;
    d = bit(n, 11.0) ? min(d, dseg(vec2(-0.063,  0.063), vec2(-0.438,  0.938), uv)) : d;
    d = bit(n, 12.0) ? min(d, dseg(vec2(-0.438,  0.000), vec2(-0.063, -0.000), uv)) : d;
    d = bit(n, 13.0) ? min(d, dseg(vec2(-0.063, -0.063), vec2(-0.438, -0.938), uv)) : d;
    d = bit(n, 14.0) ? min(d, dseg(vec2( 0.000, -0.938), vec2( 0.000, -0.063), uv)) : d;
    d = bit(n, 15.0) ? min(d, dseg(vec2( 0.063, -0.063), vec2( 0.438, -0.938), uv)) : d;
  }
  return d;
}

void main(){
  if(integer < 10){
    if(integer == 0){
      if(position.y < - 0.3 || position.y > 0.3 || position.x > 0.25 ||
         position.x < - 0.25)
        gl_FragData[0] = vec4(1.0, 1.0, 1.0, 1.0);
      else
        gl_FragData[0] = vec4(0.0, 0.0, 0.0, 0.0);
    }
    else if(integer == 1){
      if(position.x > 0.25)
        gl_FragData[0] = vec4(1.0, 1.0, 1.0, 1.0);
      else
        gl_FragData[0] = vec4(0.0, 0.0, 0.0, 0.0);
    }
    else if(integer == 2){
      if(position.y < -0.3 || position.y > 0.3 ||
         (position.y > -0.1 && position.y < 0.1) ||
         (position.y > 0.1 && position.x > 0.25) ||
         (position.y < -0.1 && position.x < -0.25))
        gl_FragData[0] = vec4(1.0, 1.0, 1.0, 1.0);
      else
        gl_FragData[0] = vec4(0.0, 0.0, 0.0, 0.0);
    }
    else if(integer == 3){
      if(position.x > 0.25 || position.y < -0.3 || position.y > 0.3 ||
         (position.y > -0.1 && position.y < 0.1))
        gl_FragData[0] = vec4(1.0, 1.0, 1.0, 1.0);
      else
        gl_FragData[0] = vec4(0.0, 0.0, 0.0, 0.0);
    }
    else if(integer == 4){
      if(position.x > 0.25 || (position.y > -0.1 && position.y < 0.1) ||
         (position.y > 0.1 && position.x < -0.25))
        gl_FragData[0] = vec4(1.0, 1.0, 1.0, 1.0);
      else
        gl_FragData[0] = vec4(0.0, 0.0, 0.0, 0.0);
    }
    else if(integer == 5){
      if(position.y < -0.3 || position.y > 0.3 ||
         (position.y > -0.1 && position.y < 0.1) ||
         (position.y < -0.1 && position.x > 0.25) ||
         (position.y > 0.1 && position.x < -0.25))
        gl_FragData[0] = vec4(1.0, 1.0, 1.0, 1.0);
      else
        gl_FragData[0] = vec4(0.0, 0.0, 0.0, 0.0);
    }
    else{
      gl_FragData[0] = vec4(1.0, 1.0, 1.0, 1.0);
    } 
  }
  else{
    vec2 coord = (position + vec2(0.5, 0.5)) * object_size;
    vec2 p = 0.2 * ( coord / object_size.xy - 0.5 ) *
      object_size.xy / object_size.x;
    float d1 = floor(mod(time / 1.0, 10.0));
    vec2 p1 = p / 0.125;
    float d = dchar(digit(float(integer) - 10.0), p1) * 200.0;
    if(d > 10.0)
      d = 100000.0;
    gl_FragData[0] = vec4(vec3(0.0, 1.0, 0.0) / d, 1.0);
  }
}
 
