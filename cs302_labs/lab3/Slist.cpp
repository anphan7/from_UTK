// include header file(s) needed
/*
    Name: AN PHAN
    Class: CS 302
    Description: In this lab you will continue sorting the multi-column data from Lab 2 which consisted of a firstname, a lastname, and a phone number. The main difference is that the data will now be stored in single linked list. In order to allow sorting by means of STL sorting algorithms (or any of the ones covered in class), you will embed a smart pointer subclass within the single linked list class and write the associated code for setting things up and applying the result.

*/
#include "Slist.h"
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
    int ID = 0;
};
istream &operator>>(istream &in, data &r)
{
    // write this to read data object data
    in >> r.firstname >> r.lastname >> r.phonenum ;
    r.ID++ ;
    return in;
}

ostream &operator<<(ostream &out, const data &r)
{
    // write this to write data object data
    // formated the output
    string fullName = r.lastname + " " + r.firstname; // concatenated the first, name
    out << left << setw(25) << fullName << r.phonenum; // 
    out << right << setw (10) << r.ID;
    return out;
}
bool operator<(const data &f1, const data &f2)
{ //overload operator < 
  // to compare the variable 
    if (f1.lastname != f2.lastname)
    {
        return (f1.lastname < f2.lastname);
    }
    else if (f1.lastname == f2.lastname && f1.firstname != f2.firstname)
    {
        return (f1.firstname < f2.firstname);
    }
    else if (f1.lastname == f2.lastname && f1.firstname == f2.firstname)
    {
        return (f1.phonenum < f2.phonenum);
    }
    return true;
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
  if (argc != 3 )
  {
      cout << "usage: ./Slist -quicksort|-mergsort repeat1.txt" << endl;
  }
  ifstream inFile;
  inFile.open(argv[2]); // open input file

  slist<data> A;
  data din;
  while (inFile >> din)
  {
    A.push_back(din);
    
  }
  inFile.close(); //  close input file

  A.sort(argv[1]);

  printlist(A.begin(), A.end());
  return 0;
}