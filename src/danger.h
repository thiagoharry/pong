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

#ifndef _danger_h_
#define _danger_h_

#include "weaver/weaver.h"
#include "includes.h"

#define DANGER_SHADER 10

#define DANGER_TIME 10000000ul

struct interface *danger;

void initialize_danger(void);
void show_danger(void);
void hide_danger(void);
void end_danger(void);
void get_danger(void);

#endif
