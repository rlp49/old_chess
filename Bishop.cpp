#include "Bishop.h"


bool Bishop::legal_move_shape(std::pair<char, char> start, std::pair<char, char> end) const {
   
   // Bishop can only move diaganolly, so check if slope is 1
   if (abs(start.first - end.first) == abs(start.second - end.second))
      return true;
    else
      return false;
 }
