#ifndef PAWN_H
#define PAWN_H

#include "Piece.h"

class Pawn : public Piece {

public:
  bool legal_move_shape(std::pair<char, char> start, std::pair<char, char> end) const {
    if (is_white()){
      if(start.second == (end.second - 1) && start.first == end.first){
	return true;
      }
      else if(start.second == '2' && end.second == '4' && start.first == end.first){
	return true;
      }
      else {
	return false;
      }
    }
    else {
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
  bool legal_capture_shape(std::pair<char, char> start, std::pair<char, char> end) const{
    
    if (is_white()){
      if (((start.first == (end.first - 1)) || (start.first == (end.first + 1))) && (start.second == (end.second -1))){
	return true;
      }
      else {
	return false;
      }
    }
    else {
      if (((start.first == (end.first - 1)) || (start.first == (end.first + 1))) && (start.second == (end.second + 1))){
	return true;
      }
      else {
	return false;
      }
    }
  }
  


    
	/////////////////////////////////////
	// DO NOT MODIFY THIS FUNCTION!!!! //
	/////////////////////////////////////
	char to_ascii() const {
		return is_white() ? 'P' : 'p';
	}

private:
	/////////////////////////////////////
	// DO NOT MODIFY THIS FUNCTION!!!! //
	/////////////////////////////////////
	Pawn(bool is_white) : Piece(is_white) {}

	friend Piece* create_piece(char piece_designator);
};

#endif // PAWN_H
