#ifndef CHESS_H
#define CHESS_H

#include <iostream>
#include <utility>
#include "Piece.h"
#include "Board.h"

class Chess {

public:
  // This default constructor initializes a board with the standard
  // piece positions, and sets the state to white's turn
  Chess();
  
  // Returns a constant reference to the board 
  /////////////////////////////////////
  // DO NOT MODIFY THIS FUNCTION!!!! //
  /////////////////////////////////////
  const Board& get_board() const { return board; }
  
  // Returns true if it is white's turn
  /////////////////////////////////////
  // DO NOT MODIFY THIS FUNCTION!!!! //
  /////////////////////////////////////
  bool turn_white() const { return is_white_turn; }
  
  // Attemps to make a move. If successful, the move is made and
  // the turn is switched white <-> black
  bool make_move(std::pair<char, char> start, std::pair<char, char> end);
  
  // Returns true if the designated player is in check
  bool in_check(bool white) const;
  
  // Returns true if the designated player is in mate
  bool in_mate(bool white) const;
  
  // Returns true if the designated player is in mate
  bool in_stalemate(bool white) const;
  
  //helper function to check if a legal move exists
  bool check_move(std::pair<char, char> start, std::pair<char, char> end, bool white) const;
  // helper function to check if piece is in the way
  bool itw(std::pair<char, char> start, std::pair<char, char> end) const;
  //helper to check if legal moves exist
  bool no_legal_moves(bool white) const;

  bool itw1(std::pair<char, char> start, std::pair<char, char> end, std::pair<char, char> was, std::pair<char, char> is) const;

  bool in_check1(bool white,  std::pair<char, char> was, std::pair<char, char> is,bool kingm) const;
  //helper for << operator
  //void set_turn(char c);
  //Reads board in from a stream
  friend std::istream& operator>> (std::istream& is, Chess& chess);
  
private:
	// The board
	Board board;

	// Is it white's turn?
	bool is_white_turn;

    std::pair<char,char> black_king;
    std::pair<char,char> white_king;

};

// Writes the board out to a stream
std::ostream& operator<< (std::ostream& os, const Chess& chess);

/*
// Reads the board in from a stream
std::istream& operator>> (std::istream& is, Chess& chess);
*/

#endif // CHESS_H
