#include <iostream>
#include <fstream>
#include <bitset>

using namespace std;

#include "PPM.h"
#include "Rnumgen.h"

const char ETX = 0x3; // end of text like ctrl+C

struct pixel {
  pixel()
  {
    r = 0;
    c = 0;
  }
  int r;
  int c;
};

void set_pixel_list(PPM &img, vector <pixel> &v  ) {
  for ( int i = 0; i < img.get_Nrows(); i++)
  {
    for (int j = 0; j < img.get_Ncols(); j++)
    {
      //set all even pixels
      if (i %2 == 0) 
      {
        if (j %2 == 0)
        {
          pixel p;
          p.r= i;
          p.c = j;
          v.push_back(p);  }}}}}

void encode(PPM &img, vector <pixel> &v) {
  int i = 0;
  int color_change = 3;
  char c;
  char bit;
  char bit_ETX;

  while(cin.get(c))
  {
    for (int k_th = 0; k_th < 7; k_th++)
    {
      bit = c >> k_th;
      //set the color = 1111 1110
      // move char to k_th location (0,1,...6)
      // encryted to 0000 000c
      if ((color_change % 3) == 0)
      {
        img[v[i].r][v[i].c].R &= 0xFE;
        img[v[i].r][v[i].c].R |= bit & 0x1;
      }
      if ((color_change % 3) == 1)
      {
        img[v[i].r][v[i].c].G &= 0xFE;
        img[v[i].r][v[i].c].G |= bit & 0x1;
      }
      if ((color_change % 3) == 2)
      {
        img[v[i].r][v[i].c].B &= 0xFE;
        img[v[i].r][v[i].c].B |= bit & 0x1;
      }
      color_change++; // swith color here
      i++;  // move to different index
    }
  }
  for (int k_th = 0; k_th < 7; k_th++)
  {
    bit_ETX = ETX >> k_th;
    //set the color = 1111 1110
    // move ETX to k_th location (0,1,...6)
    // encryted to 0000 000c + ETX
    if ((color_change % 3) == 0)
      {
        img[v[i].r][v[i].c].R &= 0xFE;
        img[v[i].r][v[i].c].R |= bit_ETX & 0x1;
      }
      if ((color_change % 3) == 1)
      {
        img[v[i].r][v[i].c].G &= 0xFE;
        img[v[i].r][v[i].c].G |= bit_ETX & 0x1;
      }
      if ((color_change % 3) == 2)
      {
        img[v[i].r][v[i].c].B &= 0xFE;
        img[v[i].r][v[i].c].B |= bit_ETX & 0x1;
      }
      color_change++; // swith color here
      i++;  // move to different index
  }
}

void decode(PPM &img, vector <pixel> &v) {  
  int color_change = 3;
  int i = 0;
  char c;
  char text;
  while(1)
  {
    for (int k_th = 0; k_th < 7; k_th++)
    {
      if ((color_change % 3) == 0)
      {
        // get the encrypted bit from image
        // move the first bit to the char
        c |= img[v[i].r][v[i].c].R & 0x1;
        c = c << 1;
      }
      if ((color_change % 3) == 1)
      {
        c |= img[v[i].r][v[i].c].G & 0x1;
        c = c << 1;
      }
      if ((color_change % 3) == 2)
      {
        c |= img[v[i].r][v[i].c].B & 0x1;
        c = c << 1;
      }
      color_change++;
      i++;
    }
    for (int j = 0; j < 8; j++)
    {
      if ((c & (1 << j)))
       text |= 1 << (7 - j);
      
    }
    if (text == ETX) { break;} // stop when hit ETX
    cout.put (text); // print the decrypted char
    text = 0; // start over
  }
    
}

int main(int argc, char *argv[]) {
  PPM image;
  string mode;
  mode = argv[1];
  vector <pixel> pi; //declare pixel_list

  image.read(argv[2]);

  set_pixel_list(image, pi);  // set all even pixels
  
  if (argc != 3 || (mode != "-encode" && mode != "-decode"))
  {
    cout << "Usage: ./Crypto1 -encode|-decode image_name.ppm" << endl;
    return 0;
  }

  if (mode == "-encode") {
    encode(image, pi); 
    image.write(argv[2]); // write new file
  }
  if (mode == "-decode") 
    decode(image, pi);

}
