#include "Pawn.h"

bool Pawn::legal_move_shape(std::pair<char, char> start, std::pair<char, char> end) const {
  if (is_white()){//since Black and white Pawns behave differently
    if(start.second == (end.second - 1) && start.first == end.first){ //Checks the move is only forward 1
      return true;
    }
    else if(start.second == '2' && end.second == '4' && start.first == end.first){// Checks for the two move
      return true;
    }
    else {
      return false;
    }
  }
  else {// Same as above for blacks perspective
    if(start.second == (end.second + 1) && start.first == end.first){
      return true;
    }
    else if(start.second == '7' && end.second == '5' && start.first == end.first){
      return true;
    }
    else {
      return false;
    }
  }
}
bool Pawn::legal_capture_shape(std::pair<char, char> start, std::pair<char, char> end) const{
  
  if (is_white()){
    if (((start.first == (end.first - 1)) || (start.first == (end.first + 1))) && (start.second == (end.second - 1))){ // Checks for legal caputre of 1 up and 1 to right or left
      return true;
    }
    else {
      return false;
    }
  }
  else {
    if (((start.first == (end.first - 1)) || (start.first == (end.first + 1))) && (start.second == (end.second + 1))){ //Same as before but from blacks perspective
      return true;
    }
    else {
      return false;
    }
  }
}



