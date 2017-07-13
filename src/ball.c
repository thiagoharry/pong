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

#include "ball.h"

static bool collision_sound;

void initialize_ball(void){
  ball =  W.new_interface(BALL_SHADER,
                          W.width/2, W.height/2,
                          BALL_WIDTH, BALL_HEIGHT, // Windth and height
                          1.0, 1.0, 1.0, 1.0);
  // Ball stars with 1/2 of the speed of paddles and moves vertially:
  ball_speed = 0.5 * (float) BALL_SPEED;
  ball_dx = 1.0; ball_dy = 0.0;
  collision_sound = 0;
}

// Checks if the ball is out of bonds because someone marked a point)
int score_ball(void){
  int ret = 0;
  int who_scored;
  if(ball -> x < 0){
    // Paddle 2 scored
    ball_dx = 1.0;
    ball_dy = 0.0;
    update_score(2);
    ret = get_score(2);
    who_scored = 2;
  }
  else if(ball -> x > W.width){
    // Paddle 1 scored
    ball_dx = -1.0;
    ball_dy = 0.0;
    update_score(1);
    ret = get_score(1);
    who_scored = 1;
  }
  if(ret){
    hide_item();
    hide_danger();
    // the ball speed should be slower now in some cases
    if((W.game -> players == 1 && who_scored == 2) ||
       W.game -> players > 1){
      int speed_multiplier;
      float new_speed;
      if(W.game -> players == 1){
        speed_multiplier = get_score(1) - 1;
        if(speed_multiplier < 1)
          return ret;
        else{
          new_speed = ball_speed +
            (0.5 + 0.375 * (score1 -> integer - 1)) * BALL_SPEED;
          if(new_speed < ball_speed)
            ball_speed = new_speed;
        }
      }
      else{
        ball_speed = ((0.5 * BALL_SPEED) + ball_speed) / 2.0;
      }
    }
  }
  return ret;
}

void reset_ball(void){
  W.move_interface(ball, 0.5 * W.width, 0.5 * W.height);
}

bool collision_ball(void){
  bool ret = false;
  // Testing collision with paddle 2:
  if(ball_dx > 0 && ball -> x + 0.5 * BALL_WIDTH > W.width - PADDLE_WIDTH &&
     ball -> y < paddle2 -> y + 0.5 * (paddle2 -> height + BALL_HEIGHT) &&
     ball -> y > paddle2 -> y - 0.5 * (paddle2 -> height + BALL_HEIGHT)){
    float angle = 0.25 * M_PI * ((ball -> y - paddle2 -> y) /
                                 (paddle2 -> height + BALL_HEIGHT));
    W.move_interface(ball, W.width - PADDLE_WIDTH - 0.5 * BALL_WIDTH, ball -> y);
    // Change direction after collision
    ball_dy = sinf(angle);
    ball_dx = cosf(angle);
    if(ball_dx > 0) ball_dx *= -1;
    // Adjusting ball speed
    ball_speed += 0.01 * BALL_SPEED;
    ret = true;
  }
  // Testing collision with paddle 1:
  else if(ball_dx < 0 && ball -> x - 0.5 * BALL_WIDTH < PADDLE_WIDTH &&
          ball -> y < paddle1 -> y + 0.5 * (paddle1 -> height + BALL_HEIGHT) &&
          ball -> y > paddle1 -> y - 0.5 * (paddle1 -> height + BALL_HEIGHT)){
    float angle = 0.25 * M_PI * ((ball -> y - paddle1 -> y) /
                                 (paddle1 -> height + BALL_HEIGHT));
    W.move_interface(ball, PADDLE_WIDTH + 0.5* BALL_WIDTH, ball -> y);
    // Change direction after collision:
    ball_dy = sinf(angle);
    ball_dx = cosf(angle);
    if(ball_dx < 0) ball_dx *= -1;
    ball_speed += 0.01 * BALL_SPEED;
    ret = true;
  }
  if(ret){
    // Limit ball speed
    if(W.game -> players == 1){
      if(ball_speed > (0.5 + 0.375 * get_score(1)) * BALL_SPEED)
        ball_speed = (0.5 + 0.375 * get_score(1)) * BALL_SPEED;
    }
    else{
      if(ball_speed > (0.5 + 0.375 * 4) * BALL_SPEED)
        ball_speed = (0.5 + 0.375 * 4) * BALL_SPEED;
    }
    collision_sound = !collision_sound;
    if(collision_sound)
      W.play_sound(collision1);
    else
      W.play_sound(collision2);
  }
  return ret;
}

void update_ball(void){
  W.move_interface(ball, ball -> x + ball_dx * ball_speed,
                   ball -> y + ball_dy * ball_speed);
  // Ball collision with upper and lower screen:
  if(ball -> y < 0.5 * BALL_HEIGHT){
    W.move_interface(ball, ball -> x, 0.5 * BALL_HEIGHT);
    if(ball_dy < 0) ball_dy *= -1;
    collision_sound = !collision_sound;
    if(collision_sound)
      W.play_sound(collision1);
    else
      W.play_sound(collision2);
  }
  else if(ball -> y > W.height - 0.5 * BALL_HEIGHT){
    W.move_interface(ball, ball -> x, W.height - 0.5 * BALL_HEIGHT);
    if(ball_dy > 0) ball_dy *= -1;
    collision_sound = !collision_sound;
    if(collision_sound)
      W.play_sound(collision1);
    else
      W.play_sound(collision2);
  }
  // Ball collision with item:
  if(item -> visible){
    float dst = sqrtf((ball -> x - item -> x) * (ball -> x - item -> x) +
                      (ball -> y - item -> y) * (ball -> y - item -> y));
    if(dst < BALL_WIDTH * 1.1){
      get_item();
    }
  }
  // Ball collision with danger
  if(danger -> visible){
    float dst = sqrtf((ball -> x - danger -> x) * (ball -> x - danger -> x) +
                      (ball -> y - danger -> y) * (ball -> y - danger -> y));
    if(dst < BALL_WIDTH * 1.1){
      get_danger();
      danger -> visible = false;
    }
  }
}
