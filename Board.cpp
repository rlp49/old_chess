#include <iostream>
#include <utility>
#include <map>
#include "Board.h"
#include "CreatePiece.h"


/////////////////////////////////////
// DO NOT MODIFY THIS FUNCTION!!!! //
/////////////////////////////////////
Board::Board(){}

//returns pointer to position if it exists on board
//returns nullptr if nothing's at that position
const Piece* Board::operator()(std::pair<char, char> position) const {
	if (occ.find(position) != occ.end())
        return occ[position];
    else
        return nullptr;
}

//adds piece with specified designator at the given position
//checks if: designator is valid, position is on board, and position is unoccupied
bool Board::add_piece(std::pair<char, char> position, char piece_designator) {
	char ch = piece_designator;
	if(position.first >= 'A' && position.first <= 'H' &&  //checks if on board
		 position.second >= '1' && position.second <= '8') {

		if(occ[position] != nullptr) //checks if pos already occupied
			return false;

        Piece piece = create_piece(piece_designator);

		occ[position] = &piece; // fixed this, occ[pos] should be a pointer
		if(occ[position] = nullptr) //checks if designator is valid
			return false;

		return true; //returns true if it passes all checks
	}
	return false;
}

//instructions only say to check if there are two kings,
//not necessarily of different colors, so...
bool Board::has_valid_kings() const {
	int count = 0
	for(char r = '8'; r >= '1'; r--) {
		for(char c = 'A'; c <= 'H'; c++) {
			if(occ[(c, r)] == 'K' || occ[(c, r)] == 'k') 
				count += 1;
		}
	}	
	if(count == 2)
		return true;
}

void Board::display() const {
	cout << board;
}

/////////////////////////////////////
// DO NOT MODIFY THIS FUNCTION!!!! //
/////////////////////////////////////
std::ostream& operator<<(std::ostream& os, const Board& board) {
	for(char r = '8'; r >= '1'; r--) {
		for(char c = 'A'; c <= 'H'; c++) {
			const Piece* piece = board(std::pair<char, char>(c, r));
			if (piece) {
				os << piece->to_ascii();
			} else {
			  os << '-';
			}
		}
		os << std::endl;
	}
	return os;
}

