#include <iostream>
#include <utility>
#include <map>
#include <sstream>
#include <vector>
#include "Board.h"
#include "CreatePiece.h"
#include "Terminal.h"

using std::make_pair;
using std::cout;

/////////////////////////////////////
// DO NOT MODIFY THIS FUNCTION!!!! //
/////////////////////////////////////
Board::Board(){}

// non trivial destructor to deallocate pieces in the map
Board::~Board() {
  for(std::map<std::pair<char, char>, Piece*>::iterator it=occ.begin(); it!=occ.end(); ++it) {
    delete it->second; 
  }
}

// delete the actual piece object
void Board::free_piece(std::pair<char, char> pos) {
  if(occ[pos]!=nullptr) {
    delete occ[pos];
  }
}

// remove piece key from map
bool Board::remove_piece(std::pair<char,char> pos) {
  if (occ[pos] != nullptr) { // check if there actually is a piece there before deleting it
    occ[pos]=nullptr;
    occ.erase(pos);
    return true;
  }
  return false;
}

bool Board::move_piece(std::pair<char,char> start, std::pair<char,char> end) {
  free_piece(end); //deallocate piece at end if there is one there already
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

bool Board::has_valid_kings() const { 
  std::stringstream ss;
  ss << *this; //basically get_board()
  char c;
  int white_king = 0;
  int black_king = 0;
  while(ss >> c) {
    if(c == 'K')
      white_king++;
    else if(c == 'k')
      black_king++;
  }
  if(white_king == 1 && black_king == 1)
    return true;
  else return false;
}

void Board::display() const {
  cout << std::endl;
  // create a terminal object to change colors
  Terminal terminal;

  // in stringstream used as a buffer to hold contents of << board
  std::stringstream in;
  in << *this;
  
  std::string temp;
  char count = '8';
  while (in >> temp) {
    terminal.color_fg(true, terminal.GREEN);
    cout << count;
    terminal.set_default();
    cout << temp << std::endl;
    count--;
  }
  terminal.color_fg(true, terminal.RED);
  cout << "+ABCDEFGH"; 
  terminal.set_default();
  cout << std::endl;
}

// copy constructor
Board::Board(const Board& old) {
  Piece * p = nullptr;
  for(std::map<std::pair<char, char>, Piece*>::const_iterator it=old.occ.cbegin(); it!=old.occ.cend(); ++it) {
    if(it->second!=nullptr) {
      p = create_piece(it->second->to_ascii());
      occ[it->first]= p;
    }
  }
}

// assignment operator
Board& Board::operator=(const Board& old) {
  Piece * p = nullptr;
  std::vector<std::pair<char, char>> coords;
  for(std::map<std::pair<char, char>, Piece*>::iterator it=occ.begin(); it!=occ.end(); ++it) {
    if(it->second!=nullptr) {
      delete occ[it->first]; //free all pieces in board
      coords.push_back(it->first);
    }
  }
  for(unsigned i = 0; i < coords.size(); i++) {
    occ.erase(coords[i]);
  }
  for(std::map<std::pair<char, char>, Piece*>::const_iterator it=old.occ.cbegin(); it!=old.occ.cend(); ++it) {
    if(it->second!=nullptr) {
      p = create_piece(it->second->to_ascii()); //allocate memory for new pieces
      occ[it->first]=p;
    }
  }
  return *this;
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
