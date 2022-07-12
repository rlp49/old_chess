/////////////////////////////////
// DO NOT MODIFY THIS FILE!!!! //
/////////////////////////////////
#include <cstddef>
#include "../header/CreatePiece.h"
#include "../header/Pawn.h"
#include "../header/Rook.h"
#include "../header/Knight.h"
#include "../header/Bishop.h"
#include "../header/Queen.h"
#include "../header/King.h"
#include "../header/Mystery.h"

Piece* create_piece(char piece_designator) {
	switch (piece_designator) {

	case 'K': return new King(true);
	case 'k': return new King(false);
	case 'Q': return new Queen(true);
	case 'q': return new Queen(false);
	case 'B': return new Bishop(true);
	case 'b': return new Bishop(false);
	case 'N': return new Knight(true);
	case 'n': return new Knight(false);
	case 'R': return new Rook(true);
	case 'r': return new Rook(false);
	case 'P': return new Pawn(true);
	case 'p': return new Pawn(false);
	case 'M': return new Mystery(true);
	case 'm': return new Mystery(false);
	default: return NULL;

	}
}
