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

#ifndef _item_h_
#define _item_h_

#define ITEM_SHADER 9

#include "weaver/weaver.h"
#include "includes.h"

struct interface *item;

int number_of_items;

void initialize_item(void);
void update_item(void);
void hide_item(void);
void show_item(void);
void get_item(void);

#endif
