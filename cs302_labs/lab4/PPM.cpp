#include "PPM.h"
#include <fstream>

using namespace std;


void PPM::read(const string& nameFile) { 
  ifstream inFile;
  inFile.open (nameFile.c_str());
  PPM p;
  string magic_ID;
  int row, col;
  int max_value;  // read in the header of the ppm file which is P6
  
  if (!inFile.is_open())
  {
    cout << nameFile << " can't open " << endl;
  }
  if (inFile.is_open())
  {
    inFile >> magic_ID >> row >> col >> max_value;
    cout << magic_ID << "\n"
         << row << " " <<  col << "\n"
         << max_value << endl;  
    while (inFile.get() != '\n');
    

    unsigned int size = (row * col *3 );    // number of bytes
    unsigned char buf[size];       
    int nrgb_read;
    while(1)
    {
      inFile.read((char*) buf, 15);
      //cout << buf << endl;
      nrgb_read = inFile.gcount() / 3;
      if (nrgb_read == 0 && inFile.eof()) 
        break; // stopping condition

      img = new RGB*[row];
      for (int i = 0; i < row; i++)
      {
        img[i] = new RGB [col];

        for (int j = 0; j < col; j++)
        {
          img[i][j].R = buf[i];
          img[i][j].G = buf[i];
          img[i][j].B = buf[i];
          
        }
      }
    }  

    
  }

  inFile.close();

}
/*
void PPM::write(const string &path ) 
{ 
  ostream outFile(path.c_str());
  if (outFile.fail()) return;
  
}
*/