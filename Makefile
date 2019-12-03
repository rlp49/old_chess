CC=g++
CFLAGS=-std=c++11 -pedantic -Wall -Wextra

# Someone double check the makefile!!!

# target executable
main: main.o Chess.o Board.o CreatePiece.o
	$(CC) -o main main.o Chess.o Board.o CreatePiece.o

# target object files
main.o: main.cpp Chess.h Board.h CreatePiece.h
	$(CC) $(CFLAGS) -c main.cpp -g

Chess.o: Chess.cpp Chess.h 
	$(CC) $(CFLAGS) -c Chess.cpp -g

Board.o: Board.cpp Board.h CreatePiece.h
	$(CC) $(CFLAGS) -c Board.cpp -g

CreatePiece.o: CreatePiece.cpp CreatePiece.h Pawn.h Rook.h Knight.h Bishop.h Queen.h King.h Mystery.h
	$(CC) $(CFLAGS) -c CreatePiece.cpp -g

Pawn.o: Pawn.cpp Pawn.h
	$(CC) $(CFLAGS) -c Pawn.cpp

Rook.o: Rook.cpp Rook.h
	$(CC) $(CFLAGS) -c Rook.cpp

Knight.o: Knight.cpp Knight.h
	$(CC) $(CFLAGS) -c Knight.cpp

Bishop.o: Bishop.cpp Bishop.h
	$(CC) $(CFLAGS) -c Bishop.cpp

Queen.o: Queen.cpp Queen.h
	$(CC) $(CFLAGS) -c Queen.cpp

King.o: King.cpp King.h
	$(CC) $(CFLAGS) -c King.cpp

clean:
	rm -f *.o main
