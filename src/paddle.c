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

#include "paddle.h"

#define ABS(x) ((x<0)?(-x):(x))

static int ai_state1, ai_state2;

void initialize_paddle(void){
  paddle1 = W.new_interface(PADDLE_SHADER,
                            0.5 * PADDLE_WIDTH, W.height/2,
                            PADDLE_WIDTH, PADDLE_HEIGHT, // Largura e altura
                            1.0, 1.0, 1.0, 1.0);
  paddle2 = W.new_interface(PADDLE_SHADER,
                            W.width - 0.5 * PADDLE_WIDTH, W.height/2,
                            PADDLE_WIDTH, PADDLE_HEIGHT, // Largura e altura
                            1.0, 1.0, 1.0, 1.0);
  paddle1 -> r = 1.0;
  paddle1 -> g = paddle1 -> b = 0.0;
  paddle2 -> b = 1.0;
  paddle2 -> r = paddle2 -> g = 0.0;
  paddle1 -> integer = 0;
  paddle2 -> integer = 0;
  ai_state1 = 0;
  ai_state2 = 0;
}

// Speed is the paddle maximum speed, time is how long it's been
// moving
void move_paddle(struct interface *paddle, int direction, long time,
                 long speed){
  if(direction == W_DOWN){
    if(time > 500000){
      W.move_interface(paddle, paddle -> x, paddle -> y - speed);
    }
    else{
      W.move_interface(paddle, paddle -> x, paddle -> y -
                       (speed/2 + (int) (speed/2.0 *
                                         (float) time /
                                         500000.0)));
    }
  }
  else{
    if(time > 500000){
      W.move_interface(paddle, paddle -> x, paddle -> y + speed);
    }
    else{
      W.move_interface(paddle, paddle -> x, paddle -> y +
                       (speed/2 + (int) (speed/2.0 *
                                         (float) time /
                                         500000.0)));
    }
  }
    // Paddle movement correction
  if(paddle -> y <   paddle -> height / 2.0)
    W.move_interface(paddle, paddle -> x,
                     paddle-> height / 2.0);
  if(paddle -> y >  W.height - paddle -> height / 2.0)
    W.move_interface(paddle, paddle -> x,
                     W.height - paddle-> height / 2.0);
}

