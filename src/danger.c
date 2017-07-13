/*
Copyright (c) Thiago "Harry" Leucz Astrizi, 2017

This file is part of pong.

pong is free software: you can redistribute it and/or modify
it under the terms of the GNU Affero General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

pong is distributed in the hope that it will be useful,
but WITHOUT ANY  WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS  FOR A PARTICULAR PURPOSE.  See the
GNU Affero General Public License for more  details.

You should have received a copy of the GNU Affero General Public License
along with pong. If not, see <http://www.gnu.org/licenses/>.
*/

#include "danger.h"

void initialize_danger(void){
  danger = W.new_interface(DANGER_SHADER,
                         W.width - paddle2 -> width - 2 * ball -> width,
                         W.random() % W.height,
                         BALL_WIDTH / 2, BALL_WIDTH / 2,
                         1.0, 1.0, 1.0, 1.0);
  danger -> visible = false;
}

void show_danger(void){
  int x_pos;
  if(ball -> x < W.width / 2)
    x_pos = W.width - paddle2 -> width - 2 * ball -> width;
  else
    x_pos = paddle2 -> width + 2 * ball -> width;
  danger -> visible = true;
  W.move_interface(danger, x_pos, W.random() % W.height);
}

void get_danger(void){
  // Cloud (2), smaller paddle (8), pods, dancing screen, ondulating screen,
  // upside down screen (1), rainbow (6), new (7)
  
  int danger_type = (W.random() % 8) + 1;
  W.play_sound(danger_sound);
  in_danger = true;
  danger_time = W.t;
  if(danger_type != 8)
    W.final_shader_integer += danger_type;
  else{
    if(danger -> x > W.width / 2)
      W.resize_interface(paddle1, paddle1 -> width, 0.5 * paddle1 -> height);
    else
      W.resize_interface(paddle2, paddle2 -> width, 0.5 * paddle2 -> height);
  }
}

void end_danger(void){
    if(W.final_shader_integer >= 10)
      W.final_shader_integer = 10;
    else
      W.final_shader_integer = 0;
    if(paddle1 -> height != PADDLE_HEIGHT)
      W.resize_interface(paddle1, paddle1 -> width, PADDLE_HEIGHT);
    if(paddle2 -> height != PADDLE_HEIGHT)
      W.resize_interface(paddle2, paddle2 -> width, PADDLE_HEIGHT);
    W.play_sound(restoration);
}

void hide_danger(void){
  danger -> visible = false;
}
