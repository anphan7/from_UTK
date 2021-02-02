#Makefile for searches
#Compiler:
CC = g++

#complier options
CFLAGS = -Wall -g

BIN = ./bin/ 

OBJ = $(BIN:%=%.o)

all: Fruit1 Fruit2

Fruit1: Fruit1.o
	$(CC) Fruit1.cpp -o Fruit1

Fruit2: Fruit2.o
	$(CC) Fruit2.cpp -o Fruit2
clean:
	@rm *.o  -f $(BIN) $(OBJ)
