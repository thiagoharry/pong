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

#ifndef _bomb_h_
#define _bomb_h_

#include "weaver/weaver.h"
#include "includes.h"

#define BOMB_SHADER 11

struct interface *bomb;

bool explosion;
int previous_screen;

void initialize_bomb(void);
void hide_bomb(void);
void show_bomb(void);
void blow_up_bomb(void);
void restore_screen_after_explosion(void);

#endif
