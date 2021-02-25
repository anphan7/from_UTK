#include "PPM.h"
#include <fstream>
#include <stdio.h>

using namespace std;

void PPM::read(const string& nameFile) { 
  ifstream inFile;
  inFile.open (nameFile.c_str(), ios::binary);
  PPM p;
  string magic_ID;
  int nrow, ncol;
  int max_value;  // read in the header of the ppm file which is P6

  if (!inFile.is_open())
  {
    cout << nameFile << " can't open " << endl;
  }
  if (inFile.is_open())
  { 
    inFile >> magic_ID >> ncol >> nrow >> max_value;
    while (inFile.get() != '\n'){};
    int npixels = nrow * ncol;
    unsigned char buf[3*npixels];   
    int count = 0 ;
    while(inFile.read((char*) buf, 3*npixels)){
      count++;
    }
    //cout << count << " " << 3*npixels << endl;
    //cout << buf << endl;
    img = new RGB*[nrow];

    for (int i = 0; i < nrow; i++)
    {
      img[i] = new RGB[ncol];
    
      for (int j = 0; j < ncol; j++)
      {
        img[i][j].R = buf[i]; 
        img[i][j].G = buf[i]; 
        img[i][j].B = buf[i];
      }
    }
  }
  inFile.close();
}

void PPM::write(const string &nameFile ) 
{ 
  ofstream outFile;
  ifstream inFile;
  inFile.open (nameFile.c_str(), ios::binary);
  string magic_ID;
  int nrow, ncol;
  int max_value;  // read in the header of the ppm file which is P6  inFile >> magic_ID >> ncol >> nrow >> max_value;

  string new_Name = nameFile.substr(0, nameFile.find(".", 0));
  outFile.open ((new_Name + "_wmsg.ppm").c_str());
  PPM p;
  if (!outFile.is_open())
  {
    cout << new_Name << " can't open " << endl;
  }
  if (outFile.is_open())
  {  
    inFile >> magic_ID >> ncol >> nrow >> max_value;
    while (inFile.get() != '\n'){};

    cout << nrow << endl;
    int npixels = ncol * nrow;
    unsigned char buf[3*npixels]; 

    inFile.read((char*) buf, 3*npixels);
    outFile << "P6" << endl;
    outFile << ncol << " " << nrow << endl;
    outFile << max_value << endl;
    outFile.write((char*) buf, 3*npixels);
  }
  outFile.close();
}
