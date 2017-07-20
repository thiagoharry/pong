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

#include "item.h"

void initialize_item(void){
  item = W.new_interface(ITEM_SHADER,
                         W.width - paddle2 -> width - 2 * ball -> width,
                         W.random() % W.height,
                         BALL_WIDTH / 2, BALL_WIDTH / 2,
                         1.0, 1.0, 1.0, 1.0);
  // The item shouldn' appear right in the ball way
  while(item -> y > W.height / 2 - BALL_WIDTH &&
        item -> y < W.height / 2 + BALL_WIDTH){
    W.move_interface(item, item -> x, W.random() % W.height);
  }
}

void update_item(void){
  if(item -> visible)
    W.rotate_interface(item, item -> rotation + 0.05);
}

void hide_item(void){
  item -> visible = false;
}

void show_item(void){
  int x_pos;
  if(ball -> x < W.width / 2)
    x_pos = W.width - paddle2 -> width - 2 * ball -> width;
  else
    x_pos = paddle2 -> width + 2 * ball -> width;
  item -> visible = true;
  W.move_interface(item, x_pos, W.random() % W.height);
}

void get_item(void){
  switch(number_of_items){
  case 0:
    paddle1 -> integer = 10;
    break;
  case 1:
    paddle2 -> integer = 10;
    break;
  case 2:
    ball -> integer = 1;
    break;
  case 3:
    score1 -> integer += 10;
    break;
  case 4:
    score2 -> integer += 10;
    break;
  default:
    W.final_shader_integer = 10;
    break;
  }
  W.play_sound(revelation);
  number_of_items ++;
  hide_item();
}
