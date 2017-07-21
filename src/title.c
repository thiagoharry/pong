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

#include "title.h"

#define TITLE_SHADER   1
#define START_SHADER   2
#define EXIT_SHADER    3

static struct interface *pong_title, *p1, *p2, *cursor;
#if W_TARGET == W_ELF
static struct interface *quit;
#endif
static int menu_selection;

// The title screen is entirely in the screen shader. We just set the
// custom shader to the entire screen:
MAIN_LOOP title(void){
 LOOP_INIT:
  {
    int y_position = 0.9 * W.height;
    if(y_position + 0.08 * W.height > W.height)
      y_position = W.height - 0.08 * W.height;
    pong_title = W.new_interface(TITLE_SHADER, W.width / 2, y_position,
                                 0.3 * W.width, 0.16 * W.height);
  }
  p1 = W.new_interface(START_SHADER, W.width / 2, 0.25 * W.height,
                         0.2 * W.width, 0.03 * W.height);
  p2 = W.new_interface(START_SHADER, W.width / 2, 0.2 * W.height,
                       0.2 * W.width, 0.03 * W.height);
#if W_TARGET == W_ELF
  quit = W.new_interface(EXIT_SHADER, W.width / 2, 0.15 * W.height,
                         0.1 * W.width, 0.03 * W.height);
#endif
  cursor = W.new_interface(W_INTERFACE_PERIMETER,
                           W.width / 2, 0.25 * W.height,
                           0.3 * W.width, 0.04 * W.height,
                           1.0, 1.0, 1.0, 1.0);
  // Loading all the sounds here and keeping them
  collision1 = W.new_sound("collision1.wav");
  collision2 = W.new_sound("collision2.wav");
  coin = W.new_sound("coin.wav");
  ball_miss = W.new_sound("ball_miss.wav");
  revelation = W.new_sound("revelation.wav");
  danger_sound = W.new_sound("danger.wav");
  restoration = W.new_sound("restore.wav");
  explosion_sound = W.new_sound("explosion.wav");
  failure_sound = W.new_sound("failure.wav");
  victory_sound = W.new_sound("victory.wav");
  menu_selection = 0;
  p1 -> integer = 1;
  p2 -> integer = 2;
  W.change_final_shader(4);
  if(W.game -> game_completed)
    W.final_shader_integer = 1;
 LOOP_BODY:
  if(W.keyboard[W_UP] == 1){
    if(menu_selection != 0){
      W.play_sound(collision1);
      menu_selection --;
      W.move_interface(cursor, cursor -> x, cursor -> y + 0.05 * W.height);
    }
  }
  else if(W.keyboard[W_DOWN] == 1){
    if(menu_selection !=
#if W_TARGET == W_ELF
       2
#else
       1
#endif
       ){
      W.play_sound(collision2);
      menu_selection ++;
      W.move_interface(cursor, cursor -> x, cursor -> y - 0.05 * W.height);
    }
  }
  else if(W.keyboard[W_ENTER] == 1){
    W.play_sound(coin);
    if(menu_selection == 0){
      W.game -> players = 1;
      Wsubloop(pong);
    }
    else if(menu_selection == 1){
      W.game -> players = 2;
      Wsubloop(pong);
    }
#if W_TARGET == W_ELF
    else if(menu_selection == 2){
      Wexit_loop();
    }
#endif
    if(W.game -> game_completed)
      W.final_shader_integer = 1;
  }
 LOOP_END:
  return;
}
