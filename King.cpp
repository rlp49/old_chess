#include "King.h"

bool King::legal_move_shape(std::pair<char, char> start, std::pair<char, char> end) const {
  int dx = end.first - start.first;
  int dy = end.second - start.second;
  
  if (dx*dx + dy*dy > 2)//checks if move is only one space away from the orginal square
    return false;
  else
    return true;
}

