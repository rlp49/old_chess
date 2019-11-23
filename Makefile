CC=g++
CFLAGS=-std=c++11 -pedantic -Wall -Wextra

# target executable
main: main.o Chess.o
	$(CC) -o main main.o Chess.o

# target object files
main.o: main.cpp Chess.h
	$(CC) $(CFLAGS) -c main.cpp -g

Chess.o: Chess.cpp Chess.h
	$(CC) $(CFLAGS) -c Chess.cpp -g

