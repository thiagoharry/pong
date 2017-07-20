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

#ifndef _title_h_
#define _title_h_

#include "includes.h"
#include "weaver/weaver.h"

struct sound *collision1, *collision2, *ball_miss, *revelation,
  *danger_sound, *restoration, *explosion_sound, *failure_sound,
  *victory_sound, *coin;

MAIN_LOOP title(void);

#endif
