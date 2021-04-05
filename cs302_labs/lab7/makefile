#Makefile for searches
#Compiler:
CC = g++
CFLAGS = -Wall 
BIN = mazemake mazesolve

all: $(BIN)

mazemake: Mazemake.cpp dset.h dset.cpp
	$(CC) $(CFLAGS) -o mazemake Mazemake.cpp dset.h dset.cpp 

mazesolve: Mazesolve.cpp
	$(CC) $(CFLAGS) -o mazesolve Mazesolve.cpp

clean:
	@rm *.o  -f $(BIN) $(OBJ)
	@rm -f maze.txt Mazemake Mazesolve
	@rm -f path.txt maze.ppm path.ppm




