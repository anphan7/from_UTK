/*
	Name: AN PHAN
	Class: CS 302
	Description:This header file defines an RGB struct and a PPM class for P6-type 		images
*/

#ifndef __PPM_H__
#define __PPM_H__

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cmath>
using namespace std;

struct RGB
{
	RGB() : R(0), G(0), B(0) {}; //constructor
	unsigned char R, G, B;
};

class PPM
{
public:
	PPM()  // constructor
	{ 
		cols = 0;
		row = 0;
	}
	~PPM() 
	{
		if (img){
			for (int i = 0; i < row ; i++){
				delete[] img[i];
			}
			delete[] img;
		}
	}
	void read(const string&);
	void write(const string&);

	RGB *operator[](int i) { return img[i]; } // take exactly 1 argument
	
	int get_Nrows() {return row; }
	int get_Ncols() { return cols; }

private:
	//data members
	RGB **img = NULL; // pointer to pointer
	int row, cols;
};

#endif
