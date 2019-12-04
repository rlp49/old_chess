#ifndef QUEEN_H
#define QUEEN_H

#include "Piece.h"
#include <cmath>
#include <iostream>

class Queen : public Piece {

public:
  ~Queen(){
    std::cout << "object being deleted" << std::endl;
  }
	bool legal_move_shape(std::pair<char, char> start, std::pair<char, char> end) const {
        // combination of rook and bishop
	  if ((start.first == end.first || start.second == end.second) || (abs(start.first - end.first) == abs(start.second - end.second))){

	    return true;
	  }
	  else{
	    return false;
	  }
	}
  
	/////////////////////////////////////
	// DO NOT MODIFY THIS FUNCTION!!!! //
	/////////////////////////////////////
	char to_ascii() const {
		return is_white() ? 'Q' : 'q';
	}

private:
	/////////////////////////////////////
	// DO NOT MODIFY THIS FUNCTION!!!! //
	/////////////////////////////////////
	Queen(bool is_white) : Piece(is_white) {}

	friend Piece* create_piece(char piece_designator);
};

#endif // QUEEN_H
