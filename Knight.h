#ifndef KNIGHT_H
#define KNIGHT_H

#include "Piece.h"

class Knight : public Piece {

public:
  virtual ~Knight(){}
	bool legal_move_shape(std::pair<char, char> start, std::pair<char, char> end) const {
		if((end.first == start.first + 2 && 
				(end.second == start.second + 1 || end.second == start.second - 1)) ||
			 (end.first == start.first - 2 &&
				(end.second == start.second + 1 || end.second == start.second - 1)) ||
			 (end.second == start.second + 2 &&
				(end.first == start.first + 1 || end.first == start.first + 1)) ||
			 (end.second == start.second - 2 &&
				(end.first == start.first + 1 || end .first == start.first + 1))) {
			return true;
		}
		return false;
	}
	
	/////////////////////////////////////
	// DO NOT MODIFY THIS FUNCTION!!!! //
	/////////////////////////////////////
	char to_ascii() const {
		return is_white() ? 'N' : 'n';
	}

private:
	/////////////////////////////////////
	// DO NOT MODIFY THIS FUNCTION!!!! //
	/////////////////////////////////////
	Knight(bool is_white) : Piece(is_white) {}

	friend Piece* create_piece(char piece_designator);
};

#endif // KNIGHT_H
