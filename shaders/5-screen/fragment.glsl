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

varying mediump vec2 coordinate;

uniform sampler2D texture1;

vec3 mod289(vec3 x) {
  return x - floor(x * (1.0 / 289.0)) * 289.0;
}

vec4 mod289(vec4 x) {
  return x - floor(x * (1.0 / 289.0)) * 289.0;
}

vec4 permute(vec4 x) {
     return mod289(((x*34.0)+1.0)*x);
}

vec4 taylorInvSqrt(vec4 r)
{
  return 1.79284291400159 - 0.85373472095314 * r;
}

float snoise(vec3 v)
  { 
  const vec2  C = vec2(1.0/6.0, 1.0/3.0) ;
  const vec4  D = vec4(0.0, 0.5, 1.0, 2.0);

// First corner
  vec3 i  = floor(v + dot(v, C.yyy) );
  vec3 x0 =   v - i + dot(i, C.xxx) ;

// Other corners
  vec3 g = step(x0.yzx, x0.xyz);
  vec3 l = 1.0 - g;
  vec3 i1 = min( g.xyz, l.zxy );
  vec3 i2 = max( g.xyz, l.zxy );

  //   x0 = x0 - 0.0 + 0.0 * C.xxx;
  //   x1 = x0 - i1  + 1.0 * C.xxx;
  //   x2 = x0 - i2  + 2.0 * C.xxx;
  //   x3 = x0 - 1.0 + 3.0 * C.xxx;
  vec3 x1 = x0 - i1 + C.xxx;
  vec3 x2 = x0 - i2 + C.yyy; // 2.0*C.x = 1/3 = C.y
  vec3 x3 = x0 - D.yyy;      // -1.0+3.0*C.x = -0.5 = -D.y

// Permutations
  i = mod289(i); 
  vec4 p = permute( permute( permute( 
             i.z + vec4(0.0, i1.z, i2.z, 1.0 ))
           + i.y + vec4(0.0, i1.y, i2.y, 1.0 )) 
           + i.x + vec4(0.0, i1.x, i2.x, 1.0 ));

// Gradients: 7x7 points over a square, mapped onto an octahedron.
// The ring size 17*17 = 289 is close to a multiple of 49 (49*6 = 294)
  float n_ = 0.142857142857; // 1.0/7.0
  vec3  ns = n_ * D.wyz - D.xzx;

  vec4 j = p - 49.0 * floor(p * ns.z * ns.z);  //  mod(p,7*7)

  vec4 x_ = floor(j * ns.z);
  vec4 y_ = floor(j - 7.0 * x_ );    // mod(j,N)

  vec4 x = x_ *ns.x + ns.yyyy;
  vec4 y = y_ *ns.x + ns.yyyy;
  vec4 h = 1.0 - abs(x) - abs(y);

  vec4 b0 = vec4( x.xy, y.xy );
  vec4 b1 = vec4( x.zw, y.zw );

  //vec4 s0 = vec4(lessThan(b0,0.0))*2.0 - 1.0;
  //vec4 s1 = vec4(lessThan(b1,0.0))*2.0 - 1.0;
  vec4 s0 = floor(b0)*2.0 + 1.0;
  vec4 s1 = floor(b1)*2.0 + 1.0;
  vec4 sh = -step(h, vec4(0.0));

  vec4 a0 = b0.xzyw + s0.xzyw*sh.xxyy ;
  vec4 a1 = b1.xzyw + s1.xzyw*sh.zzww ;

  vec3 p0 = vec3(a0.xy,h.x);
  vec3 p1 = vec3(a0.zw,h.y);
  vec3 p2 = vec3(a1.xy,h.z);
  vec3 p3 = vec3(a1.zw,h.w);

//Normalise gradients
  vec4 norm = taylorInvSqrt(vec4(dot(p0,p0), dot(p1,p1), dot(p2, p2), dot(p3,p3)));
  p0 *= norm.x;
  p1 *= norm.y;
  p2 *= norm.z;
  p3 *= norm.w;

// Mix final noise value
  vec4 m = max(0.6 - vec4(dot(x0,x0), dot(x1,x1), dot(x2,x2), dot(x3,x3)), 0.0);
  m = m * m;
  return 42.0 * dot( m*m, vec4( dot(p0,x0), dot(p1,x1), 
                                dot(p2,x2), dot(p3,x3) ) );
  }

