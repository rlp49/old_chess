#ifndef MYSTERY_H
#define MYSTERY_H

#include "Piece.h"

class Mystery : public Piece {

//moves in 3x2; think knight but bigger
public:
  virtual ~Mystery(){}
	bool legal_move_shape(std::pair<char, char> start, std::pair<char, char> end) const {
		if((end.first == start.first + 3 && 
				(end.second == start.second + 2 || end.second == start.second - 2)) ||
			 (end.first == start.first - 3 &&
				(end.second == start.second + 2 || end.second == start.second - 2)) ||
			 (end.second == start.second + 3 &&
				(end.first == start.first + 2 || end.first == start.first - 2)) ||
			 (end.second == start.second - 3 &&
				(end.first == start.first + 2 || end .first == start.first - 2))) {
			return true;
		}
		return false;
	}
	
	/////////////////////////////////////
	// DO NOT MODIFY THIS FUNCTION!!!! //
	/////////////////////////////////////
	char to_ascii() const {
		return is_white() ? 'M' : 'm';
	}

private:
	/////////////////////////////////////
	// DO NOT MODIFY THIS FUNCTION!!!! //
	/////////////////////////////////////
	Mystery(bool is_white) : Piece(is_white) {}

	friend Piece* create_piece(char piece_designator);
};

#endif // MYSTERY_H
