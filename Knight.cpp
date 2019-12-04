#include "Knight.h"

bool Knight::legal_move_shape(std::pair<char, char> start, std::pair<char, char> end) const {
  if((end.first == start.first + 2 &&
      (end.second == start.second + 1 || end.second == start.second - 1)) ||
     (end.first == start.first - 2 &&
      (end.second == start.second + 1 || end.second == start.second - 1)) ||
     (end.second == start.second + 2 &&
      (end.first == start.first + 1 || end.first == start.first - 1)) ||
     (end.second == start.second - 2 &&
      (end.first == start.first + 1 || end .first == start.first - 1))) {
    return true;//This brute force checks all 8 L shaped moves the knight can make
  }
  return false;
}