float default3DFbm(vec3 P, float frequency, float lacunarity, int octaves, float addition)
{
    float t = 0.0;
    float amplitude = 1.0;
    float amplitudeSum = 0.0;
    for(int k = 0; k < 5; ++k)
    {
        t += min(snoise(P * frequency)+addition, 1.0) * amplitude;
        amplitudeSum += amplitude;
        amplitude *= 0.5;
        frequency *= lacunarity;
    }
    return t/amplitudeSum;
}

float default3DFbm2(vec3 P, float frequency, float lacunarity,  float addition)
{
    float t = 0.0;
    float amplitude = 1.0;
    float amplitudeSum = 0.0;
    for(int k = 0; k < 2; ++k)
    {
        t += min(snoise(P * frequency)+addition, 1.0) * amplitude;
        amplitudeSum += amplitude;
        amplitude *= 0.5;
        frequency *= lacunarity;
    }
    return t/amplitudeSum;
}



float field(in vec3 p,float s,  int idx) {
   float strength = 7. + .03 * log(1.e-6 + fract(sin(time) * 4373.11));
   float accum = s/4.;
   float prev = 0.;
   float tw = 0.;
   for (int i = 0; i < 26; ++i) {
      float mag = dot(p, p);
      p = abs(p) / mag + vec3(-.5, -.4, -1.5);
      float w = exp(-float(i) / 7.);
      accum += w * exp(-strength * pow(abs(mag - prev), 2.2));
      tw += w;
      prev = mag;
   } 
   return max(0., 5. * accum / tw - .7);
}

vec3 nrand3( vec2 co ){
  vec3 a = fract( cos( co.x*8.3e-3 + co.y )*vec3(1.3e5, 4.7e5, 2.9e5) );
  vec3 b = fract( sin( co.x*0.3e-3 + co.y )*vec3(8.1e5, 1.0e5, 0.1e5) );
  vec3 c = mix(a, b, 0.5);
  return c;
}

vec2 move(vec2 g, vec2 p, float t){
  return sin( t * 2. + 9. * fract(sin((floor(g)+p)*mat2(2,7,2,5)*mat2(7,-2,2,5))));
}

float df(vec2 p, vec2 dir, float v)
{
    float a = atan(dir.x, dir.y);
    p *= mat2(cos(a), -sin(a), sin(a), cos(a));
    p *= 16.; p.y *= -0.75;
    float r = dot(p,p) * 0.02 * cos(length(vec2(p.x-dir.y, dir.x-p.y))*3.-time * (20.+4.*cos(time/4.7)))*v;
    p *= mat2(cos(r), -sin(r), sin(r), cos(r));
    return mix(max(abs(p.x)+p.y, abs(p.y*p.x)), length(p)*5., 0.04);
}

