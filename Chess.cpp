#include "Chess.h"
#include <iostream>
#include <utility>
#include <vector>
#include <cassert>

using std::cout; using std::endl;
using std::pair; using std::make_pair;
using std::vector;

// overloaded itw()
bool Chess::itw(pair<char, char> start, pair<char, char> end, Board& board) const {
  int cFile = end.first - start.first; //how many files ahead the end pos is
  int cRank = end.second - start.second; //how many ranks ahead the end pos is
  int addF;
  int addR;
  
	//jumping piece, ignore itw
  if((abs(cFile) != abs(cRank)) && cFile != 0 && cRank != 0){
    return false;
  }
  
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
  
	//checks if there's a piece in each pos b/w start and end
  pair<char, char> steps = make_pair(start.first + addF, start.second + addR);
  while(!(steps.first == end.first && steps.second == end.second)) {
    if(board(steps) != nullptr) return true;
    steps = make_pair(steps.first + addF, steps.second + addR);
    
  }
  
  return false; // return false if no pieces in the way
}

// added function itw() to check for in the way pieces
bool Chess::itw(pair<char, char> start, pair<char, char> end) const {
  int cFile = end.first - start.first; //how many files ahead the end pos is
  int cRank = end.second - start.second; //how many ranks ahead the end pos is
  int addF;
  int addR;
  
	// if piece jumps, return false
  if((abs(cFile) != abs(cRank)) && cFile != 0 && cRank != 0){
    return false;
  }
  
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
  
	//checks each square between start and end for pieces in the way
  pair<char, char> steps = make_pair(start.first + addF, start.second + addR);
  while(!(steps.first == end.first && steps.second == end.second)) {
    if(board(steps) != nullptr) return true;
    steps = make_pair(steps.first + addF, steps.second + addR);
  }
  
  return false; // return false if no pieces in the way
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
  const Piece* piece = board(start);
    bool capture_piece = false; // true when there is a piece at end pos to be captured 
    if (piece == nullptr) {
      cout << "No piece at starting pos" << endl;
      return false;
    }
    
    // Check if the piece is the current player's piece 
    if (piece->is_white() != turn_white()) {
			cout << "Not your piece" << endl;
      return false;
    }
    
    // check if end is in bounds of board
    if (!(end.first >= 'A' && end.first <= 'H' && end.second >= '1' && end.second <= '8')) {
			cout << "end pos is out of bounds" << endl;
        return false;
    }
    
    //Check if move results in capture 
    if (board(end) != nullptr) {
      if (piece->is_white() == board(end)->is_white()) {
				cout << "Your piece occupies that square" << endl;
				return false;
      }
      else
				capture_piece = true; // set capture_piece = true if exists piece at end pos that is not same color
    }
    
		// pawn_capture tells us if we need to call legal_capture instead of legal_move 
    bool pawn_capture = false;
    if (tolower(piece->to_ascii()) == 'p') {
      if(capture_piece)
				pawn_capture = true;
    }
    
    // call valid_move for the piece
    if(piece->legal_move_shape(start, end) && !pawn_capture) {
      // Check if there are no pieces in between
			if(itw(start, end)) {
	  		cout << "Piece in the way" << endl;
	  		return false; // if piece is in the way, return false
			}
    }
    else if(tolower(piece->to_ascii()) == 'p' && pawn_capture) {
      if((!(piece->legal_capture_shape(start,end)))) { 	
				cout << "Invalid Move" << endl;
	  	return false;
      }
    }
    else {
      cout << "Invalid Move" << endl;
      return false;
    }
	
    // make the move
    Board board_old = board; // make a copy of old board in case we need to undo the move
    board.move_piece(start, end);
    
    // Check for if this move puts the player in check
    if(in_check(turn_white())) {
      board = board_old; // revert to old board
      cout << "That puts you in check" << endl;
      return false;
    }
 
  	// pawn promotion
    if(tolower(piece->to_ascii()) == 'p') {
      if(piece->is_white() && end.second == '8') {
	board.free_piece(end);
				board.remove_piece(end);
				board.add_piece(end,'Q');
      }
      else if(!piece->is_white() && end.second == '1') {
	board.free_piece(end);
				board.remove_piece(end);
				board.add_piece(end,'q');
      }
    }
    
		//changes turn
    is_white_turn = !is_white_turn;
    return true;
}

// the overloaded make_move()
// does same thing as make_move() but modifies a passed in board instead of this.board
bool Chess::make_move(std::pair<char, char> start, std::pair<char, char> end, Board& board) const {
  const Piece* piece = board(start);
  bool capture_piece = false;
    
  if (piece == nullptr) {
    return false;
  }
    
  // Check if the piece is the current player's piece 
  if (piece->is_white() != turn_white()) {
    return false;
  }
    
  // check if end is in bounds of board
  if (!(end.first >= 'A' && end.first <= 'H' && end.second >= '1' && end.second <= '8')) {
    return false;
  }
    
  //Check if Piece at end is of the same color
  if (board(end) != nullptr) {
    if (piece->is_white() == board(end)->is_white())
		  return false;
    else 
	  	capture_piece = true;
  }
    
  bool pawn_capture = false;
  if (tolower(piece->to_ascii()) == 'p') {
    if(capture_piece)
			pawn_capture = true;
  }
    
  // call valid_move for the piece
  if(piece->legal_move_shape(start, end) && !pawn_capture) {
	  if(itw(start, end, board)) 
	  	return false; // if piece is in the way, return false
  }
  else if(tolower(piece->to_ascii()) == 'p' && pawn_capture) {
      if(!(piece->legal_capture_shape(start,end)))
	  		return false;
  }
  else 
    return false;
 
  // make the move
  board.move_piece(start, end);
    
  // Check for if this move puts the player in check
  if(in_check(turn_white(), board))
    return false;   
    
  //pawn promotion
  if(tolower(piece->to_ascii()) == 'p') {
    if(piece->is_white() && end.second == '8') {
			board.remove_piece(end);
			board.add_piece(end,'Q');
    }
    else if(!piece->is_white() && end.second == '1') {
			board.remove_piece(end);
			board.add_piece(end,'q');     
		}
  }
    
  return true;
}

