include "Pawn.h"

Pawn::Pawn(bool color){
  white = color;
}

bool Pawn::legal_capture_shape((std::pair<char, char> start, std::pair<char, char> end)) const {

  if (white){
    if (((start->first = end->first - 1) || (start->first = end->first + 1)) && (start->second == end->second -1)){
      return true;
    }
    else {
      return false;
    }
  }
  else {
    if (((start->first = end->first - 1) || (start->first = end->first + 1)) &&(start->second == end->second + 1)){
      return true;
    }
    else {
      return false;
    }
  }
}
