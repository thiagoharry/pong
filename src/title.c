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

#define TITLE_SHADER 1
#define START_SHADER 2
#define EXIT_SHADER  3

struct interface *pong, *p1, *p2, *quit;

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
  p1 -> integer = 1;
  p2 -> integer = 2;
  //W.change_final_shader(TITLE_SHADER);
 LOOP_BODY:
  if(W.keyboard[W_ANY])
    Wexit_loop();
 LOOP_END:
  return;
}
