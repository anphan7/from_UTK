#Makefile for searches
#Compiler:
CC = g++
CFLAGS = -Wall 
BIN = mazemake mazesolve mazeimage

all: $(BIN)

mazemake: Mazemake.cpp dset.h dset.cpp
	$(CC) $(CFLAGS) -o mazemake Mazemake.cpp dset.h dset.cpp 

mazesolve: Mazesolve.cpp
	$(CC) $(CFLAGS) -o mazesolve Mazesolve.cpp

mazeimage: Mazeimage.cpp
	$(CC) $(CFLAGS) -o mazeimage Mazeimage.cpp

clean:
	@rm *.o  -f $(BIN) $(OBJ)
	@rm -f Mazeimage Mazemake Mazesolve
	@rm -f *.txt
	@rm -f *.ppm



