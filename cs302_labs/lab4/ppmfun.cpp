#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
using namespace std;

void ppmfun(istream &fin){
    string magicid;
    int ncols, nrows;
    int maxvalue;

    fin >> magicid >> ncols >> nrows >> maxvalue;

    while (fin.get() != '\n'){}
    int npixels = nrows * ncols;

    unsigned char buf[3*npixels];
    int count=0;
    while(fin.read((char*) buf, 3*npixels)){
        count++;
    }
    cout << count << endl;
}
int main(int argc, char *argv[]){
    string fin_name(argv[1]);
    ifstream fin;
    fin.open(fin_name.c_str());
    ppmfun (fin);
}