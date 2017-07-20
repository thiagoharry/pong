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

#include "bomb.h"

void initialize_bomb(void){
  bomb = W.new_interface(BOMB_SHADER,
                         W.width - paddle2 -> width - 2 * ball -> width,
                         W.random() % W.height,
                         BALL_WIDTH / 2, BALL_WIDTH / 2,
                         1.0, 1.0, 1.0, 1.0);
  bomb -> visible = false;
  explosion = false;
}

void hide_bomb(void){
  bomb -> visible = false;
}

void show_bomb(void){
  bomb -> visible = true;
  if(ball -> x < W.width / 2){
    W.move_interface(bomb, W.width - paddle2 -> width - 2 * ball -> width,
                     W.random() % W.height);
  }
  else{
    W.move_interface(bomb, paddle1 -> width + 2 * ball -> width,
                     W.random() % W.height);
  }
  bomb -> visible = true;
}

void blow_up_bomb(void){
  explosion = true;
  W.play_sound(explosion_sound);
  previous_screen = W.final_shader_integer;
  W.final_shader_integer = 20;
  W.run_futurelly(restore_screen_after_explosion, 0.1);
}

void restore_screen_after_explosion(void){
  W.final_shader_integer = previous_screen;
}
