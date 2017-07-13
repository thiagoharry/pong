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

#ifndef _ball_h_
#define _ball_h_

#include "weaver/weaver.h"
#include "includes.h"

#define BALL_SHADER 8

#define BALL_WIDTH (W.width/40)
#define BALL_HEIGHT (W.height/27)
#define BALL_SPEED ((float) PADDLE_SPEED*((float) W.width / (float) W.height) * \
                    0.9)

struct interface *ball;

float ball_speed, ball_dx, ball_dy;

void initialize_ball(void);
int score_ball(void);
void reset_ball(void);
bool collision_ball(void);
void update_ball(void);

#endif
