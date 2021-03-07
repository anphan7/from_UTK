CC = g++
CFLAGS = -Wall

all: Crypto1 Crypto2

Crypto1: Crypto1.cpp PPM.h PPM.o Rnumgen.h Rnumgen.o
	$(CC) $(CFLAGS) -o $@ Crypto1.cpp PPM.o Rnumgen.o

Crypto2: Crypto2.cpp PPM.h PPM.o Rnumgen.h Rnumgen.o
	$(CC) $(CFLAGS) -o $@ Crypto2.cpp PPM.o Rnumgen.o

.cpp.o:
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f Crypto1 Crypto2 PPM.o Rnumgen.o
	rm -f *_wmsg.ppm