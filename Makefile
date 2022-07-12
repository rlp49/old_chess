CC=g++
CFLAGS=-std=c++11 -pedantic -Wall -Wextra

# Someone double check the makefile!!!

# target executable
chess.exe: object/main.o object/Chess.o object/Board.o object/CreatePiece.o object/Pawn.o object/Rook.o object/Knight.o object/Bishop.o object/Queen.o object/King.o
	$(CC) -o chess.exe object/main.o object/Chess.o object/Board.o object/CreatePiece.o object/Pawn.o object/Rook.o object/Knight.o object/Bishop.o object/Queen.o object/King.o

# target object files
object/main.o: class/main.cpp header/Chess.h header/Board.h header/CreatePiece.h
	$(CC) $(CFLAGS) -o object/main.o -c class/main.cpp -g

object/Chess.o: class/Chess.cpp header/Chess.h 
	$(CC) $(CFLAGS) -o object/Chess.o -c class/Chess.cpp -g

object/Board.o: class/Board.cpp header/Board.h header/CreatePiece.h header/Terminal.h
	$(CC) $(CFLAGS) -o object/Board.o -c class/Board.cpp -g

object/CreatePiece.o: class/CreatePiece.cpp header/CreatePiece.h header/Pawn.h header/Rook.h header/Knight.h header/Bishop.h header/Queen.h header/King.h header/Mystery.h
	$(CC) $(CFLAGS) -o object/CreatePiece.o -c class/CreatePiece.cpp -g

object/Pawn.o: class/Pawn.cpp header/Pawn.h
	$(CC) $(CFLAGS) -o object/Pawn.o -c class/Pawn.cpp

object/Rook.o: class/Rook.cpp header/Rook.h
	$(CC) $(CFLAGS) -o object/Rook.o -c class/Rook.cpp

object/Knight.o: class/Knight.cpp header/Knight.h
	$(CC) $(CFLAGS) -o object/Knight.o -c class/Knight.cpp

object/Bishop.o: class/Bishop.cpp header/Bishop.h
	$(CC) $(CFLAGS) -o object/Bishop.o -c class/Bishop.cpp

object/Queen.o: class/Queen.cpp header/Queen.h
	$(CC) $(CFLAGS) -o object/Queen.o -c class/Queen.cpp

object/King.o: class/King.cpp header/King.h
	$(CC) $(CFLAGS) -o object/King.o -c class/King.cpp

#Mystery.o: Mystery.cpp Mystery.h
#	$(CC) $(CFLAGS) -c Mystery.h

clean:
	rm -f object/*.o chess.exe
