#include "../header/Queen.h"


bool Queen::legal_move_shape(std::pair<char, char> start, std::pair<char, char> end) const {
  // combination of rook and bishop
  if ((start.first == end.first || start.second == end.second) || (abs(start.first - end.first) == abs(start.second - end.second))){
    return true;
  }
  else{
    return false;
  }
}
