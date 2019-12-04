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
  int cFile = end.first - start.first;
  int cRank = end.second - start.second;
  int addF;
  int addR;
  
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
  
  pair<char, char> steps = make_pair(start.first + addF, start.second + addR);
  while(!(steps.first == end.first && steps.second == end.second)) {
    if(board(steps) != nullptr) return true;
    steps = make_pair(steps.first + addF, steps.second + addR);
    
  }
  
  return false; // return false if no pieces in the way
}

// added function itw() to check for in the way pieces
bool Chess::itw(pair<char, char> start, pair<char, char> end) const {
  int cFile = end.first - start.first;
  int cRank = end.second - start.second;
  int addF;
  int addR;
  
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
Chess::Chess() : is_white_turn(true) { // constructor for Chess
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
    
    // call valid_move for the piece
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
    Board board_old = board; // make a copy of old board in case we need to undo the move, make sure it has a copy constructor
    board.move_piece(start, end);
    
    // Check for if this move puts the player in check
    if(in_check(turn_white())){
      board = board_old; // revert to old board
        cout<< "That puts you in check"<<endl;
        return false;
    }
 
  // pawn promotion
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
    
    is_white_turn = !is_white_turn;
    return true;
}

// the overloaded make_move()
bool Chess::make_move(std::pair<char, char> start, std::pair<char, char> end, Board& board) const {
  const Piece* piece = board(start);
  bool othph = false;
    
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
    if (board(end) != nullptr){
      if (piece->is_white() == board(end)->is_white()){
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
    
    // call valid_move for the piece
    if(piece->legal_move_shape(start, end) && pawnall){
      // if not knight, check if there are no pieces in between
      if(tolower(piece->to_ascii()) != 'n'){
	if (itw(start, end, board)) {
	  return false; // if piece is in the way, return false
	}
      }
    }
    else if(tolower(piece->to_ascii()) == 'p' && !pawnall){
      if
      (!(piece->legal_capture_shape(start,end))){
	  return false;
      }
    }
    else {
      return false;
    }
    // make the move
    board.move_piece(start, end);
    
    // Check for if this move puts the player in check
    if(in_check(turn_white(), board)){
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
    
    return true;
}

bool Chess::in_check(bool white) const {
    pair<char, char> king;  
    for (char i = 'A'; i <= 'H'; i++) {
      for (char j = '1'; j <= '8'; j++) {
        pair<char,char> piece = make_pair(i,j);
        if (board(piece) == nullptr) {
          continue;
        }
        if (board(piece)->to_ascii() == 'K' && white) {
          king = piece;
          break;
        }
        if (board(piece)->to_ascii() == 'k' && !white) {
          king = piece;
          break;
        }
      }
    }
    cout << "location of king: " << king.first << king.second << endl; 
    // looping through the entire board to chech each piece
    for (char i = 'A'; i <= 'H'; i++) {
        for (char j = '1'; j <= '8'; j++) {
	        pair<char, char> piece = make_pair(i, j);
            //cout << "checking pair: " << piece.first << piece.second << endl; 
            if (board(piece) == nullptr) {
                continue; // pass if piece doesn't exist
            }

            if (board(piece)->is_white() == white || !board(piece)->is_white() == !white) {
                continue; // pass if piece is same color as the king
            }

        // only knight's can jump over other pieces so no need to check for in the way pieces
            if (tolower(board(piece)->to_ascii() == 'n')) { 
              if (board(piece)->legal_capture_shape(piece, king)) {
                cout << "put in check by: " << piece.first << piece.second << endl;
                return true;
              }
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

// overloaded in_check()
bool Chess::in_check(bool white, Board& board) const {
   //cout << "running overloaded in_check()" << endl; 
    pair<char, char> king;  
    // loop to find the king
    for (char i = 'A'; i <= 'H'; i++) {
      for (char j = '1'; j <= '8'; j++) {
        pair<char,char> piece = make_pair(i,j);
        if (board(piece) == nullptr)
          continue;
        if (board(piece)->to_ascii() == 'K' && white) {
          king = piece;
          break;
        }
        if (board(piece)->to_ascii() == 'k' && !white) {
          king = piece;
          break;
        }
      }
    }

    // see if any opponent pieces can capture king
    for (char i = 'A'; i <= 'H'; i++) {
        for (char j = '1'; j <= '8'; j++) {
	        pair<char, char> piece = make_pair(i, j);
            if (board(piece) == nullptr) {
                continue; // pass if piece doesn't exist
            }

            if (board(piece)->is_white() == white || !board(piece)->is_white() == !white) {
                continue; // pass if piece is same color as the king
            }

        // only knight's can jump over other pieces so no need to check for in the way pieces
            if (tolower(board(piece)->to_ascii() == 'n') && 
                board(piece)->legal_capture_shape(piece, king)) {
                //cout << "put in check by: " << piece.first << piece.second << endl;
                return true;
            }
        
        // for all other pieces
            if(board(piece)->legal_capture_shape(piece, king) && !itw(piece, king, board)) {
                //cout << "put in check by: " << piece.first << piece.second << endl;
                return true; 
            }

        }
    }
    return false;
}

// checks for legal moves for all pieces, returns true if no legal moves found
bool Chess::in_stalemate(bool white) const { 
  Board board = this->board;
  vector<pair<char,char>> pieces; // vector storing pieces to check moves with
  
  // first for loop gets a vector of pieces
  for (char i = 'A'; i <= 'H'; i++) {
    for (char j = '1'; j <= '8'; j++) {
      pair<char,char> piece = make_pair(i,j);
      
      if (this->board(piece) == nullptr)
        continue;
      
      // check if same color
      if (this->board(piece)->is_white() == white || !this->board(piece)->is_white() == !white)
        pieces.push_back(piece);
    }
  }

  // second for loop makes moves with the pieces in vector
  for (int i = 0; i < pieces.size(); i++) {
    pair<char,char> cur = pieces[i]; // current piece to check moves with
    cout << "checking piece " << cur.first << cur.second << endl;    
    for (char j = 'A'; j <= 'H'; j++) {
      for (char k = '1'; k <= '8'; k++) {
        pair<char,char> move = make_pair(j,k); // create a possible move
        Board old = board; // make a copy of board to undo the move
        if (make_move(cur, move, board)) {
          cout << "Not in checkmate. You can move: " << cur.first << cur.second << " to " << move.first << move.second << endl;
          cout << board;
          return false; // if move was succesful and not in check anymore
        }
        board = old; // need asignment operator
      }
    }
  }
  return true;
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
      chess.board.remove_piece(coord);
    }
  }
  
  char c;
  for(char k = '8'; k >= '1'; k--) {
    for(char l = 'A'; l <= 'H'; l++) {
      is.get(c);
      //std::cout << c;
      coord = make_pair(l, k);
      if(c=='p'||c=='P'||c=='k'||c=='K'||c=='n'||c=='N'||c=='q'||c=='Q'||c=='r'||c=='R'||c=='b'||c=='B') {
        chess.board.add_piece(coord, c);
      }
    }
    is.get(c);
    //std::cout << c;
  }
  is.get(c);
  if(c == 'w') 
    chess.is_white_turn = true;
  if(c == 'b') 
    chess.is_white_turn = false;

  // need to implement way to put move commands from .txt
  return is;
}   
