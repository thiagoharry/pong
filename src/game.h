/*
Copyright (c) harry,,,, 2017

This file is part of pong.

pong is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

pong is distributed in the hope that it will be useful,
but WITHOUT ANY  WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS  FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more  details.

You should have received a copy of the GNU General Public License
along with pong. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _game_h_
#define _game_h_

#include "weaver/weaver.h"
#include "includes.h"

struct _game_struct{
  // You can personalize this struct putting your variables here. But
  // don't change it's name. Access it in W.game variable.

} _game;

MAIN_LOOP main_loop(void);

#endif
