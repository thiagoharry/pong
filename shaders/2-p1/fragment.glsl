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

void main(){// 30x5
  vec4 color;
  if(integer == 1){
    if(coordinate.x < 0.033){ // Column 1
      if(coordinate.y < 0.8 && coordinate.y > 0.6)
        color = vec4(1.0, 1.0, 1.0, 1.0);
      else
        color = vec4(0.0, 0.0, 0.0, 0.0);
    }
    else if(coordinate.x < 0.066){ // Column 2
      color = vec4(1.0, 1.0, 1.0, 1.0);
    }
    else if(coordinate.x < 0.133){ // Column 3 and 4
      color = vec4(0.0, 0.0, 0.0, 0.0);
    }
    else if(coordinate.x < 0.166){ // Column 5
      color = vec4(1.0, 1.0, 1.0, 1.0);
    }
    else if(coordinate.x < 0.199){ // Column 6
      if(coordinate.y > 0.8 || (coordinate.y <= 0.6 && coordinate.y > 0.4)){
        color = vec4(1.0, 1.0, 1.0, 1.0);
      }
      else color = vec4(0.0, 0.0, 0.0, 0.0);
    }
    else if(coordinate.x < 0.233){ // Column 7
      if(coordinate.y <= 0.8 && coordinate.y > 0.6){
        color = vec4(1.0, 1.0, 1.0, 1.0);
      }
      else color = vec4(0.0, 0.0, 0.0, 0.0);
    }
  }
  else if(integer == 2){
    if(coordinate.x < 0.033){ // Column 1
      if(coordinate.y > 0.8)
        color = vec4(1.0, 1.0, 1.0, 1.0);
      else if( coordinate.y > 0.4)
        color = vec4(0.0, 0.0, 0.0, 0.0);
      else
        color = vec4(1.0, 1.0, 1.0, 1.0);
    }
    else if(coordinate.x < 0.066){ // Column 2
      if(coordinate.y > 0.8)
        color = vec4(1.0, 1.0, 1.0, 1.0);
      else if( coordinate.y > 0.6)
        color = vec4(0.0, 0.0, 0.0, 0.0);
      else if( coordinate.y > 0.4)
        color = vec4(1.0, 1.0, 1.0, 1.0);
      else if( coordinate.y > 0.2)
        color = vec4(0.0, 0.0, 0.0, 0.0);
      else
        color = vec4(1.0, 1.0, 1.0, 1.0);
    }
    else if(coordinate.x < 0.099){ // Column 3
      if(coordinate.y > 0.8)
        color = vec4(0.0, 0.0, 0.0, 0.0);
      else if( coordinate.y > 0.6)
        color = vec4(1.0, 1.0, 1.0, 1.0);
      else if( coordinate.y > 0.2)
        color = vec4(0.0, 0.0, 0.0, 0.0);
      else
        color = vec4(1.0, 1.0, 1.0, 1.0);
    }
    else if(coordinate.x < 0.133){ // Column 4
      color = vec4(0.0, 0.0, 0.0, 0.0);
    }
    else if(coordinate.x < 0.166){ // Column 5
      color = vec4(1.0, 1.0, 1.0, 1.0);
    }
    else if(coordinate.x < 0.199){ // Column 6
      if(coordinate.y > 0.8 || (coordinate.y <= 0.6 && coordinate.y > 0.4)){
        color = vec4(1.0, 1.0, 1.0, 1.0);
      }
      else color = vec4(0.0, 0.0, 0.0, 0.0);
    }
    else if(coordinate.x < 0.233){ // Column 7
      if(coordinate.y <= 0.8 && coordinate.y > 0.6){
        color = vec4(1.0, 1.0, 1.0, 1.0);
      }
      else color = vec4(0.0, 0.0, 0.0, 0.0);
    }
  }
  if(coordinate.x >= 0.233){
    // Now we get the pixels in each line:
    if(coordinate.y > 0.8){
      if(coordinate.x  < 0.4)
        color = vec4(0.0, 0.0, 0.0, 0.0);
      else if(coordinate.x < 0.466)
        color = vec4(1.0, 1.0, 1.0, 1.0);
      else if(coordinate.x < 0.499)
        color = vec4(0.0, 0.0, 0.0, 0.0);
      else if(coordinate.x < 0.599)
        color = vec4(1.0, 1.0, 1.0, 1.0);
      else if(coordinate.x < 0.633)
        color = vec4(0.0, 0.0, 0.0, 0.0);
      else if(coordinate.x < 0.733)
        color = vec4(1.0, 1.0, 1.0, 1.0);
      else if(coordinate.x < 0.766)
        color = vec4(0.0, 0.0, 0.0, 0.0);
      else if(coordinate.x < 0.833)
        color = vec4(1.0, 1.0, 1.0, 1.0);
      else if(coordinate.x < 0.899)
        color = vec4(0.0, 0.0, 0.0, 0.0);
      else
        color = vec4(1.0, 1.0, 1.0, 1.0);
    }
    else if(coordinate.y > 0.6){
      if(coordinate.x  < 0.366)
        color = vec4(0.0, 0.0, 0.0, 0.0);
      else if(coordinate.x < 0.4)
        color = vec4(1.0, 1.0, 1.0, 1.0);
      else if(coordinate.x < 0.533)
        color = vec4(0.0, 0.0, 0.0, 0.0);
      else if(coordinate.x < 0.566)
        color = vec4(1.0, 1.0, 1.0, 1.0);
      else if(coordinate.x < 0.633)
        color = vec4(0.0, 0.0, 0.0, 0.0);
      else if(coordinate.x < 0.666)
        color = vec4(1.0, 1.0, 1.0, 1.0);
      else if(coordinate.x < 0.699)
        color = vec4(0.0, 0.0, 0.0, 0.0);
      else if(coordinate.x < 0.733)
        color = vec4(1.0, 1.0, 1.0, 1.0);
      else if(coordinate.x < 0.766)
        color = vec4(0.0, 0.0, 0.0, 0.0);
      else if(coordinate.x < 0.799)
        color = vec4(1.0, 1.0, 1.0, 1.0);
      else if(coordinate.x < 0.833)
        color = vec4(0.0, 0.0, 0.0, 0.0);
      else if(coordinate.x < 0.866)
        color = vec4(1.0, 1.0, 1.0, 1.0);
      else if(coordinate.x < 0.933)
        color = vec4(0.0, 0.0, 0.0, 0.0);
      else if(coordinate.x < 0.966)
        color = vec4(1.0, 1.0, 1.0, 1.0);
      else
        color = vec4(0.0, 0.0, 0.0, 0.0);
    }
    else if(coordinate.y > 0.4){
      if(coordinate.x  < 0.4)
        color = vec4(0.0, 0.0, 0.0, 0.0);
      else if(coordinate.x  < 0.433)
        color = vec4(1.0, 1.0, 1.0, 1.0);
      else if(coordinate.x  < 0.533)
        color = vec4(0.0, 0.0, 0.0, 0.0);
      else if(coordinate.x  < 0.566)
        color = vec4(1.0, 1.0, 1.0, 1.0);
      else if(coordinate.x  < 0.633)
        color = vec4(0.0, 0.0, 0.0, 0.0);
      else if(coordinate.x  < 0.733)
        color = vec4(1.0, 1.0, 1.0, 1.0);
      else if(coordinate.x  < 0.766)
        color = vec4(0.0, 0.0, 0.0, 0.0);
      else if(coordinate.x  < 0.866)
        color = vec4(1.0, 1.0, 1.0, 1.0);
      else if(coordinate.x  < 0.933)
        color = vec4(0.0, 0.0, 0.0, 0.0);
      else if(coordinate.x  < 0.966)
        color = vec4(1.0, 1.0, 1.0, 1.0);
      else
        color = vec4(0.0, 0.0, 0.0, 0.0);
    }
    else if(coordinate.y > 0.2){
      if(coordinate.x  < 0.433)
        color = vec4(0.0, 0.0, 0.0, 0.0);
      else if(coordinate.x  < 0.466)
        color = vec4(1.0, 1.0, 1.0, 1.0);
      else if(coordinate.x  < 0.533)
        color = vec4(0.0, 0.0, 0.0, 0.0);
      else if(coordinate.x  < 0.566)
        color = vec4(1.0, 1.0, 1.0, 1.0);
      else if(coordinate.x  < 0.633)
        color = vec4(0.0, 0.0, 0.0, 0.0);
      else if(coordinate.x  < 0.666)
        color = vec4(1.0, 1.0, 1.0, 1.0);
      else if(coordinate.x  < 0.699)
        color = vec4(0.0, 0.0, 0.0, 0.0);
      else if(coordinate.x  < 0.733)
        color = vec4(1.0, 1.0, 1.0, 1.0);
      else if(coordinate.x  < 0.766)
        color = vec4(0.0, 0.0, 0.0, 0.0);
      else if(coordinate.x  < 0.833)
        color = vec4(1.0, 1.0, 1.0, 1.0);
      else if(coordinate.x  < 0.933)
        color = vec4(0.0, 0.0, 0.0, 0.0);
      else if(coordinate.x  < 0.966)
        color = vec4(1.0, 1.0, 1.0, 1.0);
      else
        color = vec4(0.0, 0.0, 0.0, 0.0);
    }
    else{
      if(coordinate.x  < 0.366)
        color = vec4(0.0, 0.0, 0.0, 0.0);
      else if(coordinate.x  < 0.433)
        color = vec4(1.0, 1.0, 1.0, 1.0);
      else if(coordinate.x  < 0.533)
        color = vec4(0.0, 0.0, 0.0, 0.0);
      else if(coordinate.x  < 0.566)
        color = vec4(1.0, 1.0, 1.0, 1.0);
      else if(coordinate.x  < 0.633)
        color = vec4(0.0, 0.0, 0.0, 0.0);
      else if(coordinate.x  < 0.666)
        color = vec4(1.0, 1.0, 1.0, 1.0);
      else if(coordinate.x  < 0.699)
        color = vec4(0.0, 0.0, 0.0, 0.0);
      else if(coordinate.x  < 0.733)
        color = vec4(1.0, 1.0, 1.0, 1.0);
      else if(coordinate.x  < 0.766)
        color = vec4(0.0, 0.0, 0.0, 0.0);
      else if(coordinate.x  < 0.799)
        color = vec4(1.0, 1.0, 1.0, 1.0);
      else if(coordinate.x  < 0.833)
        color = vec4(0.0, 0.0, 0.0, 0.0);
      else if(coordinate.x  < 0.866)
        color = vec4(1.0, 1.0, 1.0, 1.0);
      else if(coordinate.x  < 0.933)
        color = vec4(0.0, 0.0, 0.0, 0.0);
      else if(coordinate.x  < 0.966)
        color = vec4(1.0, 1.0, 1.0, 1.0);
      else
        color = vec4(0.0, 0.0, 0.0, 0.0);
    }
  }
  gl_FragData[0] = color;
}
 