void paddle_ai(int paddle){
  int speed;
  int enemy_score;
  int *state;
  struct interface *pad;
  if(paddle == 1){
    enemy_score = get_score(2);
    pad = paddle1;
    state = &ai_state1;
  }
  else{
    enemy_score = get_score(1);
    pad = paddle2;
    state = &ai_state2;
  }
  speed = (int) (0.5 * PADDLE_SPEED + enemy_score * 0.5 * PADDLE_SPEED / 4.0);
  switch(enemy_score){
  case 0:
    if((ball_dx > 0.0 && ball_dx < 0.999 && paddle == 2) ||
       (ball_dx < 0.0 && ball_dx > -0.999 && paddle == 1)){
      if(*state == 0){ // Movendo pra cima
        if(pad -> y > 3 * pad -> height / 4 &&
           !(ball -> y > W.height / 2 && pad -> y < W.height / 2))
          W.move_interface(pad, pad -> x, pad -> y - speed);
        else
          *state = 1;
      }
      else{
        if(pad -> y < W.height - 3 * pad -> height / 4 &&
           !(ball -> y < W.height / 2 && pad -> y > W.height / 2))
          W.move_interface(pad, pad -> x, pad -> y + speed);
        else
          *state = 0;
      }
    }
    break;
  case 1:
    if((ball -> x > W.width / 2 && paddle == 2) ||
       (ball -> x < W.width / 2 && paddle == 1)){
      if((ball -> x > 7 * W.width / 8 && paddle == 2) ||
         (ball -> x < W.width / 8 && paddle == 1)){
        if(ball -> y > pad -> y + pad -> height / 2)
          W.move_interface(pad, pad -> x, pad -> y + speed);
        else if(ball -> y < pad -> y - pad -> height / 2)
          W.move_interface(pad, pad -> x, pad -> y - speed);
      }
      else if(ball -> y < W.height / 2 + W.height / 10 &&
         ball -> y > W.height / 2 - W.height / 10){
        // Detect ball in center
        if(pad -> y < W.height / 2  &&
           pad -> y + pad -> height / 3 < W.height / 2)
          W.move_interface(pad, pad -> x, pad -> y + speed);
        else if(pad -> y > W.height / 2 &&
                pad -> y - pad -> height / 3 > W.height / 2)
          W.move_interface(pad, pad -> x, pad -> y - speed);
      }
      else if(ball -> y > W.height / 2 + W.height / 10){
        // Ball in upper position
        if(pad -> y < 3 * W.height / 2 &&
           pad -> y + pad -> height / 2 < 3 * W.height / 4)
          W.move_interface(pad, pad -> x, pad -> y + speed);
      }
      else if(ball -> y < W.height / 2 - W.height / 10){
        // Ball in lower position
        if(pad -> y > W.height / 4 &&
           pad -> y + pad -> height / 2 > W.height / 4)
          W.move_interface(pad, pad -> x, pad -> y - speed);
      }
    }
    break;
  case 2:
    if((ball -> x > 9 * W.width / 10 && paddle == 2) ||
       (ball -> x < W.width / 10 && paddle == 1)){
      if(ball -> y > pad -> y + pad -> height / 2)
        W.move_interface(pad, pad -> x, pad -> y + speed);
      else if(ball -> y < pad -> y - pad -> height / 2)
        W.move_interface(pad, pad -> x, pad -> y - speed);
    }
    else if((ball -> x > W.width / 2 && paddle == 2) ||
            (ball -> x < W.width / 2 && paddle == 1)){
      if(ball -> y < W.height / 2 + W.height / 10 &&
         ball -> y > W.height / 2 - W.height / 10){
        if(pad -> y < W.height / 2 &&
           pad -> y + pad -> height / 2 < W.height / 2)
          W.move_interface(pad, pad -> x, pad -> y + speed);
        else if(pad -> y > W.height / 2 &&
                pad -> y > W.height / 2 - pad -> height / 2)
          W.move_interface(pad, pad -> x, pad -> y - speed);
      }
      else if(ball -> y > W.height / 2 + W.height / 10 &&
              ball -> y < 3 * W.height / 4){
        // Ball in upper position
        if(pad -> y < 3 * W.height / 2 &&
           pad -> y + pad -> height / 2 < 3 * W.height / 4)
          W.move_interface(pad, pad -> x, pad -> y + speed);
        else if(pad -> y - pad -> height / 2 > 3 * W.height / 4){
          W.move_interface(pad, pad -> x, pad -> y - speed);
        }
      }
      else if(ball -> y < W.height / 2 - W.height / 10 &&
              ball -> y > W.height / 4){
        // Ball in lower position
        if(pad -> y > W.height / 4 &&
           pad -> y + pad -> height / 2 > W.height / 4)
          W.move_interface(pad, pad -> x, pad -> y - speed);
        else if(pad -> y + pad -> height / 2 < W.height / 4)
          W.move_interface(pad, pad -> x, pad -> y + speed);
      }
      else if(ball -> y < W.height / 4){
        W.move_interface(pad, pad -> x, pad -> y - speed);
      }
      else if(ball -> y > 3 * W.height / 4){
        W.move_interface(pad, pad -> x, pad -> y + speed);
      }
    }
    break;
  case 3:
    if((ball -> x > W.width / 2 && ball_dx > 0.0 && paddle == 2) ||
       (ball -> x < W.width / 2 && ball_dx < 0.0 && paddle == 1)){
      if(ball -> y < pad -> y - pad -> height / 4)
        W.move_interface(pad, pad -> x, pad -> y - speed);
      else if(ball -> y > pad -> y + pad -> height / 4)
        W.move_interface(pad, pad -> x, pad -> y + speed);
    }
    break;
  default:
    if((ball_dx > 0.0 && paddle == 2) ||
       (ball_dx < 0.0 && paddle == 1)){
      float distance_x;
      if(paddle == 2){
        distance_x = W.width - ball -> x;
      }
      else{
        distance_x = - ball -> x;
      }
      float time = (float) distance_x / (ball_speed * ball_dx);
      float end_y = (float) ball -> y + time * (ball_speed * ball_dy);
      while(end_y < 0.0 || end_y > (float) W.height){
        if(end_y < 0){
          end_y *= -1;
        }
        else if(end_y > (float) W.height){
          end_y = (float) W.height - (end_y - (float) W.height); 
        }
      }
      if(pad -> y - pad -> height / 3 > end_y)
        W.move_interface(pad, pad -> x, pad -> y - speed);
      else if(pad -> y + pad -> height / 3 < end_y)
        W.move_interface(pad, pad -> x, pad -> y + speed);
    }
    break;
  }
      // Paddle movement correction
  if(pad -> y <   pad -> height / 2.0)
    W.move_interface(pad, pad -> x,
                     pad -> height / 2.0);
  if(pad -> y >  W.height - pad -> height / 2.0)
    W.move_interface(pad, pad -> x,
                     W.height - pad -> height / 2.0);
}
