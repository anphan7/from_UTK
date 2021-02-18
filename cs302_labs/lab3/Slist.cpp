// include header file(s) needed

#include "Slist.h"
#include <iostream>
#include <cstring>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
using namespace std;

// modify the data class and the associated input 
// and output operators to store, set and print a 
// line number identifier called ID

class data
{
public:
    // add operator< using lastname, firstname, phone number

    friend bool operator<(const data &f1, const data &f2);
    friend istream &operator>>(istream &, data &);
    friend ostream &operator<<(ostream &, const data &);

private:
    string firstname; 
    string lastname;
    string phonenum;
};
istream &operator>>(istream &in, data &r)
{
    // write this to read data object data
    in >> r.firstname >> r.lastname >> r.phonenum;
    return in;
}

ostream &operator<<(ostream &out, const data &r)
{
    // write this to write data object data
    // formated the output
    string fullName = r.lastname + ", " + r.firstname; // concatenated the first, name
    out << left << setw(25) << fullName << r.phonenum; // 
    return out;
}

template <typename Tdata>
void printlist(Tdata begin, Tdata end) // function for printing the iretator 
{
    for (; begin != end; ++begin)       // print until reach end
    {
        cout << *begin << endl;
    }
}

int main(int argc, char *argv[]) {
  // copy command-line check from Qsort.cpp,
  // then modify to apply to this assignment
  string mode;
  mode = argv[1];
  ifstream inFile;
  inFile.open(argv[argc -1 ]); // open input file

  slist<data> A;

  data din;
  while (inFile >> din)
    A.push_back(din);

  inFile.close(); //  close input file

  A.sort(mode);

  printlist(A.begin(), A.end());
}