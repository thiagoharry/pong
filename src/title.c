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

#include "title.h"

#define TITLE_SHADER   1
#define START_SHADER   2
#define EXIT_SHADER    3

static struct interface *pong, *p1, *p2, *quit, *cursor;
static int menu_selection;

struct sound *collision1, *collision2, *coin;

// The title screen is entirely in the screen shader. We just set the
// custom shader to the entire screen:
MAIN_LOOP title(void){
 LOOP_INIT:
  pong = W.new_interface(TITLE_SHADER, W.width / 2, W.height - 100,
                         250, 100);
  p1 = W.new_interface(START_SHADER, W.width / 2, 250,
                         200, 25);
  p2 = W.new_interface(START_SHADER, W.width / 2, 200,
                       200, 25);
  quit = W.new_interface(EXIT_SHADER, W.width / 2, 150,
                         100, 25);
  cursor = W.new_interface(W_INTERFACE_PERIMETER,
                           W.width / 2, 250,
                           210, 35,
                           1.0, 1.0, 1.0, 1.0);
  collision1 = W.new_sound("collision1.wav");
  collision2 = W.new_sound("collision2.wav");
  coin = W.new_sound("coin.wav");
  menu_selection = 0;
  p1 -> integer = 1;
  p2 -> integer = 2;
 LOOP_BODY:
  if(W.keyboard[W_UP] == 1){
    if(menu_selection != 0){
      W.play_sound(collision1);
      menu_selection --;
      W.move_interface(cursor, cursor -> x, cursor -> y + 50);
    }
  }
  else if(W.keyboard[W_DOWN] == 1){
    if(menu_selection != 2){
      W.play_sound(collision2);
      menu_selection ++;
      W.move_interface(cursor, cursor -> x, cursor -> y - 50);
    }
  }
  else if(W.keyboard[W_ENTER] == 1){
    W.play_sound(coin);
    if(menu_selection == 0){
      W.game -> players = 1;
    }
    else if(menu_selection == 1){
      W.game -> players = 1;
    }
    else if(menu_selection == 2){
      Wexit_loop();
    }
  }
 LOOP_END:
  return;
}
