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
