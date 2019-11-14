#ifndef BISHOP_H
#define BISHOP_H

#include "Piece.h"
#include <cmath.h>

class Bishop : public Piece {

public:
	bool legal_move_shape(std::pair<char, char> start, std::pair<char, char> end) const {
        
        // Bishop can only move diaganolly, so check if slope is 1
        if (abs(start->first - end->fist) == abs(start->second - end->second))
            return true;
        else
		    return false;
	}

	/////////////////////////////////////
	// DO NOT MODIFY THIS FUNCTION!!!! //
	/////////////////////////////////////
	char to_ascii() const {
		return is_white() ? 'B' : 'b';
	}

private:
	/////////////////////////////////////
	// DO NOT MODIFY THIS FUNCTION!!!! //
	/////////////////////////////////////
	Bishop(bool is_white) : Piece(is_white) {}

	friend Piece* create_piece(char piece_designator);
};

#endif // BISHOP_H
