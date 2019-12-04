#include <iostream>
#include <utility>
#include <map>
#include "Board.h"
#include "CreatePiece.h"

using std::make_pair;
using std::cout;

/////////////////////////////////////
// DO NOT MODIFY THIS FUNCTION!!!! //
/////////////////////////////////////
Board::Board(){}

bool Board::in_check(bool white) const {
  // check if the king is threatened in the current board state
 
    // get location of the player's king
    pair<char, char> king;  
    if (white)
        king = white_king;
    else
        king = black_king;
    //cout << "location of king: " << king.first << king.second << endl; 
    // looping through the entire board to chech each piece
    for (char i = 'A'; i <= 'H'; i++) {
        for (char j = '1'; j <= '8'; j++) {
	        pair<char, char> piece = make_pair(i, j);
            //cout << "checking pair: " << piece.first << piece.second << endl; 
            if (board(piece) == nullptr) {
                //cout << "nothing at " << piece.first << piece.second << endl;
                continue; // pass if piece doesn't exist
            }

            if (board(piece)->is_white() == white || !board(piece)->is_white() == !white) {
                //cout << "piece at " << piece.first << piece.second << " is the same color" << endl;
                continue; // pass if piece is same color as the king
            }

        // only knight's can jump over other pieces so no need to check for in the way pieces
            if (tolower(board(piece)->to_ascii() == 'k') && 
                //cout << "piece at " << piece.first << piece.second << " is a knight" << endl;
                board(piece)->legal_capture_shape(piece, king)) {
                cout << "put in check by: " << piece.first << piece.second << endl;
                return true;
            }
        
        // for all other pieces
            if(board(piece)->legal_capture_shape(piece, king) && !itw(piece, king)) {
                cout << "put in check by: " << piece.first << piece.second << endl;
                return true; 
            }

            //cout << "piece: " << board(piece)->to_ascii() << " does not threaten king" << endl;
        }
    }
    return false;
}


bool Board::check_move(std::pair<char, char> start, std::pair<char, char> end) {
  // check if start is a piece
  const Piece* piece = board(start);
    bool othph = false;
    if (piece == nullptr)
        return false;
    
    // Check if the piece is the current player's piece 
    if (piece->is_white() != turn_white())
      return false
    
    // check if end is in bounds of board
    if (!(end.first >= 'A' && end.first <= 'H' && end.second >= '1' && end.second <= '8'))
      return false;
    
    //Check if Piece at end is of the same color
    if (board(end) != nullptr){
      if (piece->is_white() == board(end)->is_white())
				return false;
      else
				othph = true;
    }
    
    bool pawnall = true;
    if (tolower(piece->to_ascii()) == 'p'){
      if(othph){
				pawnall = false;
      }
    }
    
    // call valid_move for the piece
    if(piece->legal_move_shape(start, end) && pawnall){
      // if not knight, check if there are no pieces in between
      if(tolower(piece->to_ascii()) != 'n'){
				if (itw(start, end)) {
	  			return false; // if piece is in the way, return false
				}
      }
    }
    else if(tolower(piece->to_ascii()) == 'p' && !pawnall){
      if(!(piece->legal_capture_shape(start,end))){
	  		return false;
      }
    }
    else {
      return false;
    }
    // make the move
    Board board_old = board; // make a copy of old board in case we need to undo the move, make sure it has a copy constructor
    board.move_piece(start, end);
    
    // Check for if this move puts the player in check
    if(in_check(turn_white())){
      board = board_old; // revert to old board
        return false;
    }
    
    if(tolower(piece->to_ascii()) == 'p') {
      if(piece->is_white() && end.second == '8'){
				board.remove_piece(end);
				board.add_piece(end,'Q');
      }
      if(!piece->is_white() && end.second == '1'){
				board.remove_piece(end);
				board.add_piece(end,'q');
      }
    }
    
    // update location of king
    if(piece->to_ascii() == 'K')
        white_king = end;
    else if (piece->to_ascii() == 'k')
        black_king = end;

    is_white_turn = !is_white_turn;
    return true;
}


 bool Board::make_move(std::pair<char, char> start, std::pair<char, char> end)                                       // check if start is a piece
  const Piece* piece = board(start);
    bool othph = false;
    if (piece == nullptr)
      {
      cout << "No piece at starting pos" << endl;
        return false;
    }
    
    // Check if the piece is the current player's piece 
    if (piece->is_white() != turn_white())
      {
    cout << "Not your piece" << endl;
      return false;
    }
    
    // check if end is in bounds of board
    if (!(end.first >= 'A' && end.first <= 'H' && end.second >= '1' && end.second <= '8'))
      {
    cout << "end pos is out of bounds" << endl;
        return false;
      }
    
    //Check if Piece at end is of the same color
    if (board(end) != nullptr){
      if (piece->is_white() == board(end)->is_white()){
    cout << "Your piece occupies that square" << endl;
    return false;
      }
      else{
    othph = true;
      }
    }
    
    bool pawnall = true;
    if (tolower(piece->to_ascii()) == 'p'){
      if(othph){
    pawnall = false;
      }
    }
