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

#include "pong.h"

static bool game_ended, beginning_of_game;
static unsigned long long end_moment;
static int ball_old_x;
static unsigned long c;

MAIN_LOOP pong(void){
 LOOP_INIT:
  c = 0;
  W.change_final_shader(5);
  game_ended = false;
  beginning_of_game = true;
  in_danger = false;
  number_of_items = 0;
  initialize_paddle();
  initialize_score();
  initialize_ball();
  initialize_item();
  initialize_danger();
  initialize_bomb();
  if(W.game -> game_completed){
    W.final_shader_integer = 10;
    paddle1 -> integer = 10;
    paddle2 -> integer = 10;
    ball -> integer = 1;
    score1 -> integer = 10;
    score2 -> integer = 10;
  }
  else{
    W.final_shader_integer = 0;
  }
 LOOP_BODY:
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
            W.move_interface(ball, W.width, ball -> y);
            W.play_sound(victory_sound);
          }
          else{ // Computer won
            game_ended = true;
            end_moment = W.t;
            W.play_sound(failure_sound);
            W.move_interface(ball, 0.0, ball -> y);
            if(W.final_shader_integer < 10)
              W.final_shader_integer = 9;
            else
              W.final_shader_integer = 19;
          }
        }
        else{ // One of 2 players won
          end_moment = W.t;
          if(ball -> x > W.width / 2)
            W.move_interface(ball, W.width, ball -> y);
          else
            W.move_interface(ball, 0.0, ball -> y);
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
  if(W.keyboard[W_UP] > 0 && !game_ended){
    if(W.game -> players == 1)
      move_paddle(paddle1, W_UP, W.keyboard[W_UP], PADDLE_SPEED);
    else
      move_paddle(paddle2, W_UP, W.keyboard[W_UP], PADDLE_SPEED);
  }
  else if(W.keyboard[W_DOWN] > 0 && !game_ended){
    if(W.game -> players == 1)
      move_paddle(paddle1, W_DOWN, W.keyboard[W_DOWN], PADDLE_SPEED);
    else
      move_paddle(paddle2, W_DOWN, W.keyboard[W_DOWN], PADDLE_SPEED);
  }
  if(W.game -> players == 2){
    if(W.keyboard[W_W] > 0 && !game_ended)
      move_paddle(paddle1, W_UP, W.keyboard[W_W], PADDLE_SPEED);
    else if(W.keyboard[W_S] > 0 && !game_ended)
    move_paddle(paddle1, W_DOWN, W.keyboard[W_S], PADDLE_SPEED);
  }
  // Computer AI
  if(W.game -> players < 2)
    paddle_ai(2);
  
  // Check if ball collided, if not move it:
  ball_old_x = ball -> x;
  if(!game_ended){
    if(!explosion && collision_ball()){
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
      // Check if we need to hide danger:
      if(danger -> visible && ball -> x > W.width / 2 &&
         danger -> x > W.width / 2)
        hide_danger();
      else if(danger -> visible && ball -> x < W.width / 2 &&
              danger -> x < W.width / 2)
        hide_danger();
      // Check if we need to hide bomb:
      if(bomb -> visible && ball -> x > W.width / 2 &&
         bomb -> x > W.width / 2)
        hide_bomb();
      else if(bomb -> visible && ball -> x < W.width / 2 &&
              bomb -> x < W.width / 2)
        hide_bomb();
    }
    else{
      update_ball();
    }

    // Animating items
    update_item();

    // Ball crossed the screen center, going to left:
    if(ball_old_x >= W.width / 2 && ball -> x < W.width / 2){
      if(!game_ended){
        if(!(item -> visible) && number_of_items < 6){
          if(W.random() % 5 < 2)
            show_item(); // Regenerate item
        }
        if(!beginning_of_game && !(danger -> visible) && !in_danger){
          if(W.random() % 5 < 2)
            show_danger(); // Regenerate danger
        }
        if(get_score(1) == 4 && !(bomb -> visible) && !in_danger){
          if(W.random() % 5 == 0)
            show_bomb();
        }
      }
    }

    // Ball crossed the center, going right:
    if(ball_old_x < W.width / 2 && ball -> x >= W.width / 2){
      if(!game_ended && W.game -> players > 1){
        if(!(item -> visible) && number_of_items < 6){
          if(W.random() % 5 < 2)
            show_item(); // Regenerate item
        }
        if(!beginning_of_game && !(danger -> visible) && !in_danger){
          if(W.random() % 5 < 2)
            show_danger(); // Regenerate danger
        }
        if(get_score(2) == 4 && !(bomb -> visible) && !in_danger){
          if(W.random() % 5 == 0)
            show_bomb();
        }
      }
    }
  }

  // If we spent more than DANGER_TIME in danger, revert to normal.
  // And the ondulating screen is too evil to be allowed fot so much
  // time if the game is in the end.
  if(in_danger && ((W.t - danger_time > DANGER_TIME) ||
     ((W.final_shader_integer == 5 || W.final_shader_integer == 15) &&
      score1 -> integer == 4 && (W.t - danger_time > DANGER_TIME / 2)))){
    end_danger();
    in_danger = false;
  }
  // Handling explosion:
  if(explosion && bomb -> visible){
    struct interface *pad;
    if(bomb -> x > W.width / 2)
      pad = paddle2;
    else
      pad = paddle1;
    if(bomb -> width < 10.0 * BALL_WIDTH)
      W.resize_interface(bomb, bomb -> width *= 1.2, bomb -> height *= 1.2);
    else
      bomb -> visible = false;
    if(pad -> width < 20.0 * PADDLE_WIDTH)
      W.resize_interface(pad, pad -> width *= 1.2, pad -> height *= 1.1);
    else
      pad -> visible = false;
    if(pad -> integer == 0)
      pad -> integer = 1;
    else if(pad  -> integer == 10)
      pad -> integer = 11;
  }
  // Checking for end of game:
  if(game_ended &&
     ((!explosion && W.t - end_moment > 3000000) ||
      (W.t - end_moment > 5000000))){
    if(number_of_items >= 6 && W.game -> players == 1){
      W.game -> game_completed = true;
    }
    Wexit_loop();
  }

 LOOP_END:
  printf("%ld\n", c);
  return;
}
