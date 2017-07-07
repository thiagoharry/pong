/*
Copyright (c) Thiago Leucz Astrizi 2017

This file is part of pong.

pong is free software: you can redistribute it and/or modify
it under the terms of the GNU Affero General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

pong is distributed in the hope that it will be useful,
but WITHOUT ANY  WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS  FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more  details.

You should have received a copy of the GNU General Public License
along with pong. If not, see <http://www.gnu.org/licenses/>.
*/

#include "game.h"


// This is the first main loop. It's used to load all the sound files
// in the beginning and keep them loaded during all the game.
MAIN_LOOP main_loop(void){ // The game loop
 LOOP_INIT: // Code executed during loop initialization
  Wsubloop(title);
 LOOP_BODY: // Code executed every loop iteration
  Wexit_loop();

 LOOP_END: // Code executed at the end of the loop
  return;
}

int main(void){
  Winit(); // Initializes Weaver

  //copyleft();
  Wloop(main_loop);
  return 0;
}
