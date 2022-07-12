#include "../header/Rook.h"

bool Rook::legal_move_shape(std::pair<char, char> start, std::pair<char, char> end) const {
  if(start.first == end.first || start.second == end.second) {
    //need to check if rook stays on same rank or file between start and end
    return true;
  }
  return false;
}
