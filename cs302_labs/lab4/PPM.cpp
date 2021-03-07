#include "PPM.h"
#include <fstream>
#include <stdio.h>

using namespace std;

void PPM::read(const string& nameFile) { 
  ifstream inFile;
  inFile.open (nameFile.c_str(), ios::binary | ios::in);
  string magic_ID;
  int max_value;  // read in the header of the ppm file which is P6

  if (!inFile.is_open())
  {
    cout << nameFile << " can't open " << endl;
  }
  
  
  if (inFile.is_open())
  { 
    
    inFile >> magic_ID >> cols >> row >> max_value; 
    if (magic_ID != "P6")
    {
      inFile.close();
      cout << "This is not a P6 format PPM image." << endl;
      cout << " Please try a differnt file " << endl;
      exit(0);
    }
  
    if (max_value != 255)
    {
      cout << "The max value of color not equal 255" << endl;
      exit (0);
    }
    while (inFile.get() != '\n'){};
    int npixels = row * cols; // size of the image
    unsigned char buf[3*npixels];    // buffer with size of the image
    inFile.read((char*) buf, npixels * 3); // read every binary into the buffer
    img = new RGB*[row];    // allocate the row
    int k = 0;
    for (int i = 0; i < row; i++)
    {
      img[i] = new RGB[cols]; // allocate the col

      for (int j = 0; j < cols; j++)
      {
        img[i][j].R = buf[k]; 
        img[i][j].G = buf[k+1]; 
        img[i][j].B = buf[k+2];
        k+=3;
      }
    }
  }
  inFile.close();
}
/*
    int **                int *                int 
    +---+                 +---+                +---+
pt: |   | --------------->|   | pt[0] -------->|   | pt[0][0]
    +---+                 +---+                +---+
                          |   | pt[1]          |   | pt[0][1]
                          +---+                +---+
                          |   | pt[2]          |   | pt[0][2]
                          +---+                +---+
                           ...                  ...
                          +---+                +---+
                          |   | pt[9]          |   | pt[0][9]
                          +---+                +---+
*/

void PPM::write(const string &nameFile ) 
{ 
  ofstream outFile;
  PPM p;
  string magic_ID = "P6";
  int max_value = 255;
  string new_Name = nameFile.substr(0, nameFile.find(".", 0)); // parse the name of the file before the dot
  outFile.open ((new_Name + "_wmsg.ppm").c_str(), ios::binary| ios::out); // open the same name file + _wmsg.ppm
  if (!outFile.is_open())
  {
    cout << new_Name << " can't open " << endl;
  }
  if (outFile.is_open())
  {  
	  outFile << magic_ID << endl;  
    outFile << cols << " " << row << endl;  
    outFile << max_value << endl;
    for (int i = 0; i < row; i++)
    {
      for (int j = 0; j < cols; j++)
      { 
        outFile << img[i][j].R << img[i][j].G << img[i][j].B; // write image to new file
      }
    }
  }
  outFile.close();
}
