#include "Chess.h"
#include <iostream>

using std::cout; using std::endl;

// added function itw() to check for in the way pieces
static bool itw(pair<char, char> start, pair<char, char> end) {
    int cFile = end->first - start->first;
    int cRank = end->second - start->second;
    int addF;
    int addR;
    
    if (cFile < 0)
        addF = -1;
    else if(cFile ==0)
        addF = 0;
    else
        addF = 1;
    
    if (cRank < 0)
        addR = -1;
    else if(cRank ==0)
        addR = 0;
    else
        addR = 1;
    
    int step = 1;
    while((step*addR != cRank) || (step*addF != cFile)){
        pair<char, char> steps = (start->first + step*addF, start->second + step*addR);
        if(ooc[steps])
            return false;
    }
}

/////////////////////////////////////
// DO NOT MODIFY THIS FUNCTION!!!! //
/////////////////////////////////////
Chess::Chess() : is_white_turn(true) {
	// Add the pawns
	for (int i = 0; i < 8; i++) {
		board.add_piece(std::pair<char, char>('A' + i, '1' + 1), 'P');
		board.add_piece(std::pair<char, char>('A' + i, '1' + 6), 'p');
	}

	// Add the rooks
	board.add_piece(std::pair<char, char>( 'A'+0 , '1'+0 ) , 'R' );
	board.add_piece(std::pair<char, char>( 'A'+7 , '1'+0 ) , 'R' );
	board.add_piece(std::pair<char, char>( 'A'+0 , '1'+7 ) , 'r' );
	board.add_piece(std::pair<char, char>( 'A'+7 , '1'+7 ) , 'r' );

	// Add the knights
	board.add_piece(std::pair<char, char>( 'A'+1 , '1'+0 ) , 'N' );
	board.add_piece(std::pair<char, char>( 'A'+6 , '1'+0 ) , 'N' );
	board.add_piece(std::pair<char, char>( 'A'+1 , '1'+7 ) , 'n' );
	board.add_piece(std::pair<char, char>( 'A'+6 , '1'+7 ) , 'n' );

	// Add the bishops
	board.add_piece(std::pair<char, char>( 'A'+2 , '1'+0 ) , 'B' );
	board.add_piece(std::pair<char, char>( 'A'+5 , '1'+0 ) , 'B' );
	board.add_piece(std::pair<char, char>( 'A'+2 , '1'+7 ) , 'b' );
	board.add_piece(std::pair<char, char>( 'A'+5 , '1'+7 ) , 'b' );

	// Add the kings and queens
	board.add_piece(std::pair<char, char>( 'A'+3 , '1'+0 ) , 'Q' );
	board.add_piece(std::pair<char, char>( 'A'+4 , '1'+0 ) , 'K' );
	board.add_piece(std::pair<char, char>( 'A'+3 , '1'+7 ) , 'q' );
	board.add_piece(std::pair<char, char>( 'A'+4 , '1'+7 ) , 'k' );
}

