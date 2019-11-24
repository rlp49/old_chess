CC=g++
CFLAGS=-std=c++11 -pedantic -Wall -Wextra

# target executable
main: main.o Chess.o Board.o
	$(CC) -o main main.o Chess.o Board.o

# target object files
main.o: main.cpp Chess.h Board.h
	$(CC) $(CFLAGS) -c main.cpp -g

Chess.o: Chess.cpp Chess.h
	$(CC) $(CFLAGS) -c Chess.cpp -g

Board.o: Board.cpp Board.h CreatePiece.h
	$(CC) $(CFLAGS) -c Board.cpp -g

