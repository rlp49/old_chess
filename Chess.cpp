#include "Chess.h"
#include <iostream>
#include <utility>

using std::cout; using std::endl;
using std::pair; using std::make_pair;

// added function itw() to check for in the way pieces
bool Chess::itw(pair<char, char> start, pair<char, char> end) const {
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

bool Chess::itw1(std::pair<char, char> start, std::pair<char, char> end, std::pair<char, char> was, std::pair<char, char> is) const {
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
    if(steps == was){

    }
    else if(steps == is){
      return true;
    }
    else if(board(steps) != nullptr){
      return true;
    }
    steps = make_pair(steps.first + addF, steps.second + addR);
    
  }
  
  return false; // return false if no pieces in the way
}


bool Chess::no_legal_moves(bool white) const{
  //Iterate through all peieces with every possible move
  pair<char,char> startm;
  pair<char,char> endm;
  
  for (char q = 'A'; q <='H'; q++){
    for (char z = '1'; z <='8'; z++) {
      startm =  make_pair(q,z);
      //std::cout << q << " " << z << std::endl;
      //std::cout <<"HERE"<<std::endl;
      if(board(startm)){//Finds is a piece exists
	if((white && board(startm)->is_white()) || !(white || board(startm)->is_white())){ // Check if it a piece that is the turns color
	  for (char a = 'A'; a <='H'; a++){
	    for (char b = '1'; b <='8'; b++) {
	      endm = make_pair(a,b);
	      // TODO compiler error here: check_move() is not const
	      if (check_move(startm , endm, white)){//checks every possible move for a legal move
		std::cout << q << " " << z << std::endl;
		std::cout << a << " " << b << std::endl << std::endl;;
		
		return false;// if a legal move is found the player is NOT in mate
	      }
	    }
	  }	
	}
      }
    }
  }
  return true;// if not legal moves are found they are in a mate
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

    // store location of kings
    black_king = std::pair<char, char>( 'A'+4 , '1'+7 );
    white_king = std::pair<char, char>( 'A'+4 , '1'+0 );
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
      std::cout<< "Here" << std::endl;
      if((!(piece->legal_capture_shape(start,end)))){
	std::cout<< "Here2" << std::endl;
	
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

//like make_move, but only used for checking mates
//avoid error messages
bool Chess::check_move(std::pair<char, char> start, std::pair<char, char> end, bool white) const {
  // check if start is a piece
  const Piece* piece = board(start);
    bool othph = false;
    if (piece == nullptr)
        return false;
    
    // Check if the piece is the current player's piece 
    if (piece->is_white() != turn_white())
      return false;
    
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

    bool kingm =false;
    if(tolower(piece->to_ascii()) == 'k'){
      kingm = true;
    }
    //std::cout<< "here" << std::endl;
    if(in_check1(white, start, end, kingm)){
      return false;
    }
    else{
      return true;
    }
    // make the move
    
}

bool Chess::in_check1(bool white,std::pair<char, char> was, std::pair<char, char> is, bool kingm) const {
  // check if the king is threatened in the current board state
  
  // get location of the player's king
  pair<char, char> king;  
  if (white)
    king = white_king;
  else
    king = black_king;

  if(kingm){
    king = is;
  }
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
      if (tolower(board(piece)->to_ascii() == 'k') &&  board(piece)->legal_capture_shape(piece, king)) {
	//cout << "put in check by: " << piece.first << piece.second << endl;
	return true;
      }
      
      // for all other pieces
      if(board(piece)->legal_capture_shape(piece, king) && !itw1(piece, king, was, is)) {
	//cout << "put in check by: " << piece.first << piece.second << endl;
	return true; 
      }
      
      //cout << "piece: " << board(piece)->to_ascii() << " does not threaten king" << endl;
    }
  }
  return false;
}




bool Chess::in_check(bool white) const {
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

// NOTE: if we want in_mate to be a const function we can't call check_move() inside it.
// Need to fix implementation. 
bool Chess::in_mate(bool white) const { 
  // Board nex = board;
  //return false;
  return(no_legal_moves(white) && in_check(white));
}


bool Chess::in_stalemate(bool white) const {
  //
  //Board nex = board;
  //return false;
  return (no_legal_moves(white) && !in_check(white));
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
	return is;
}
