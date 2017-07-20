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

#include "score.h"

void initialize_score(void){
  score1 = W.new_interface(SCORE_SHADER,
                           0.375 * W.width, W.height - 100,
                           3 * PADDLE_WIDTH, 5 * W.height/27);
  score2 = W.new_interface(SCORE_SHADER,
                           0.625 * W.width, W.height - 100,
                           3 * PADDLE_WIDTH, 5 * W.height/27);

  if(W.game -> game_completed){
    score1 -> integer = 10;
    score2 -> integer = 10;
  }
  else{
    score1 -> integer = 0;
    score2 -> integer = 0;
  }
  
}

int get_score(int score){
  if(score == 1)
    return score1 -> integer % 10;
  else
    return score2 -> integer % 10;
}

void update_score(int score){
  if(score == 1 &&
     (score1 -> integer < 5 ||
      (score1 -> integer > 10 && score1 -> integer < 15)))
    score1 -> integer ++;
  else if(score == 2 &&
     (score2 -> integer < 5 ||
      (score2 -> integer > 10 && score2 -> integer < 15)))
    score2 -> integer ++;
}
