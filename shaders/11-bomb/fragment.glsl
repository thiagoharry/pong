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
  vec2 fuse = vec2(0.8, 0.725);
  float dst, x_pos, y_pos;
  x_pos = position.x - 0.05 * float(int((position.x + 0.5) / 0.05));
  y_pos = position.y - 0.02 * float(int((position.y + 0.5) / 0.02)); 
  /*if(abs(-0.05 - x_pos) > (0.05 * (20.0 / object_size.x))){
    color = vec4(0.0, 0.0, 0.0, 0.0);
  }
  else if(abs(-0.05 - y_pos) > (0.05 * (20.0 / object_size.y))){
    color = vec4(0.0, 0.0, 0.0, 0.0);
    }
    else*/ if(position.y > 0.9){ //linha 1 e 2
    color  = vec4(0.0, 0.0, 0.0, 0.0);
  }
  else if(position.y > 0.85){ // Linha 3
    if(position.x < 0.75)
      color = vec4(0.0, 0.0, 0.0, 0.0);
    else if(position.x < 0.8)
      color = vec4 (0.8784313725490196, 0.03529411764705882, 0.0, 1.0);
    else
      color = vec4(0.0, 0.0, 0.0, 0.0);
  }
  else if(position.y > 0.8){ // Linha 4
    if(position.x < 0.35)
      color = vec4 (0.0, 0.0, 0.0, 0.0);
    else if(position.x < 0.4)
      color = vec4 (0.01, 0.01, 0.01, 1.0);
    else if(position.x < 0.45)
      color = vec4 (0.03137254901960784, 0.023529411764705882, 0.01568627450980392, 1.0);
    else if(position.x < 0.5)
      color = vec4 (0.027450980392156862, 0.0196078431372549, 0.01568627450980392, 1.0);
    else if(position.x < 0.55)
      color = vec4 (0.01, 0.01, 0.01, 1.0);
    else if(position.x < 0.7)
      color = vec4(0.0, 0.0, 0.0, 0.0);
    else if(position.x < 0.75)
      color = vec4 (0.8823529411764706, 0.09019607843137255, 0.0, 1.0);
    else if(position.x < 0.8)
      color = vec4 (1.0, 0.6588235294117647, 0.00784313725490196, 1.0);
    else if(position.x < 0.85)
      color = vec4 (0.8941176470588236, 0.1450980392156863, 0.0, 1.0);
    else
      color = vec4(0.0, 0.0, 0.0, 0.0);
  }
  else if(position.y > 0.75){ // Linha 5
    if(position.x < 0.25)
      color = vec4(0.0, 0.0, 0.0, 0.0);
    else if(position.x < 0.35)
      color = vec4 (0.01, 0.01, 0.01, 1.0);
    else if(position.x < 0.4)
      color = vec4 (0.19215686274509805, 0.34509803921568627, 0.42745098039215684, 1.0);
    else if(position.x < 0.45)
      color = vec4 (0.23529411764705882, 0.36470588235294116, 0.4392156862745098, 1.0);
    else if(position.x < 0.5)
      color = vec4 (0.25098039215686274, 0.4, 0.48627450980392156, 1.0);
    else if(position.x < 0.55)
      color = vec4 (0.07058823529411765, 0.050980392156862744, 0.03529411764705882, 1.0);
    else if(position.x < 0.6)
      color = vec4 (0.01568627450980392, 0.00392156862745098, 0.0, 1.0);
    else if(position.x < 0.65)
      color = vec4 (0.0392156862745098, 0.0392156862745098, 0.0392156862745098, 1.0);
    else if(position.x < 0.7)
      color = vec4 (0.0, 0.00392156862745098, 0.03137254901960784, 1.0);
    else if(position.x < 0.75)
      color = vec4 (0.9803921568627451, 0.16470588235294117, 0.0, 1.0);
    else if(position.x < 0.8)
      color = vec4 (1.0, 1.0, 0.00392156862745098, 1.0);
    else if(position.x < 0.85)
      color = vec4 (0.8941176470588236, 0.11372549019607843, 0.0, 1.0);
    else
      color = vec4(0.0, 0.0, 0.0, 0.0);
  }
  else if(position.y > 0.7){ // Linha 6
    if(position.x < 0.2)
      color = vec4(0.0, 0.0, 0.0, 0.0);
    else if(position.x < 0.25)
      color = vec4 (0.01, 0.01, 0.01, 1.0);
    else if(position.x < 0.3)
      color = vec4 (0.19215686274509805, 0.34509803921568627, 0.42745098039215684, 1.0);
    else if(position.x < 0.4)
      color = vec4 (1.0, 1.0, 1.0, 1.0);
    else if(position.x < 0.45)
      color = vec4 (0.19215686274509805, 0.34509803921568627, 0.42745098039215684, 1.0);
    else if(position.x < 0.5)
      color = vec4 (0.0392156862745098, 0.0, 0.0, 1.0);
    else if(position.x < 0.55)
      color = vec4 (0.3843137254901961, 0.5686274509803921, 0.7333333333333333, 1.0);
    else if(position.x < 0.6)
      color = vec4 (0.45098039215686275, 0.6352941176470588, 0.796078431372549, 1.0);
    else if(position.x < 0.65)
      color = vec4 (0.00784313725490196, 0.01568627450980392, 0.03529411764705882, 1.0);
    else if(position.x < 0.7)
      color = vec4 (0.6470588235294118, 0.49019607843137253, 0.23921568627450981, 1.0);
    else if(position.x < 0.75)
      color = vec4 (0.5686274509803921, 0.5019607843137255, 0.26666666666666666, 1.0);
    else if(position.x < 0.8)
      color = vec4 (0.9058823529411765, 0.043137254901960784, 0.0, 1.0);
    else
      color = vec4(0.0, 0.0, 0.0, 0.0);
  }
  else if(position.y > 0.65){ // Linha 7
    if(position.x < 0.15)
      color = vec4(0.0, 0.0, 0.0, 0.0);
    else if(position.x < 0.2)
      color = vec4 (0.01, 0.01, 0.01, 1.0);
    else if(position.x < 0.25)
      color = vec4 (0.2196078431372549, 0.3607843137254902, 0.43529411764705883, 1.0);
    else if(position.x < 0.3)
      color = vec4 (0.14901960784313725, 0.2823529411764706, 0.34901960784313724, 1.0);
    else if(position.x < 0.4)
      color = vec4 (1.0, 1.0, 1.0, 1.0);
    else if(position.x < 0.4)
      color = vec4 (0.00784313725490196, 0.0, 0.0, 1.0);
    else if(position.x < 0.45)
      color = vec4 (0.3607843137254902, 0.5568627450980392, 0.7294117647058823, 1.0);
    else if(position.x < 0.5)
      color = vec4 (1.0, 1.0, 1.0, 1.0);
    else if(position.x < 0.55)
      color = vec4 (0.01, 0.01, 0.01, 1.0);
    else if(position.x < 0.6)
      color = vec4 (0.6823529411764706, 0.5176470588235295, 0.2549019607843137, 1.0);
    else if(position.x < 0.65)
      color = vec4 (0.6431372549019608, 0.48627450980392156, 0.23921568627450981, 1.0);
    else if(position.x < 0.7)
      color = vec4 (0.0, 0.0, 0.01568627450980392, 1.0);
    else
      color = vec4(0.0, 0.0, 0.0, 0.0);
  }
  else if(position.y > 0.6){ // Linha 8
    if(position.x < 0.15)
      color = vec4(0.0, 0.0, 0.0, 0.0);
    else if(position.x < 0.2)
      color = vec4 (0.01, 0.01, 0.01, 1.0);
    else if(position.x < 0.25)
      color = vec4 (0.6078431372549019, 0.7764705882352941, 0.9411764705882353, 1.0);
    else if(position.x < 0.3)
      color = vec4 (0.6, 0.7647058823529411, 0.9215686274509803, 1.0);
    else if(position.x < 0.35)
      color = vec4 (0.14901960784313725, 0.2823529411764706, 0.35294117647058826, 1.0);
    else if(position.x < 0.4)
      color = vec4 (0.1803921568627451, 0.3215686274509804, 0.4, 1.0);
    else if(position.x < 0.45)
      color = vec4 (0.043137254901960784, 0.03529411764705882, 0.03137254901960784, 1.0);
    else if(position.x < 0.5)
      color = vec4 (0.8745098039215686, 0.8392156862745098, 0.8352941176470589, 1.0);
    else if(position.x < 0.55)
      color = vec4 (0.7529411764705882, 0.7450980392156863, 0.7568627450980392, 1.0);
    else if(position.x < 0.6)
      color = vec4 (0.8980392156862745, 0.8745098039215686, 0.8784313725490196, 1.0);
    else if(position.x < 0.65)
      color = vec4 (0.01, 0.01, 0.01, 1.0);
    else if(position.x < 0.7)
      color = vec4 (0.054901960784313725, 0.054901960784313725, 0.06666666666666667, 1.0);
    else if(position.x < 0.75)
      color = vec4 (0.03529411764705882, 0.03529411764705882, 0.03529411764705882, 1.0);
    else
      color = vec4(0.0, 0.0, 0.0, 0.0);
  }
  else if(position.y > 0.55){ // Linha 9
    if(position.x < 0.1)
      color = vec4(0.0, 0.0, 0.0, 0.0);
    else if(position.x < 0.15)
      color = vec4(0.01, 0.01, 0.01, 1.0);
    else if(position.x < 0.2)
      color = vec4 (0.050980392156862744, 0.2, 0.3137254901960784, 1.0);
    else if(position.x < 0.3)
      color = vec4 (1.0, 1.0, 1.0, 1.0);
    else if(position.x < 0.35)
      color = vec4 (0.17254901960784313, 0.3058823529411765, 0.3803921568627451, 1.0);
    else if(position.x < 0.4)
      color = vec4 (0.23137254901960785, 0.36470588235294116, 0.4392156862745098, 1.0);
    else if(position.x < 0.45)
      color = vec4 (0.06666666666666667, 0.0392156862745098, 0.01568627450980392, 1.0);
    else if(position.x < 0.5)
      color = vec4 (0.37254901960784315, 0.5725490196078431, 0.7450980392156863, 1.0);
    else if(position.x < 0.55)
      color = vec4 (0.8549019607843137, 0.807843137254902, 0.792156862745098, 1.0);
    else if(position.x < 0.6)
      color = vec4 (0.3333333333333333, 0.5098039215686274, 0.6627450980392157, 1.0);
    else if(position.x < 0.65)
      color = vec4 (0.43137254901960786, 0.596078431372549, 0.7529411764705882, 1.0);
    else if(position.x < 0.7)
      color = vec4 (0.23921568627450981, 0.38823529411764707, 0.4666666666666667, 1.0);
    else if(position.x < 0.75)
      color = vec4 (0.08627450980392157, 0.06666666666666667, 0.054901960784313725, 1.0);
    else if(position.x < 0.8)
      color = vec4 (0.01, 0.01, 0.01, 1.0);
    else
      color = vec4(0.0, 0.0, 0.0, 0.0);
  }
  else if(position.y > 0.5){ // Linha 10
    if(position.x < 0.1)
      color = vec4(0.0, 0.0, 0.0, 0.0);
    else if(position.x < 0.15)
      color = vec4(0.01, 0.01, 0.01, 1.0);
    else if(position.x < 0.2)
      color = vec4 (0.615686274509804, 0.788235294117647, 0.9490196078431372, 1.0);
    else if(position.x < 0.25)
      color = vec4 (1.0, 1.0, 1.0, 1.0);
    else if(position.x < 0.3)
      color = vec4 (0.32941176470588235, 0.5098039215686274, 0.6705882352941176, 1.0);
    else if(position.x < 0.35)
      color = vec4 (0.21568627450980393, 0.33725490196078434, 0.403921568627451, 1.0);
    else if(position.x < 0.4)
      color = vec4 (0.23137254901960785, 0.35294117647058826, 0.4235294117647059, 1.0);
    else if(position.x < 0.45)
      color = vec4 (0.12156862745098039, 0.26666666666666666, 0.3803921568627451, 1.0);
    else if(position.x < 0.5)
      color = vec4 (0.050980392156862744, 0.011764705882352941, 0.0, 1.0);
    else if(position.x < 0.55)
      color = vec4 (0.4, 0.5843137254901961, 0.7490196078431373, 1.0);
    else if(position.x < 0.6)
      color = vec4 (0.4196078431372549, 0.5843137254901961, 0.7333333333333333, 1.0);
    else if(position.x < 0.65)
      color = vec4 (0.2196078431372549, 0.3568627450980392, 0.42745098039215684, 1.0);
    else if(position.x < 0.7)
      color = vec4 (0.07058823529411765, 0.0392156862745098, 0.01568627450980392, 1.0);
    else if(position.x < 0.75)
      color = vec4 (0.13725490196078433, 0.28627450980392155, 0.403921568627451, 1.0);
    else if(position.x < 0.8)
      color = vec4 (0.03529411764705882, 0.027450980392156862, 0.0196078431372549, 1.0);
    else
      color = vec4(0.0, 0.0, 0.0, 0.0);
  }
  else if(position.y > 0.45){ // Linha 11
    if(position.x < 0.1)
      color = vec4(0.0, 0.0, 0.0, 0.0);
    else if(position.x < 0.15)
      color = vec4 (0.06274509803921569, 0.054901960784313725, 0.043137254901960784, 1.0);
    else if(position.x < 0.2)
      color = vec4 (0.596078431372549, 0.7647058823529411, 0.9215686274509803, 1.0);
    else if(position.x < 0.25)
      color = vec4 (1.0, 1.0, 1.0, 1.0);
    else if(position.x < 0.3)
      color = vec4 (0.1607843137254902, 0.29411764705882354, 0.36470588235294116, 1.0);
    else if(position.x < 0.4)
      color = vec4 (0.2235294117647059, 0.34901960784313724, 0.4196078431372549, 1.0);
    else if(position.x < 0.45)
      color = vec4 (0.23529411764705882, 0.3607843137254902, 0.42745098039215684, 1.0);
    else if(position.x < 0.5)
      color = vec4 (0.12941176470588237, 0.27058823529411763, 0.3843137254901961, 1.0);
    else if(position.x < 0.55)
      color = vec4 (0.07058823529411765, 0.043137254901960784, 0.0196078431372549, 1.0);
    else if(position.x < 0.6)
      color = vec4 (0.07450980392156863, 0.054901960784313725, 0.0392156862745098, 1.0);
    else if(position.x < 0.65)
      color = vec4 (0.08235294117647059, 0.054901960784313725, 0.0392156862745098, 1.0);
    else if(position.x < 0.7)
      color = vec4 (0.13333333333333333, 0.2784313725490196, 0.38823529411764707, 1.0);
    else if(position.x < 0.75)
      color = vec4 (0.13333333333333333, 0.2627450980392157, 0.3686274509803922, 1.0);
    else if(position.x < 0.8)
      color = vec4 (0.03529411764705882, 0.027450980392156862, 0.0196078431372549, 1.0);
    else
      color = vec4(0.0, 0.0, 0.0, 0.0);    
  }
  else if(position.y > 0.4){ // Linha 12
    if(position.x < 0.1)
      color = vec4(0.0, 0.0, 0.0, 0.0);
    else if(position.x < 0.15)
      color = vec4 (0.06274509803921569, 0.054901960784313725, 0.043137254901960784, 1.0);
    else if(position.x < 0.2)
      color = vec4 (0.40784313725490196, 0.5686274509803921, 0.7215686274509804, 1.0);
    else if(position.x < 0.25)
      color = vec4 (0.3686274509803922, 0.5372549019607843, 0.6901960784313725, 1.0);
    else if(position.x < 0.3)
      color = vec4 (0.21568627450980393, 0.33725490196078434, 0.403921568627451, 1.0);
    else if(position.x < 0.4)
      color = vec4 (0.2235294117647059, 0.34901960784313724, 0.4196078431372549, 1.0);
    else if(position.x < 0.45)
      color = vec4 (0.23529411764705882, 0.3607843137254902, 0.42745098039215684, 1.0);
    else if(position.x < 0.5)
      color = vec4 (0.12156862745098039, 0.24705882352941178, 0.34901960784313724, 1.0);
    else if(position.x < 0.65)
      color = vec4 (0.13333333333333333, 0.26666666666666666, 0.3686274509803922, 1.0);
    else if(position.x < 0.7)
      color = vec4 (0.12941176470588237, 0.2549019607843137, 0.35294117647058826, 1.0);
    else if(position.x < 0.75)
      color = vec4 (0.13333333333333333, 0.26666666666666666, 0.3686274509803922, 1.0);
    else if(position.x < 0.8)
      color = vec4 (0.03529411764705882, 0.027450980392156862, 0.0196078431372549, 1.0);
    else
      color = vec4(0.0, 0.0, 0.0, 0.0);
  }
  else if(position.y > 0.35){ // Linha 13
    if(position.x < 0.1)
      color = vec4(0.0, 0.0, 0.0, 0.0);
    else if(position.x < 0.15)
      color = vec4 (0.06274509803921569, 0.054901960784313725, 0.043137254901960784, 1.0);
    else if(position.x < 0.2)
      color = vec4 (0.23137254901960785, 0.37254901960784315, 0.45098039215686275, 1.0);
    else if(position.x < 0.25)
      color = vec4 (0.21176470588235294, 0.3333333333333333, 0.4, 1.0);
    else if(position.x < 0.3)
      color = vec4 (0.2235294117647059, 0.34901960784313724, 0.4196078431372549, 1.0);
    else if(position.x < 0.35)
      color = vec4 (0.23137254901960785, 0.3568627450980392, 0.4235294117647059, 1.0);
    else if(position.x < 0.4)
      color = vec4 (0.23529411764705882, 0.3607843137254902, 0.42745098039215684, 1.0);
    else if(position.x < 0.45)
      color = vec4 (0.11764705882352941, 0.24313725490196078, 0.34509803921568627, 1.0);
    else if(position.x < 0.5)
      color = vec4 (0.12941176470588237, 0.2549019607843137, 0.35294117647058826, 1.0);
    else if(position.x < 0.7)
      color = vec4 (0.12941176470588237, 0.2549019607843137, 0.35294117647058826, 1.0);
    else if(position.x < 0.75)
      color = vec4 (0.13725490196078433, 0.2784313725490196, 0.39215686274509803, 1.0);
    else if(position.x < 0.8)
      color = vec4 (0.01, 0.0, 0.0, 1.0);
    else
      color = vec4(0.0, 0.0, 0.0, 0.0);
  }
  else if(position.y > 0.3){ // Linha 14
    if(position.x < 0.15)
      color = vec4(0.0, 0.0, 0.0, 0.0);
    else if(position.x < 0.2)
      color = vec4 (0.06274509803921569, 0.054901960784313725, 0.043137254901960784, 1.0);
    else if(position.x < 0.25)
      color = vec4 (0.23921568627450981, 0.37254901960784315, 0.4470588235294118, 1.0);
    else if(position.x < 0.3)
      color = vec4 (0.23529411764705882, 0.3607843137254902, 0.42745098039215684, 1.0);
    else if(position.x < 0.65)
      color = vec4 (0.11764705882352941, 0.24313725490196078, 0.34509803921568627, 1.0);
    else if(position.x < 0.7)
      color = vec4 (0.13333333333333333, 0.26666666666666666, 0.3686274509803922, 1.0);
    else if(position.x < 0.75)
      color = vec4 (0.027450980392156862, 0.011764705882352941, 0.0, 1.0);
    else
      color = vec4(0.0, 0.0, 0.0, 0.0);
  }
  else if(position.y > 0.25){ // Linha 15
    if(position.x < 0.15)
      color = vec4(0.0, 0.0, 0.0, 0.0);
    else if(position.x < 0.2)
      color = vec4 (0.06274509803921569, 0.054901960784313725, 0.043137254901960784, 1.0);
    else if(position.x < 0.25)
      color = vec4 (0.13333333333333333, 0.27450980392156865, 0.38823529411764707, 1.0);
    else if(position.x < 0.65)
      color = vec4 (0.12941176470588237, 0.2549019607843137, 0.35294117647058826, 1.0);
    else if(position.x < 0.7)
      color = vec4 (0.13725490196078433, 0.2784313725490196, 0.39215686274509803, 1.0);
    else if(position.x < 0.75)
      color = vec4 (0.01, 0.0, 0.0, 1.0);
    else
      color = vec4(0.0, 0.0, 0.0, 0.0);
  }
  else if(position.y > 0.2){ // Linha 16
    if(position.x < 0.2)
      color = vec4(0.0, 0.0, 0.0, 0.0);
    else if(position.x < 0.25)
      color = vec4 (0.06274509803921569, 0.054901960784313725, 0.043137254901960784, 1.0);
    else if(position.x < 0.3)
      color = vec4 (0.13725490196078433, 0.2784313725490196, 0.39215686274509803, 1.0);
    else if(position.x < 0.6)
      color = vec4 (0.13333333333333333, 0.26666666666666666, 0.3686274509803922, 1.0);
    else if(position.x < 0.65)
      color = vec4 (0.13725490196078433, 0.2784313725490196, 0.39215686274509803, 1.0);
    else if(position.x < 0.7)
      color = vec4 (0.01, 0.0, 0.0, 1.0);
    else
      color = vec4(0.0, 0.0, 0.0, 0.0);
  }
  else if(position.y > 0.15){ // Linha 17
    if(position.x < 0.25)
      color = vec4(0.0, 0.0, 0.0, 0.0);
    else if(position.x < 0.3)
      color = vec4 (0.06274509803921569, 0.054901960784313725, 0.043137254901960784, 1.0);
    else if(position.x < 0.35)
      color = vec4 (0.027450980392156862, 0.011764705882352941, 0.0, 1.0);
    else if(position.x < 0.4)
      color = vec4 (0.13725490196078433, 0.2784313725490196, 0.39215686274509803, 1.0);
    else if(position.x < 0.5)
      color = vec4 (0.13333333333333333, 0.26666666666666666, 0.3686274509803922, 1.0);
    else if(position.x < 0.55)
      color = vec4 (0.13725490196078433, 0.2784313725490196, 0.39215686274509803, 1.0);
    else if(position.x < 0.65)
      color = vec4 (0.01, 0.0, 0.0, 1.0);
    else
      color = vec4(0.0, 0.0, 0.0, 0.0);
  }
  else if(position.y > 0.1){ // Linha 18
    if(position.x < 0.35)
      color = vec4(0.0, 0.0, 0.0, 0.0);
    else if(position.x < 0.4)
      color = vec4 (0.03137254901960784, 0.023529411764705882, 0.01568627450980392, 1.0);
    else if(position.x < 0.5)
      color = vec4 (0.09019607843137255, 0.08235294117647059, 0.0784313725490196, 1.0);
    else if(position.x < 0.55)
      color = vec4 (0.03137254901960784, 0.023529411764705882, 0.01568627450980392, 1.0);
    else
      color = vec4(0.0, 0.0, 0.0, 0.0);
      }
  else{
    color = vec4(0.0, 0.0, 0.0, 0.0);
  }
  dst = distance(position, fuse);
  color /= dst + 0.25 * abs(sin(time * 2.5));
  //color.g *= 1.05 * dst;
  gl_FragData[0] = color;
}
 

 
