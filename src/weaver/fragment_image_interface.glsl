/*683:*/
#line 15289 "./cweb/weaver.w"


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


/*472:*/
#line 10266 "./cweb/weaver.w"

uniform vec4 object_color;
uniform mat4 model_view_matrix;
uniform vec2 object_size;
uniform float time;
uniform sampler2D texture1;
uniform int integer;
/*:472*/
#line 15304 "./cweb/weaver.w"


varying mediump vec2 coordinate;

void main(){
gl_FragData[0]= texture2D(texture1,coordinate);
}
/*:683*/
