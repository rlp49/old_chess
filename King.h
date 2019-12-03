#ifndef KING_H
#define KING_H

#include "Piece.h"

class King : public Piece {

public:
	bool legal_move_shape(std::pair<char, char> start, std::pair<char, char> end) const {
		/////////////////////////
		// [REPLACE THIS STUB] //
		/////////////////////////
        int dx = end.first - start.first;
        int dy = end.second - start.second;

        if (dx*dx + dy*dy > 2)
            return false;
        else
            return true;
	}

	/////////////////////////////////////
	// DO NOT MODIFY THIS FUNCTION!!!! //
	/////////////////////////////////////
	char to_ascii() const {
		return is_white() ? 'K' : 'k';
	}

private:
	/////////////////////////////////////
	// DO NOT MODIFY THIS FUNCTION!!!! //
	/////////////////////////////////////
	King(bool is_white) : Piece(is_white) {}

	friend Piece* create_piece(char piece_designator);
};

#endif // KING_H
