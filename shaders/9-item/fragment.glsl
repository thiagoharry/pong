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
  if(position.y < 0.05){ //linha 1
    if(position.x > 0.65 && position.x < 0.7)
      color = vec4(0.718, 0.07, 0.07, 1.0);
    else
      color = vec4(0.0, 0.0, 0.0, 0.0);
  }
  else if(position.y < 0.1){ // Linha 2
    if(position.x < 0.6)
      color = vec4(0.0, 0.0, 0.0, 0.0);
    else if(position.x < 0.65)
      color = vec4(0.695, 0.07, 0.07, 1.0);
    else if(position.x < 0.75)
      color = vec4(0.617, 0.019, 0.019, 1.0);
    else color = vec4(0.0, 0.0, 0.0, 0.0);
  }
  else if(position.y < 0.15){ // Linha 3
    if(position.x < 0.55)
      color = vec4(0.0, 0.0, 0.0, 0.0);
    else if(position.x < 0.6)
      color = vec4(0.836, 0.871, 0.871, 1.0);
    else if(position.x < 0.65)
      color = vec4(0.8, 0.852, 0.953, 1.0);
    else if(position.x < 0.7)
      color = vec4(0.613, 0.031, 0.031, 1.0);
    else if(position.x < 0.75)
      color = vec4(0.547, 0.0, 0.0, 1.0);
    else if(position.x < 0.8)
      color = vec4(0.5, 0.0, 0.0, 1.0);
    else color = vec4(0.0, 0.0, 0.0, 0.0);
  }
  else if(position.y < 0.2){ // Linha 4
    if(position.x < 0.5)
      color = vec4(0.0, 0.0, 0.0, 0.0);
    else if(position.x < 0.55)
      color = vec4(0.8125, 0.8045, 0.7695, 1.0);
    else if(position.x < 0.6)
      color = vec4(0.801, 0.852, 0.953, 1.0);
    else if(position.x < 0.65)
      color = vec4(0.836, 0.961, 0.949, 1.0);
    else if(position.x < 0.7)
      color = vec4(0.723, 0.66, 0.656, 1.0);
    else if(position.x < 0.75)
      color = vec4(0.523, 0.0625, 0.0625, 1.0);
    else if(position.x < 0.85)
      color = vec4(0.453, 0.0, 0.0, 1.0);
    else color = vec4(0.0, 0.0, 0.0, 0.0);
  }
  else if(position.y < 0.25){ // Linha 5
    if(position.x < 0.45)
      color = vec4(0.0, 0.0, 0.0, 0.0);
    else if(position.x < 0.5)
      color = vec4(1.0, 0.773, 0.094, 1.0);
    else if(position.x < 0.55)
      color = vec4(0.922, 0.167, 0.0039, 1.0);
    else if(position.x < 0.6)
      color = vec4(0.738, 0.727, 0.742, 1.0);
    else if(position.x < 0.65)
      color = vec4(0.703, 0.94, 0.891, 1.0);
    else if(position.x < 0.7)
      color = vec4(0.785, 0.887, 0.879, 1.0);
    else if(position.x < 0.75)
      color = vec4(0.766, 0.781, 0.777, 1.0);
    else if(position.x < 0.8)
      color = vec4(0.555, 0.172, 0.172, 1.0);
    else if(position.x < 0.85)
      color = vec4(0.488, 0.0, 0.0, 1.0);
    else if(position.x < 0.9)
      color = vec4(0.473, 0.0, 0.0, 1.0);
    else color = vec4(0.0, 0.0, 0.0, 0.0);
  }
  else if(position.y < 0.3){ // Linha 6
    if(position.x < 0.45)
      color = vec4(0.0, 0.0, 0.0, 0.0);
    else if(position.x < 0.5)
      color = vec4(0.965, 0.641, 0.0, 1.0);
    else if(position.x < 0.55)
      color = vec4(0.961, 0.625, 0.0, 1.0);
    else if(position.x < 0.6)
      color = vec4(0.945, 0.680, 0.0039, 1.0);
    else if(position.x < 0.65)
      color = vec4(0.789, 0.758, 0.617, 1.0);
    else if(position.x < 0.7)
      color = vec4(0.777, 0.832, 0.988, 1.0);
    else if(position.x < 0.75)
      color = vec4(0.891, 0.965, 0.980, 1.0);
    else if(position.x < 0.8)
      color = vec4(0.886, 0.953, 0.945, 1.0);
    else if(position.x < 0.85)
      color = vec4(0.616, 0.271, 0.271, 1.0);
    else if(position.x < 0.9)
      color = vec4(0.510, 0.000, 0.000, 1.0);
    else color = vec4(0.0, 0.0, 0.0, 0.0);
  }
  else if(position.y < 0.35){ // Linha 7
    if(position.x < 0.4)
      color = vec4(0.0, 0.0, 0.0, 0.0);
    else if(position.x < 0.45)
      color = vec4(0.249, 0.641, 0.0, 1.0);
    else if(position.x < 0.5)
      color = vec4 (0.9764705882352941, 0.6588235294117647, 0.0, 1.0);
    else if(position.x < 0.55)
      color = vec4 (0.9254901960784314, 0.6274509803921569, 0.0, 1.0);
    else if(position.x < 0.6)
      color = vec4 (0.9725490196078431, 0.7215686274509804, 0.0196078431372549, 1.0);
    else if(position.x < 0.65)
      color = vec4 (0.9882352941176471, 0.6705882352941176, 0.0, 1.0);
    else if(position.x < 0.7)
      color = vec4 (0.8823529411764706, 0.7725490196078432, 0.5529411764705883, 1.0);
    else if(position.x < 0.75)
      color = vec4 (0.8117647058823529, 0.8745098039215686, 1.0, 1.0);
    else if(position.x < 0.8)
      color = vec4 (0.8705882352941177, 0.9333333333333333, 0.9725490196078431, 1.0);
    else if(position.x < 0.85)
      color = vec4 (0.803921568627451, 0.8352941176470589, 0.8235294117647058, 1.0);
    else color = vec4(0.0, 0.0, 0.0, 0.0);
  }
  else if(position.y < 0.4){ // Linha 8
    if(position.x < 0.35)
      color = vec4(0.0, 0.0, 0.0, 0.0);
    else if(position.x < 0.4)
      color = vec4 (0.9764705882352941, 0.6588235294117647, 0.0, 1.0);
    else if(position.x < 0.45)
      color = vec4 (0.9294117647058824, 0.615686274509804, 0.0, 1.0);
    else if(position.x < 0.5)
      color = vec4 (0.9607843137254902, 0.6980392156862745, 0.0196078431372549, 1.0);
    else if(position.x < 0.55)
      color = vec4 (1.0, 0.7647058823529411, 0.00392156862745098, 1.0);
    else if(position.x < 0.6)
      color = vec4 (0.9921568627450981, 0.7058823529411765, 0.0, 1.0);
    else if(position.x < 0.65)
      color = vec4 (1.0, 0.6627450980392157, 0.0, 1.0);
    else if(position.x < 0.7)
      color = vec4 (1.0, 0.6862745098039216, 0.0, 1.0);
    else if(position.x < 0.75)
      color = vec4 (0.8705882352941177, 0.7490196078431373, 0.39215686274509803, 1.0);
    else if(position.x < 0.8)
      color = vec4 (0.7411764705882353, 0.7725490196078432, 0.8549019607843137, 1.0);
    else if(position.x < 0.85)
      color = vec4 (0.7686274509803922, 0.803921568627451, 0.8235294117647058, 1.0);
    else color = vec4(0.0, 0.0, 0.0, 0.0);
  }
  else if(position.y < 0.45){ // Linha 9
    if(position.x < 0.3)
      color = vec4(0.0, 0.0, 0.0, 0.0);
    else if(position.x < 0.35)
      color = vec4 (0.996078431372549, 0.7294117647058823, 0.03529411764705882, 1.0);
    else if(position.x < 0.4)
      color = vec4 (0.9333333333333333, 0.611764705882353, 0.0, 1.0);
    else if(position.x < 0.45)
      color = vec4 (0.9490196078431372, 0.6823529411764706, 0.0196078431372549, 1.0);
    else if(position.x < 0.5)
      color = vec4 (1.0, 0.7647058823529411, 0.00784313725490196, 1.0);
    else if(position.x < 0.55)
      color = vec4 (0.996078431372549, 0.7137254901960784, 0.0, 1.0);
    else if(position.x < 0.6)
      color = vec4 (0.9882352941176471, 0.6666666666666666, 0.00784313725490196, 1.0);
    else if(position.x < 0.65)
      color = vec4 (0.996078431372549, 0.7254901960784313, 0.03529411764705882, 1.0);
    else if(position.x < 0.7)
      color = vec4 (0.996078431372549, 0.7333333333333333, 0.00784313725490196, 1.0);
    else if(position.x < 0.75)
      color = vec4 (0.9411764705882353, 0.5490196078431373, 0.0, 1.0);
    else if(position.x < 0.8)
      color = vec4 (0.8, 0.6039215686274509, 0.2823529411764706, 1.0);
    else color = vec4(0.0, 0.0, 0.0, 0.0);
  }
  else if(position.y < 0.5){ // Linha 10
    if(position.x < 0.25)
      color = vec4(0.0, 0.0, 0.0, 0.0);
    else if(position.x < 0.3)
      color = vec4 (1.0, 0.7764705882352941, 0.1843137254901961, 1.0);
    else if(position.x < 0.35)
      color = vec4 (0.9411764705882353, 0.611764705882353, 0.0, 1.0);
    else if(position.x < 0.4)
      color = vec4 (0.9372549019607843, 0.6666666666666666, 0.0196078431372549, 1.0);
    else if(position.x < 0.45)
      color = vec4 (1.0, 0.7607843137254902, 0.011764705882352941, 1.0);
    else if(position.x < 0.5)
      color = vec4 (1.0, 0.7294117647058823, 0.0, 1.0);
    else if(position.x < 0.55)
      color = vec4 (0.9882352941176471, 0.6666666666666666, 0.00392156862745098, 1.0);
    else if(position.x < 0.6)
      color = vec4 (0.996078431372549, 0.7098039215686275, 0.03529411764705882, 1.0);
    else if(position.x < 0.65)
      color = vec4 (0.984313725490196, 0.7411764705882353, 0.01568627450980392, 1.0);
    else if(position.x < 0.7)
      color = vec4 (0.9215686274509803, 0.6078431372549019, 0.0, 1.0);
    else if(position.x < 0.75)
      color = vec4 (0.8980392156862745, 0.5411764705882353, 0.0, 1.0);
    else color = vec4(0.0, 0.0, 0.0, 0.0);
  }
  else if(position.y < 0.55){ // Linha 11
    if(position.x < 0.25)
      color = vec4(0.0, 0.0, 0.0, 0.0);
    else if(position.x < 0.3)
      color = vec4 (0.9529411764705882, 0.615686274509804, 0.0, 1.0);
    else if(position.x < 0.35)
      color = vec4 (0.9333333333333333, 0.6470588235294118, 0.011764705882352941, 1.0);
    else if(position.x < 0.4)
      color = vec4 (0.9333333333333333, 0.6470588235294118, 0.011764705882352941, 1.0);
    else if(position.x < 0.45)
      color = vec4 (1.0, 0.7411764705882353, 0.0, 1.0);
    else if(position.x < 0.5)
      color = vec4 (0.9882352941176471, 0.6705882352941176, 0.0, 1.0);
    else if(position.x < 0.55)
      color = vec4 (0.996078431372549, 0.6980392156862745, 0.03137254901960784, 1.0);
    else if(position.x < 0.6)
      color = vec4 (0.9882352941176471, 0.7450980392156863, 0.023529411764705882, 1.0);
    else if(position.x < 0.65)
      color = vec4 (0.9372549019607843, 0.6431372549019608, 0.0, 1.0);
    else if(position.x < 0.7)
      color = vec4 (0.8823529411764706, 0.5137254901960784, 0.0, 1.0);
    else color = vec4(0.0, 0.0, 0.0, 0.0);
  }
  else if(position.y < 0.6){ // Linha 12
    if(position.x < 0.2)
      color = vec4(0.0, 0.0, 0.0, 0.0);
    else if(position.x < 0.25)
      color = vec4 (0.9647058823529412, 0.6392156862745098, 0.0, 1.0);
    else if(position.x < 0.3)
      color = vec4 (0.9254901960784314, 0.6274509803921569, 0.0, 1.0);
    else if(position.x < 0.35)
      color = vec4 (0.9882352941176471, 0.7411764705882353, 0.01568627450980392, 1.0);
    else if(position.x < 0.4)
      color = vec4 (1.0, 0.7529411764705882, 0.0, 1.0);
    else if(position.x < 0.45)
      color = vec4 (0.9882352941176471, 0.6784313725490196, 0.0, 1.0);
    else if(position.x < 0.5)
      color = vec4 (0.9921568627450981, 0.6862745098039216, 0.027450980392156862, 1.0);
    else if(position.x < 0.55)
      color = vec4 (0.9921568627450981, 0.7490196078431373, 0.027450980392156862, 1.0);
    else if(position.x < 0.6)
      color = vec4 (0.9490196078431372, 0.6705882352941176, 0.0, 1.0);
    else if(position.x < 0.65)
      color = vec4 (0.8823529411764706, 0.5058823529411764, 0.0, 1.0);
    else color = vec4(0.0, 0.0, 0.0, 0.0);
  }
  else if(position.y < 0.65){ // Linha 13
    if(position.x < 0.15)
      color = vec4(0.0, 0.0, 0.0, 0.0);
    else if(position.x < 0.2)
      color = vec4 (0.9686274509803922, 0.6666666666666666, 0.0, 1.0);
    else if(position.x < 0.25)
      color = vec4 (0.9294117647058824, 0.615686274509804, 0.0, 1.0);
    else if(position.x < 0.3)
      color = vec4 (0.9725490196078431, 0.7254901960784313, 0.0196078431372549, 1.0);
    else if(position.x < 0.35)
      color = vec4 (1.0, 0.7568627450980392, 0.0, 1.0);
    else if(position.x < 0.4)
      color = vec4 (0.9921568627450981, 0.6862745098039216, 0.0, 1.0);
    else if(position.x < 0.45)
      color = vec4 (0.9921568627450981, 0.6745098039215687, 0.0196078431372549, 1.0);
    else if(position.x < 0.5)
      color = vec4 (0.996078431372549, 0.7450980392156863, 0.03137254901960784, 1.0);
    else if(position.x < 0.55)
      color = vec4 (0.9607843137254902, 0.6980392156862745, 0.0, 1.0);
    else if(position.x < 0.6)
      color = vec4 (0.8901960784313725, 0.5176470588235295, 0.0, 1.0);
    else color = vec4(0.0, 0.0, 0.0, 0.0);
  }
  else if(position.y < 0.7){ // Linha 14
    if(position.x < 0.15)
      color = vec4(0.0, 0.0, 0.0, 0.0);
    else if(position.x < 0.2)
      color = vec4 (0.9137254901960784, 0.6705882352941176, 0.25098039215686274, 1.0);
    else if(position.x < 0.25)
      color = vec4 (0.9882352941176471, 0.6862745098039216, 0.0, 1.0);
    else if(position.x < 0.3)
      color = vec4 (1.0, 0.7725490196078432, 0.0, 1.0);
    else if(position.x < 0.35)
      color = vec4 (0.9921568627450981, 0.6980392156862745, 0.0, 1.0);
    else if(position.x < 0.4)    
      color = vec4 (0.9882352941176471, 0.6666666666666666, 0.01568627450980392, 1.0);
    else if(position.x < 0.45)
      color = vec4 (0.996078431372549, 0.7372549019607844, 0.03529411764705882, 1.0);
    else if(position.x < 0.5)
      color = vec4 (0.9686274509803922, 0.7176470588235294, 0.0, 1.0);
    else if(position.x < 0.55)
      color = vec4 (0.8980392156862745, 0.5372549019607843, 0.0, 1.0);
    else if(position.x < 0.6)
      color = vec4 (0.9019607843137255, 0.6274509803921569, 0.1843137254901961, 1.0);
    else color = vec4(0.0, 0.0, 0.0, 0.0);
  }
  else if(position.y < 0.75){ // Linha 15
    if(position.x < 0.1)
      color = vec4(0.0, 0.0, 0.0, 0.0);
    else if(position.x < 0.15)
      color = vec4 (0.9294117647058824, 0.8549019607843137, 0.8980392156862745, 1.0);
    else if(position.x < 0.2)
      color = vec4 (0.9294117647058824, 0.7843137254901961, 0.6470588235294118, 1.0);
    else if(position.x < 0.25)
      color = vec4 (0.9058823529411765, 0.7137254901960784, 0.34901960784313724, 1.0);
    else if(position.x < 0.3)
      color = vec4 (0.9490196078431372, 0.6901960784313725, 0.10980392156862745, 1.0);
    else if(position.x < 0.35)
      color = vec4 (1.0, 0.6705882352941176, 0.0, 1.0);
    else if(position.x < 0.4)
      color = vec4 (0.996078431372549, 0.7254901960784313, 0.03529411764705882, 1.0);
    else if(position.x < 0.45)
      color = vec4 (0.9764705882352941, 0.7294117647058823, 0.00784313725490196, 1.0);
    else if(position.x < 0.5)
      color = vec4 (0.9098039215686274, 0.5647058823529412, 0.0, 1.0);
    else if(position.x < 0.55)
      color = vec4 (0.8941176470588236, 0.5764705882352941, 0.07450980392156863, 1.0);
    else color = vec4(0.0, 0.0, 0.0, 0.0);
  }
  else if(position.y < 0.8){ // Linha 16
    if(position.x < 0.1)
      color = vec4(0.0, 0.0, 0.0, 0.0);
    else if(position.x < 0.15)
      color = vec4 (0.9176470588235294, 0.8, 0.7294117647058823, 1.0);
    else if(position.x < 0.2)
      color = vec4 (0.9137254901960784, 0.7764705882352941, 0.7686274509803922, 1.0);
    else if(position.x < 0.25)
      color = vec4 (0.807843137254902, 0.6901960784313725, 0.8862745098039215, 1.0);
    else if(position.x < 0.3)
      color = vec4 (0.8470588235294118, 0.6235294117647059, 0.42745098039215684, 1.0);
    else if(position.x < 0.35)
      color = vec4 (1.0, 0.7137254901960784, 0.0, 1.0);
    else if(position.x < 0.4)
      color = vec4 (0.9921568627450981, 0.7254901960784313, 0.0, 1.0);
    else if(position.x < 0.45)
      color = vec4 (0.9254901960784314, 0.6, 0.0, 1.0);
    else if(position.x < 0.5)
      color = vec4 (0.8823529411764706, 0.5411764705882353, 0.0, 1.0);
    else color = vec4(0.0, 0.0, 0.0, 0.0);
  }
  else if(position.y < 0.85){ // Linha 17
    if(position.x < 0.1)
      color = vec4(0.0, 0.0, 0.0, 0.0);
    else if(position.x < 0.15)
      color = vec4 (0.8941176470588236, 0.7607843137254902, 0.7019607843137254, 1.0);
    else if(position.x < 0.2)
      color = vec4 (0.8784313725490196, 0.7058823529411765, 0.6431372549019608, 1.0);
    else if(position.x < 0.25)
      color = vec4 (0.8313725490196079, 0.6470588235294118, 0.6196078431372549, 1.0);
    else if(position.x < 0.3)
      color = vec4 (0.8470588235294118, 0.6509803921568628, 0.5450980392156862, 1.0);
    else if(position.x < 0.35)
      color = vec4 (0.9058823529411765, 0.7098039215686275, 0.39215686274509803, 1.0);
    else if(position.x < 0.4)
      color = vec4 (0.9058823529411765, 0.6470588235294118, 0.21176470588235294, 1.0);
    else if(position.x < 0.45)
      color = vec4 (0.8862745098039215, 0.5176470588235295, 0.0, 1.0);
    else color = vec4(0.0, 0.0, 0.0, 0.0);
  }
  else if(position.y < 0.9){ // Linha 18
    if(position.x < 0.1)
      color = vec4(0.0, 0.0, 0.0, 0.0);
    else if(position.x < 0.15)
      color = vec4 (0.9294117647058824, 0.7529411764705882, 0.6823529411764706, 1.0);
    else if(position.x < 0.2)
      color = vec4 (0.8509803921568627, 0.6549019607843137, 0.592156862745098, 1.0);
    else if(position.x < 0.25)
      color = vec4 (0.8431372549019608, 0.6352941176470588, 0.5450980392156862, 1.0);
    else if(position.x < 0.3)
      color = vec4 (0.8666666666666667, 0.6627450980392157, 0.5803921568627451, 1.0);
    else if(position.x < 0.35)
      color = vec4 (0.8823529411764706, 0.6980392156862745, 0.6980392156862745, 1.0);
    else if(position.x < 0.4)
      color = vec4 (0.8823529411764706, 0.6784313725490196, 0.5333333333333333, 1.0);
    else color = vec4(0.0, 0.0, 0.0, 0.0);
  }
  else if(position.y < 0.95){ // Linha 19
    if(position.x < 0.1)
      color = vec4(0.0, 0.0, 0.0, 0.0);
    else if(position.x < 0.15)
      color = vec4 (1.0, 0.7137254901960784, 0.0, 1.0);
    else if(position.x < 0.2)
      color = vec4 (0.8274509803921568, 0.6196078431372549, 0.5450980392156862, 1.0);
    else if(position.x < 0.25)
      color = vec4 (0.8274509803921568, 0.6196078431372549, 0.5450980392156862, 1.0);
    else color = vec4(0.0, 0.0, 0.0, 0.0);
  }
  else{ // Linha 20
    if(position.x < 0.1)
      color = vec4(0.0, 0.0, 0.0, 0.0);
    else if(position.x < 0.15)
      color = vec4 (1.0, 0.7137254901960784, 0.0, 1.0);
    else color = vec4(0.0, 0.0, 0.0, 0.0);
  }
  dst = distance(color, vec4(1.0, 1.0, 0.0, 1.0));
  r = sin(time);
  g = cos(time * 0.5 + 0.25);
  b = position.x * 0.5;
  if(dst < 0.6)
    gl_FragData[0] = vec4(r, g, b, 1.0);
  else
    gl_FragData[0] = color;
}
