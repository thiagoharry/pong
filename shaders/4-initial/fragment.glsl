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

#define RAY_STEPS 60
#define SHADOW_STEPS 12
#define LIGHT_COLOR vec3(.85,.9,1.)
#define AMBIENT_COLOR vec3(.3,.9,1.)
#define FLOOR_COLOR vec3(1.,.7,.9)
#define ENERGY_COLOR vec3(1.,.7,.4)
#define BRIGHTNESS .9
#define GAMMA 2.1
#define SATURATION .9

#define detail .00005
#define t time

vec3 lightdir=normalize(vec3(0.8,-0.3,-1.));
vec3 ambdir=normalize(vec3(0.,0.,1.));
const vec3 origin=vec3(0.,3.11,0.);
vec3 energy=vec3(0.01);
float vibration=0.;
float det=0.0;
vec3 pth1;

float fnoo() {
  return sin(time) * 0.5 + 0.5;
}

vec2 de(vec3 pos) {
  float hid=0.;
  vec3 tpos=pos;
  tpos.xz=abs(.5-mod(tpos.xz,1.));
  vec4 p=vec4(tpos,1.);
  float y=max(0.,.35-abs(pos.y-3.35))/.35;
  for (int i=0; i<7; i++) {//LOWERED THE ITERS
    p.xyz = abs(p.xyz)-vec3(-0.02,1.98,-0.02);
    p=p*(2.0+vibration*y)/clamp(dot(p.xyz,p.xyz),.4,1.)-vec4(0.5,1.,0.4,0.);
    p.xz*=mat2(-0.416*fnoo(),-0.91,0.91,-0.416*fnoo());
  }
  float fl=pos.y-3.013;
  float fr=(length(max(abs(p.xyz)-vec3(0.1,5.0,0.1),vec3(0.0)))-0.05)/p.w;//RETURN A RRECT
  //float fr=length(p.xyz)/p.w;
  float d=min(fl,fr);
  d=min(d,-pos.y+3.95);
  if (abs(d-fl)<.001) hid=1.;
  return vec2(d,hid);
}


float calcAO( const vec3 pos, const vec3 nor ) {
  float aodet=detail*40.;
  float totao = 0.0;
  float sca = 14.0;
  for( int aoi=0; aoi<5; aoi++ ) {
    float hr = aodet*float(aoi*aoi);
    vec3 aopos =  nor * hr + pos;
    float dd = de( aopos ).x;
    totao += -(dd-hr)*sca;
    sca *= 0.7;
  }
  return clamp( 1.0 - 5.0*totao, 0., 1.0 );
}

vec3 path(float ti){
  return vec3(sin(ti),.3-sin(ti*.632)*.3,cos(ti*.5))*.5;
}

mat2 rot(float a) {
  return mat2(cos(a),sin(a),-sin(a),cos(a));	
}



vec3 normal(vec3 p) {
  vec3 e = vec3(0.0,det,0.0);
  
  return normalize(vec3(
			de(p+e.yxx).x-de(p-e.yxx).x,
			de(p+e.xyx).x-de(p-e.xyx).x,
			de(p+e.xxy).x-de(p-e.xxy).x
			)
                   );	
}

float Sphere(vec3 p, vec3 rd, float r){//A RAY TRACED SPHERE
  float b = dot( -p, rd );
  float inner = b * b - dot( p, p ) + r * r;
  if( inner < 0.0 ) return -1.0;
  return b - sqrt( inner );
}



float texture(vec3 p) {
  p=abs(.5-fract(p*10.));
  vec3 c=vec3(3.);
  float es, l=es=0.;
  for (int i = 0; i < 10; i++) { 
    p = abs(p + c) - abs(p - c) - p; 
    p/= clamp(dot(p, p), .0, 1.);
    p = p* -1.5 + c;
    if ( mod(float(i), 2.) < 1. ) { 
      float pl = l;
      l = length(p);
      es+= exp(-1. / abs(l - pl));
    }
  }
  return es;
}

vec3 light(in vec3 p, in vec3 dir, in vec3 n, in float hid) {//PASSING IN THE NORMAL
#ifdef ENABLE_HARD_SHADOWS
  float sh=shadow(p, lightdir);
#else
  float sh=calcAO(p,-2.5*lightdir);//USING AO TO MAKE VERY SOFT SHADOWS
#endif
  float ao=calcAO(p,n);
  float diff=max(0.,dot(lightdir,-n))*sh;
  float y=3.35-p.y;
  vec3 amb=max(.5,dot(dir,-n))*.5*AMBIENT_COLOR;
  if (hid<.5) {
    amb+=max(0.2,dot(vec3(0.,1.,0.),-n))*FLOOR_COLOR*pow(max(0.,.2-abs(3.-p.y))/.2,1.5)*2.;
    amb+=energy*pow(max(0.,.4-abs(y))/.4,2.)*max(0.2,dot(vec3(0.,-sign(y),0.),-n))*2.;
  }
  vec3 r = reflect(lightdir,n);
  float spec=pow(max(0.,dot(dir,-r))*sh,10.);
  vec3 col;
  float energysource=pow(max(0.,.04-abs(y))/.04,4.)*2.;
  if (hid>1.5) {col=vec3(1.); spec=spec*spec;}
  else{
    float k=texture(p)*.23+.2; 
    k=min(k,1.5-energysource);
    col=mix(vec3(k,k*k,k*k*k),vec3(k),.3);
    if (abs(hid-1.)<.001) col*=FLOOR_COLOR*1.3;
  }
  col=col*(amb+diff*LIGHT_COLOR)+spec*LIGHT_COLOR;	
  if (hid<.5) { 
    col=max(col,energy*2.*energysource);
  }
  col*=min(1.,ao+length(energy)*.5*max(0.,.1-abs(y))/.1);
  return col;
}

