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

static bool game_ended, beginning_of_game;
static unsigned long long end_moment;

MAIN_LOOP pong(void){
 LOOP_INIT:
  W.change_final_shader(5);
  if(W.game -> game_completed)
    W.final_shader_integer = 1;
  else
    W.final_shader_integer = 0;
  game_ended = false;
  beginning_of_game = true;
  initialize_paddle();
  initialize_score();
  initialize_ball();
  initialize_item();
 LOOP_BODY:
  if(W.keyboard[W_ESC])
    Wexit_loop();

  // First we check if someone scored
  {
    int score;
    if((score = score_ball())){
      if(score == 5 && !game_ended){
        game_ended = true;
        if(W.game -> players == 1){
          int player1_score = get_score(1);
          if(player1_score == 5){ // Player 1 won
            end_moment = W.t;
            W.play_sound(victory_sound);
          }
          else{ // Computer won
            game_ended = true;
            end_moment = W.t;
            W.play_sound(failure_sound);
            if(W.final_shader_integer < 10)
              W.final_shader_integer = 9;
            else
              W.final_shader_integer = 19;
          }
        }
        else{ // One of 2 players won
          end_moment = W.t;
          W.play_sound(victory_sound);
        }
      }
      else if(!game_ended){ // Someone marked a point, but the game didn't end
        W.play_sound(ball_miss);
        reset_ball();
      }
    }
  }

  // Player input
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

  // Check if ball collided, if not move it:
  if(!game_ended){
    if(collision_ball()){
      if(beginning_of_game && ball_dy != 0.0)
        beginning_of_game = false;
      // Check if we need to hide item
      if(!beginning_of_game && ball -> x > W.width / 2 &&
         item -> x > W.width / 2){
        hide_item();
      }
      else if(!beginning_of_game && ball -> x < W.width / 2 &&
         item -> x < W.width / 2){
        hide_item();
      }
    }
    else{
      update_ball();
    }
    // Animating items
    update_item();
  }
  
  // Checking for end of game:
  if(game_ended && ((W.t - end_moment > 3000000))){
    Wexit_loop();
  }
  
 LOOP_END:
  return;
}
