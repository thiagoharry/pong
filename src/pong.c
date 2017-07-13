/*
Copyright (c) harry,,,, 2017

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

#include "pong.h"

static bool game_ended;

MAIN_LOOP pong(void){
 LOOP_INIT:
  W.change_final_shader(5);
  if(W.game -> game_completed)
    W.final_shader_integer = 1;
  else
    W.final_shader_integer = 0;
  game_ended = false;
  initialize_paddle();
  initialize_score();
  
 LOOP_BODY:
  if(W.keyboard[W_ESC])
    Wexit_loop();
  if(W.keyboard[W_UP] && !game_ended){
    if(W.game -> players == 1)
      move_paddle(paddle1, W_UP, W.keyboard[W_UP], PADDLE_SPEED);
    else
      move_paddle(paddle2, W_UP, W.keyboard[W_UP], PADDLE_SPEED);
  }
  else if(W.keyboard[W_DOWN] && !game_ended){
    if(W.game -> players == 1)
      move_paddle(paddle1, W_DOWN, W.keyboard[W_DOWN], PADDLE_SPEED);
    else
      move_paddle(paddle2, W_DOWN, W.keyboard[W_DOWN], PADDLE_SPEED);
  }
  if(W.game -> players == 2){
    if(W.keyboard[W_W] && !game_ended)
      move_paddle(paddle1, W_UP, W.keyboard[W_W], PADDLE_SPEED);
    else if(W.keyboard[W_S] && !game_ended)
    move_paddle(paddle1, W_DOWN, W.keyboard[W_S], PADDLE_SPEED);
  }
 LOOP_END:
  return;
}