// calls legal_capture() on all of the opponent's pieces to see if they can capture the king
bool Chess::in_check(bool white) const {
	//finds location of the king
  pair<char, char> king;  
  for(char i = 'A'; i <= 'H'; i++) {
    for(char j = '1'; j <= '8'; j++) {
      pair<char,char> piece = make_pair(i,j);
      if(board(piece) == nullptr) 
        continue;
      if(board(piece)->to_ascii() == 'K' && white) {
        king = piece;
        break;
      }
      if (board(piece)->to_ascii() == 'k' && !white) {
        king = piece;
        break;
      }
    }
  }
   
  // looping through the entire board to check each piece
  for(char i = 'A'; i <= 'H'; i++) {
    for(char j = '1'; j <= '8'; j++) {
	    pair<char, char> piece = make_pair(i, j);
      if(board(piece) == nullptr) 
        continue; // pass if piece doesn't exist
      if(board(piece)->is_white() == white || !board(piece)->is_white() == !white) 
        continue; // pass if piece is same color as the king
      // checks if king in check
      if(board(piece)->legal_capture_shape(piece, king) && !itw(piece, king)) {
        cout << "put in check by: " << piece.first << piece.second << endl;
        return true; 
  		}
    }
  }
  return false;
}

// overloaded in_check()
// does same thing as in_check() but on a passed in board
bool Chess::in_check(bool white, Board& board) const {
  pair<char, char> king;  
  // loop to find the king
  for(char i = 'A'; i <= 'H'; i++) {
    for(char j = '1'; j <= '8'; j++) {
      pair<char,char> piece = make_pair(i,j);
      if(board(piece) == nullptr)
        continue;
      if(board(piece)->to_ascii() == 'K' && white) {
        king = piece;
        break;
      }
      if(board(piece)->to_ascii() == 'k' && !white) {
        king = piece;
        break;
      }
    }
  }
  // see if any opponent pieces can capture king
  for(char i = 'A'; i <= 'H'; i++) {
    for(char j = '1'; j <= '8'; j++) {
	    pair<char, char> piece = make_pair(i, j);
      if(board(piece) == nullptr) 
        continue; // pass if piece doesn't exist
      if(board(piece)->is_white() == white || !board(piece)->is_white() == !white)
        continue; // pass if piece is same color as the king
      // checks if king is in check
      if(board(piece)->legal_capture_shape(piece, king) && !itw(piece, king, board)) 
        return true; 
    }
  }
  return false;
}

// checks for legal moves for all pieces, returns true if no legal moves found
bool Chess::in_stalemate(bool white) const {
  Board board = this->board; // make a copy of the board
  vector<pair<char,char>> pieces; // vector storing pieces to check moves with
  
  // first get the position of all current turn player's pieces
  for(char i = 'A'; i <= 'H'; i++) {
    for(char j = '1'; j <= '8'; j++) {
      pair<char,char> piece = make_pair(i,j);
      if(this->board(piece) == nullptr)
        continue;
     
      // add the pieces to the vector if same color as current turn 
      if(this->board(piece)->is_white() == white || !this->board(piece)->is_white() == !white)
        pieces.push_back(piece);
    }
  }

  // try to make moves with the pieces in vector
  for(unsigned i = 0; i < pieces.size(); i++) {
    pair<char,char> cur = pieces[i]; // current piece to check moves with    
    for (char j = 'A'; j <= 'H'; j++) {
      for (char k = '1'; k <= '8'; k++) {
        pair<char,char> move = make_pair(j,k); // create a possible move
        Board old = board; // make a copy of board to undo the move
        if (make_move(cur, move, board)) 
          return false; // if move was succesful and not in check anymore      
        board = old; // restore previous board to undo the move 
      }
    }
  }
  return true; // if no possible moves found, return true
}

// in_mate is basically stalemate but king is currently in_check()
bool Chess::in_mate(bool white) const {
  return (in_check(white) && in_stalemate(white)); 
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
  //clearing current board
  std::pair<char, char> coord;
  for(char i = 'A'; i <= 'H'; i++) {
    for(char j = '1'; j <= '8'; j++) {
      coord = make_pair(i, j);
      chess.board.free_piece(coord);
      chess.board.remove_piece(coord);
    }
  }

  // populate board from text file
  char c=' ';
  for(char k = '8'; k >= '1'; k--) {
    for(char l = 'A'; l <= 'H'; l++) {
      is.get(c);
      coord = make_pair(l, k);
      if(c=='p'||c=='P'||c=='k'||c=='K'||c=='n'||c=='N'||c=='q'||c=='Q'||c=='r'||c=='R'||c=='b'||c=='B'||c=='M'||c=='m') {
        chess.board.add_piece(coord, c);
      }
	}
    is.get(c);
  }
  is.get(c);
  if(c == 'w') 
    chess.is_white_turn = true;
  if(c == 'b') 
    chess.is_white_turn = false;

  return is;
}   
