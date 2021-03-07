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
      if (i %2 == 0)
      {
        if (j %2 == 0)
        {
          pixel p;
          p.r= i;
          p.c = j;
          v.push_back(p);
        }
      }
    }
  }
}


void encode(PPM &img, vector <pixel> &v) {
  int index = 0;
  int color_change = 3;
  char c;
  while(cin.get(c))
  {
    for (int k = 0; k < 7; k++)
    {
      if ((color_change % 3) == 0)
      {
        img[v[index].r][v[index].c].R &= 0xFE;
        img[v[index].r][v[index].c].R |= ((c >> k) & 0x1);
      }
      if ((color_change % 3) == 1)
      {
        img[v[index].r][v[index].c].G &= 0xFE;
        img[v[index].r][v[index].c].G |= ((c >> k) & 0x1);
      }
      if ((color_change % 3) == 2)
      {
        img[v[index].r][v[index].c].B &= 0xFE;
        img[v[index].r][v[index].c].B |= ((c >> k) & 0x1);
      }
      color_change+=1;
      index+=1;
    }
  }
  
  for (int k = 0; k < 7; k++)
  {
    if ((color_change % 3) == 0)
      {
        img[v[index].r][v[index].c].R &= 0xFE;
        img[v[index].r][v[index].c].R |= ((ETX >> k) & 0x1);
      }
      if ((color_change % 3) == 1)
      {
        img[v[index].r][v[index].c].G &= 0xFE;
        img[v[index].r][v[index].c].G |= ((ETX >> k) & 0x1);
      }
      if ((color_change % 3) == 2)
      {
        img[v[index].r][v[index].c].B &= 0xFE;
        img[v[index].r][v[index].c].B |= ((ETX >> k) & 0x1);
      }
      color_change+=1;
      index+=1;
  }
}

void decode(PPM &img, vector <pixel> &v) {  
  int counter = 3;
  int index = 0;
  char out = 0;
  char out2 = 0 ;
  while(1)
  {
    for (int k = 0; k < 7; k++)
    {
      if ((counter % 3) == 0)
      {
        out |= img[v[index].r][v[index].c].R & 0x1;
        out = out << 1;
      }
      if ((counter % 3) == 1)
      {
        out |= img[v[index].r][v[index].c].G & 0x1;
        out = out << 1;
      }
      if ((counter % 3) == 2)
      {
        out |= img[v[index].r][v[index].c].B & 0x1;
        out = out << 1;
      }
      counter += 1;
      index += 1;
    }
    for (int i = 0; i < 8; i++)
    {
      if ((out & (1<< i)))
      {
        out2 |= 1 << ((8-1)-i);
      }
    }
    if (out2 == ETX) { break;}
    cout.put (out2);
    out = 0x0;
    out2 = 0x0;
  }
    
}

int main(int argc, char *argv[]) {
  PPM image;
  string mode;
  mode = argv[1];
  vector <pixel> pi; //declare pixel_list

/* 
  parse command line arguments
  if something not right,
    print error message and exit
*/
  image.read(argv[2]);

  set_pixel_list(image, pi);
  
  if (argc != 3 || (mode != "-encode" && mode != "-decode"))
  {
    cout << "Usage: ./Crypto1 -encode|-decode image_name.ppm" << endl;
    return 0;
  }

  if (mode == "-encode") {
    encode(image, pi); 
    image.write(argv[2]);
  }
  if (mode == "-decode") 
    decode(image, pi);

}
