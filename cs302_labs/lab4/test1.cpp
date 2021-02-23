#include "PPM.h"
#include <fstream>

using namespace std;


void PPM::read(const string& nameFile) { 
  ifstream inFile;
  inFile.open (nameFile.c_str(), ios::in | ios::binary);
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
    while (inFile.get() != '\n'); // skip the trailing white space
    

    int size = row * col ;    // number of bytes
    unsigned char buf[size];         
    while(1)
    {
      inFile.read((char*) buf, size);
      //cout << "Start here-------" << endl;
      cout << buf << endl;
      //cout << "End here---------" << endl;
    
    
      /*
      img = new RGB*[row];
      for (int i = 0; i < row; i++)
      {
        img[i] = new RGB [col];

        for (int j = 0; j < col; j++)
        {
          img[j][i].R = buf[i];
          img[j][i].G = buf[i];
          img[j][i].B = buf[i];
          
        }
      }
      */
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