void main(){
  vec2 position = coordinate;
  vec4 color;
  if(integer == 3 || integer == 13){// Dancing screen
    position = position + vec2(0.03 * sin(time * 3.0), 0.03 * cos(time * 4.0));
  }
  else if(integer == 5 || integer == 15){ // Ondulating screen
    position.y = position.y + 0.25 * sin(sin(time) * 0.5 *
                                                (4.0 * position.x - 2.0));
  }
  else if(integer == 7 || integer == 17){ // Dancing deformation
    vec3 P = vec3(position, time / 5.0);
    position.x += 0.064 * default3DFbm2(P, 2.0, 2.0, 0.9) - 0.04;
    position.y += 0.064 * default3DFbm2(P, 2.0, 2.0, 0.9) - 0.04;
  }
  if(position.x >= 0.0 && position.x <= 1.0 &&
     position.y >= 0.0 && position.y <= 1.0)
    color = texture2D(texture1, position);
  else
    color = vec4(0.0, 0.0, 0.0, 0.0);
  if(integer >= 10 && vec3(color) == vec3(0.0, 0.0, 0.0)){
    vec2 surfacePosition = position;
    vec2 uv = surfacePosition;
    vec2 uvs = uv ;
    vec3 p = vec3(uvs / 4., 0) + vec3(1., -1.3, 0.);
    p += .2 * vec3(sin(time / 32.), sin(time / 24.),  sin(time / 256.));
    float freqs[4];
    freqs[0] = 0.05;
    freqs[1] = 0.3; 
    freqs[2] = 0.3;
    freqs[3] = 0.7; 
   
   float t = field(p,freqs[3], 26);
   float v = (1. - exp((abs(uv.x) - 1.) * 6.)) *
     (1. - exp((abs(uv.y) - 1.) * 6.));
   
   //Second Layer
   vec3 p2 = vec3(uvs / (4.+sin(time*0.055)*0.2+0.2+
                         sin(time*0.075)*0.3+0.4), 1.5) + vec3(2., -1.3, -1.);
   p2 += 0.25 * vec3(sin(time / 32.), sin(time / 24.),  sin(time / 256.));
   float t2 = field(p2,freqs[3], 18);
   vec4 c2 =  mix(.2, 0.2, v) * vec4(1.3 * t2 * t2 * t2 ,1.8  * t2 * t2 ,
                                     t2* freqs[0], t2);
    //Let's add some stars
   //Thanks to http://glsl.heroku.com/e#6904.0
   vec2 seed = p.xy * 2.0;   
   seed = floor(seed * object_size.x);
   vec3 rnd = nrand3( seed );
   vec4 starcolor = vec4(pow(rnd.y,20.0));
  
   //Second Layer
   vec2 seed2 = p2.xy * 3.0;
   seed2 = floor(seed2 * object_size.x);
   vec3 rnd2 = nrand3( seed2 );
   starcolor += vec4(pow(rnd2.y,40.0));
   color = mix(freqs[3]-.5, 1.,1.0) * vec4(1.5*freqs[2] * t * t* t , 1.2*freqs[1] * t * t, freqs[3]*t, 1.0) +c2+starcolor;
  }
  if(integer == 2 || integer == 12){// CLoud
    vec3 P = vec3(position, time / 5.0);
    float c;
    if(integer == 12)
      c = default3DFbm(P, 2.0, 2.0, 10, 0.6);
    else
      c = default3DFbm(P, 2.0, 2.0, 10, 0.9);
    color += vec4(c, c, c, c);
  }
  if(integer == 4 || integer == 14){// Poles
    vec4 poles;
    vec2 g = position * object_size * 1.5;
    float d = 15.;
    vec2 p = g /= object_size.y / d, ac,al;
    float adjust = default3DFbm2(vec3(position, time), 2.0, 2.0, 0.9);
    //vec3 adjust = nrand3(position);
    for(int x=-1;x<=1;x++)
      for(int y=-1;y<=1;y++){
        p = vec2(x,y),
          al = move(g,p, time-0.1),
          ac = move(g,p, time),
          p += .5 + .5 * ac - fract(g),
          d = min(d, df(p, ac-al, length(ac-move(g,p, time+0.1))*0.5));
      }
    poles = mix(vec4(1.0), vec4(1.,.98,.96,1.)*min(1., 1.2-0.2*length(0.1 * position)), d);
    if(distance(poles, vec4(1.0, 1.0, 1.0, 1.0)) < 0.09){
      color += poles;
      color.r = 0.3568 - 0.25 * adjust;
      color.g = 0.2902 - 0.25 * adjust;
      color.b = 0.0784 - 0.25 * adjust;
    }
  }
  else if(integer == 6 || integer == 16){
    float r = 0.0;
    float g = 0.0;
    float b = 0.0;
    float x = 0.;
    for(int i = 0; i < 25; i++) {
      x += float(i)*float(i)/64.;
      r += sin(x)*1.62/length(100.0*position-vec2(x-g*50.,50.*g*b*sin(time)+50.));
      g += cos(x)*1.62/length(100.0*position-vec2(x-r*50.,50.*r*b*cos(time)+50.));
      b += tan(x)*1.62/length(100.0*position-vec2(x+b*50.,50.*b*sin(time)+50.));
    }

    color = 0.25 * (color + 3.0*vec4(r, g, b, 1.0));
  }
  if(integer == 9 || integer == 19)
    color.r = color.g = color.b = (color.r + color.g + color.b) / 3.0;
  else if(integer == 20)
    color = vec4(1.0, 1.0, 1.0, 1.0);
  gl_FragData[0] = color;
}
 