bool Chess::make_move(std::pair<char, char> start, std::pair<char, char> end) {
    // check if start is a piece
    Piece* piece = occ[start];
    if (piece == NULL)
    {
        cout << "No piece at starting pos" << endl;
        return false;
    }

    // Check if the piece is the current player's piece 
    if (piece->white != turn_white())
    {
        cout << "Not your piece" << endl;
        return false;
    }

    // check if end is in bounds of board
    if (!(end->first >= 'A' && end->first <= 'H' && end->second >= '1' && end->second <= '8'))
    {
        cout << "end pos is out of bounds" << endl;
        return false;
    }

    //Check if Piece at end is of the same color
    if (occ[end]){
        if (ooc[start]->is_white() == ooc[end]->is_white()){
	        cout << "Your piece occupies that square" << endl;
	        return false;
        }
    }

    

    // call valid_move for the piece
    if(ooc[start].legal_move_shape(start, end)){
        // if not knight, check if there are no pieces in between
        if(ooc[start].to_ascii != 'N' && ooc[start].to_ascii != 'n'){
            int cFile = end->first - start->first;
	        int cRank = end->second - start->second;
	        int addF;
	        int addR;
	        
            if (cFile < 0){
	            addF = -1;
	        }
            else if(cFile ==0){
	            addF = 0;
	        }
            else{
	            addF = 1;
	        }
	        
            if (cRank < 0){
                addR = -1;
            }
            else if(cRank ==0){
                addR = 0;
            }
            else{
                addR = 1;
            }
	        
            int step = 1;
	        while((step*addR != cRank) || (step*addF != cFile)){
	            pair<char, char> steps = (start->first + step*addF, start->second + step*addR);
	            if(ooc[steps]){
	                cout << "piece is in the way" << endl;
	                return false;
	            }
	        }
        }
    }
    else if(ooc[start].to_ascii() == 'P' || ooc.to_ascii() == 'p'){
        if (!ooc[start].legal_capture_shape(start,end)){
	        cout << "Invalid Move" << endl;
	        return false;
        }
    }

    // move by swapping pointer of start and end, set start to note
    Piece* temp = ooc[end];
    ooc[end] = ooc[start];
    ooc[start] = NULL;

    // Check for if this move puts the player in check
    if(in_check(turn_white)){
      ooc[start] = ooc[end];
      ooc[end] = temp;
      cout<< "That puts you in check"<<endl;
      return false;
    }
    return true;
}


bool Chess::in_check(bool white) const {
    // check if the king is threatened in the current board state

    // TODO Direct check. Test if the king is currently in check from the opponents move.
    pair<char, char> prev;  // game needs to somehow keep track on the previous move as a field
    pair<char, char> king;  // also should keep track of king as a field or loop through board to find manually
    
    // returns true if prev has a legal move to capture and no peice in the way (if not rook)
    if (tolower(ooc[prev].to_ascii() == 'p'))
        return ooc[prev].legal_capture_shape(prev, king) && !itw(prev, king); // if prev is a pawn
    else if (tolower(ooc[prev].to_ascii() == 'r'))
        return ooc[prev].legal_capture_shape(prev, king); // if prev is a rook
    else
        return ooc[prev].legal_capture_shape(prev, king) && !itw(prev, king); // if prev is anything else

    // TODO Discovered check. Test if the king is put into check by your own move.
    bool in_check = false;
    
    // looping through the entire board to chech each piece
    for (int i = 0; i < 8; i++) {
        for (int j = 0; i < 8; j++) {
            if (in_check) // return if we already found piece that puts king in check
                return true;

            pair<char, char> piece = make_pair(i+'A', j+'0');
            if (ooc[piece].is_white() != white) { // check if piece in board tho opposite player's 
                if (tolower(ooc[piece].to_ascii() == 'p'))
                    in_check = ooc[piece].legal_capture_shape(piece, king) && !itw(piece, king);
                else if (tolower(ooc[piece].to_ascii() == 'r'))
                    in_check = ooc[piece].legal_capture_shape(piece, king);
                else
                    in_check = ooc[piece].legal_capture_shape(piece, king) && !itw(piece, king); 
            }
        }
    }
                    
	return false;
}


bool Chess::in_mate(bool white) const {
	/////////////////////////
	// [REPLACE THIS STUB] //
	/////////////////////////
	return false;
}


bool Chess::in_stalemate(bool white) const {
    return (in_mate(white) != in_check(white));
}


/////////////////////////////////////
// DO NOT MODIFY THIS FUNCTION!!!! //
/////////////////////////////////////
std::ostream& operator<< (std::ostream& os, const Chess& chess) {
	// Write the board out and then either the character 'w' or the character 'b',
	// depending on whose turn it is
	return os << chess.get_board() << (chess.turn_white() ? 'w' : 'b');
}


std::istream& operator>> (std::istream& is, Chess& chess) {
	/////////////////////////
	// [REPLACE THIS STUB] //
	/////////////////////////
	return is;
}
