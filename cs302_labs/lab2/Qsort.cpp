
// include header files needed
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

class data {
  public:
    // add operator< using lastname, firstname, phone number

    friend istream & operator>>(istream &, data &);
    friend ostream & operator<<(ostream &, const data &);

  private:
    string firstname;
    string lastname;
    string phonenum;
};

istream & operator>>(istream &in, data &r) { 
  // write this to read data object data
}

ostream & operator<<(ostream &out, const data &r) {
  // write this to write data object data
}

template <typename Tdata>
void quicksort(...) { 
  // write this 
}

template <typename Tdata>
void quickselect(...) { 
  // write this 
}

void printlist(...) { 
  // see Lab 1
}

int main(int argc, char *argv[]) {
  // perform command-line error checking
  // usage: Qsort -stl | -rpivot [k0 k1] file.txt

  open file.txt 

  vector<data> A;

  data din;
  while (fin >> din)
    A.push_back(din);

  close file.txt
  
  if (sorting option -stl) {
    std::sort(A.begin(), A.end();

  } else 
  if (sorting option -rpivot) {
    int N = (int)A.size();

    int k0 = 0;
    int k1 = N-1;

    // if specified, update k0, k1 and apply quickselect 
    // to ensure that A[0:k0-1] <= A[k0:k1] <= A[k1+1:N-1]

    quicksort(A, k0, k1);
  } 

  printlist(A.begin(), A.end());
}