vec3 raymarch(in vec3 from, in vec3 dir){
  float ey=mod(t*.5,1.);
  float glow,eglow,ref,sphdist,totdist=glow=eglow=ref=sphdist=0.;
  vec2 d=vec2(1.,0.);
  vec3 p, col=vec3(0.);
  vec3 origdir=dir,origfrom=from,sphNorm;
	
  //FAKING THE SQUISHY BALL BY MOVING A RAY TRACED BALL
  vec3 wob=cos(dir*500.0*length(from-pth1)+(from-pth1)*250.+time*10.)*0.0005;
  float t1=Sphere(from-pth1+wob,dir,0.015);
  float tg=Sphere(from-pth1+wob,dir,0.02);
  if(t1>0.){
    ref=1.0;from+=t1*dir;sphdist=t1;
    sphNorm=normalize(from-pth1+wob);
    dir=reflect(dir,sphNorm);
  } 
  else if (tg>0.) { 
    vec3 sphglowNorm=normalize(from+tg*dir-pth1+wob);
    glow+=pow(max(0.,dot(sphglowNorm,-dir)),5.);
  };
  
  for (int i=0; i<RAY_STEPS; i++) {
    if (d.x>det && totdist<3.0) {
      p=from+totdist*dir;
      d=de(p);
      det=detail*(1.+totdist*60.)*(1.+ref*5.);
      totdist+=d.x; 
      energy=ENERGY_COLOR*(1.5+sin(time*20.+p.z*10.))*.25;
      if(d.x<0.015)glow+=max(0.,.015-d.x)*exp(-totdist);
      if (d.y<.5 && d.x<0.03){//ONLY DOING THE GLOW WHEN IT IS CLOSE ENOUGH
        float glw=min(abs(3.35-p.y-ey),abs(3.35-p.y+ey));//2 glows at once
        eglow+=max(0.,.03-d.x)/.03*
          (pow(max(0.,.05-glw)/.05,5.)
           +pow(max(0.,.15-abs(3.35-p.y))/.15,8.))*1.5;
      }
    }
  }
  float l=pow(max(0.,dot(normalize(-dir.xz),normalize(lightdir.xz))),2.);
  l*=max(0.2,dot(-dir,lightdir));
  vec3 backg=.5*(1.2-l)+LIGHT_COLOR*l*.7;
  backg*=AMBIENT_COLOR;
  if (d.x<=det) {
    vec3 norm=normal(p-abs(d.x-det)*dir);//DO THE NORMAL CALC OUTSIDE OF LIGHTING (since we already have the sphere normal)
    col=light(p-abs(d.x-det)*dir, dir, norm, d.y)*exp(-.2*totdist*totdist); 
    col = mix(col, backg, 1.0-exp(-1.*pow(totdist,1.5)));
  } else { 
    col=backg;
  }
  vec3 lglow=LIGHT_COLOR*pow(l,30.)*.5;
  col+=glow*(backg+lglow)*1.3;
  col+=pow(eglow,2.)*energy*.015;
  col+=lglow*min(1.,totdist*totdist*.3);
  if (ref>0.5) {
    vec3 sphlight=light(origfrom+sphdist*origdir,origdir,sphNorm,2.);
    col=mix(col*.3+sphlight*.7,backg,1.0-exp(-1.*pow(sphdist,1.5)));
  }
  return col; 
}

vec3 move(inout mat2 rotview1,inout mat2 rotview2) {
  vec3 go=path(t);
  vec3 adv=path(t+.7);
  vec3 advec=normalize(adv-go);
  float an=atan(advec.x,advec.z);
  rotview1=mat2(cos(an),sin(an),-sin(an),cos(an));
  an=advec.y*1.7;
  rotview2=mat2(cos(an),sin(an),-sin(an),cos(an));
  return go;
}

void main(){
  vec4 color;
  pth1 = path(t+.3)+origin+vec3(0.,.01,0.);
  vec2 uv = coordinate * 2.0 -1.0;
  vec2 uv2=uv;
  uv.y*=object_size.y/object_size.x;
  mat2 rotview1, rotview2;
  vec3 from=origin+move(rotview1,rotview2);
  vec3 dir=normalize(vec3(uv*.8,1.));
  dir.yz*=rot(0.0);
  dir.xz*=rot(0.0);
  dir.yz*=rotview2;
  dir.xz*=rotview1;
  color = texture2D(texture1, coordinate);
  if(color.r == 0.0 && integer == 1){
    color=vec4(raymarch(from,dir), 1.0);
    color=clamp(color,vec4(.0),vec4(1.));
    color=pow(color,vec4(GAMMA))*BRIGHTNESS;
    color=mix(vec4(length(color)),color,SATURATION);
  }
  gl_FragData[0] = color;
}
 