call valid_move for the piece
    if(piece->legal_move_shape(start, end) && pawnall){
      // if not knight, check if there are no pieces in between
      if(tolower(piece->to_ascii()) != 'n'){
    if (itw(start, end)) {
      cout << "Piece in the way" << endl;
      return false; // if piece is in the way, return false
    }
      }
    }
    else if(tolower(piece->to_ascii()) == 'p' && !pawnall){
      if
      (!(piece->legal_capture_shape(start,end))){
    cout << "Invalid Move" << endl;
      return false;
      }
    }
    else {
      cout << "Invalid Move" << endl;
      return false;
    }
    // make the move
    Board board_old = board; // make a copy of old board in case we need to undo the move, make sure it has a copy     constructor
    board.move_piece(start, end);
    
    // Check for if this move puts the player in check
    if(in_check(turn_white())){
      board = board_old; // revert to old board
        cout<< "That puts you in check"<<endl;
        return false;
    }
    
    if(tolower(piece->to_ascii()) == 'p') {
      if(piece->is_white() && end.second == '8'){
    board.remove_piece(end);
    board.add_piece(end,'Q');
      }
      if(!piece->is_white() && end.second == '1'){
    board.remove_piece(end);
    board.add_piece(end,'q');
      }
    }
    
    // update location of king
    if(piece->to_ascii() == 'K')
        white_king = end;
    else if (piece->to_ascii() == 'k')
        black_king = end;

    is_white_turn = !is_white_turn;
    return true;
}
bool Board::itw(pair<char, char> start, pair<char, char> end) const {
   int cFile = end.first - start.first;
   int cRank = end.second - start.second;
   int addF;
   int addR;

   if((abs(cFile) != abs(cRank)) && cFile != 0 && cRank != 0){
     return false;
   }

   //if knight, just return false
   //if(tolower(board(start)->to_ascii()) == 'n') return false;
   //maybe add other checks, if mystery piece is also a jumper? if time permits
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

   pair<char, char> steps = make_pair(start.first + addF, start.second + addR);
   while(!(steps.first == end.first && steps.second == end.second)) {
     if(board(steps) != nullptr) return true;
     steps = make_pair(steps.first + addF, steps.second + addR);

   }

   return false; // return false if no pieces in the way
 }


Board::Board(Board& old) {
    occ = old.occ;
}

bool Board::remove_piece(std::pair<char,char> pos) {
    if (occ[pos] != nullptr) { // check if there actually is a piece there before deleting it
        occ.erase(pos);
        return true;
    }
    return false;
}

bool Board::move_piece(std::pair<char,char> start, std::pair<char,char> end) {
    if (occ[end] != nullptr) // if end pos has a piece, need to delete it first
        delete occ[end];

    // move piece and delete start
    occ[end] = occ[start];
    remove_piece(start);

    return true;
}
//returns pointer to position if it exists on board
//returns nullptr if nothing's at that position
const Piece* Board::operator()(std::pair<char, char> position) const {
	if (occ.find(position) != occ.end())
        return occ.at(position);
    else
        return nullptr;
}

//adds piece with specified designator at the given position
//checks if: designator is valid, position is on board, and position is unoccupied
bool Board::add_piece(std::pair<char, char> position, char piece_designator) {
	if(position.first >= 'A' && position.first <= 'H' &&  //checks if on board
		 position.second >= '1' && position.second <= '8') {

		if(occ[position] != nullptr) //checks if pos already occupied
			return false;

        occ[position] = create_piece(piece_designator);

		if(occ[position] == nullptr) //checks if designator is valid
			return false;

		return true; //returns true if it passes all checks
	}
	return false;
}

//instructions only say to check if there are two kings,
//not necessarily of different colors, so...
bool Board::has_valid_kings() const {
	int count = 0;
	for(char r = '8'; r >= '1'; r--) {
		for(char c = 'A'; c <= 'H'; c++) {
			if(occ.at(make_pair(c,r))->to_ascii() == 'K' || occ.at(make_pair(c,r))->to_ascii() == 'k') 
				count += 1;
		}
	}	
	if(count == 2)
		return true;
}

void Board::display() const {
	cout << *this;
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

