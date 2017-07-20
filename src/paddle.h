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

#ifndef _paddle_h_
#define _paddle_h_

#include "weaver/weaver.h"
#include "includes.h"

#define PADDLE_SPEED (W.height/40)
#define PADDLE_WIDTH (W.width/40)
#define PADDLE_HEIGHT (W.height/7)

#define PADDLE_SHADER 6

struct interface *paddle1, *paddle2;

void initialize_paddle(void);
void move_paddle(struct interface *, int, long, long);
void paddle_ai(int);

#endif
