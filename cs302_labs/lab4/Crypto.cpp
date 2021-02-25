#include <iostream>
#include <fstream>
using namespace std;

#include "PPM.h"
#include "Rnumgen.h"

const char ETX = 0x3;

/*
struct pixel {
  write this
}

void set_pixel_list(...) {
  write this
}

void encode(...) {
  write this
}

void decode(...) {
  write this
}
*/
int main(int argc, char *argv[]) {
  PPM image;

  //image.read(argv[1]);
  image.write(argv[1]);

/* 
  parse command line arguments
  if something not right,
    print error message and exit

  PPM img;
  img.read(fname);

  declare pixel_list

  set_pixel_list(pixel_list);

  if (mode = ENCODE) {
    encode(fname, img);
	img.write(fname)
  }
  else
  if (mode = DECODE) 
    decode(fname, img);
*/
}
