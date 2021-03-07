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

    while (inFile.get() != '\n'){};
    int npixels = row * cols; 
    unsigned char buf[3*npixels];   
    inFile.read((char*) buf, npixels * 3);
    img = new RGB*[row];
    int k = 0;
    for (int i = 0; i < row; i++)
    {
      img[i] = new RGB[cols];

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

void PPM::write(const string &nameFile ) 
{ 
  ofstream outFile;
  PPM p;
  string magic_ID = "P6";
  int max_value = 255;
  string new_Name = nameFile.substr(0, nameFile.find(".", 0));
  outFile.open ((new_Name + "_wmsg.ppm").c_str(), ios::binary| ios::out);
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
        outFile << img[i][j].R << img[i][j].G << img[i][j].B;
      }
    }
  }
  outFile.close();
}
