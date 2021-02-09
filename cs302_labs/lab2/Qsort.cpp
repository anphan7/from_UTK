
// include header files needed
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string.h>
#include <algorithm>
#include <vector>
#include <sstream>
#include <iterator>
#include <stdlib.h>

using namespace std;

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
bool operator<(const data &f1, const data &f2)
{ //overload operator <
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
}

istream &operator>>(istream &in, data &r)
{
    // write this to read data object data
    in >> r.firstname >> r.lastname >> r.phonenum;
    return in;
}

ostream &operator<<(ostream &out, const data &r)
{
    // write this to write data object data
    out <<  r.lastname << ", " << left << setw(25) << r.firstname;
    out  << r.phonenum;
    return out;
}

template <typename Tdata>
void quicksort(vector<Tdata> &A, int left, int right)
{
    if ((right - left) == 1)
    {
        if (A[right] < A[left])
        {
            swap(A[right], A[left]);
        }
    }
    if (left  < right)
    {
        srand(time(NULL));
        int random = rand() % (right - left);
        int pindex = left + random;
        Tdata pivot = A[pindex];

        swap(A[pindex], A[right]);
        int i = left - 1;
        int j = right;

        while (1)
        {
            while (A[++i] < pivot && i != right)
            {
            }
            while (pivot < A[--j] && (j > left))
            {
            }
            if (i >= j || (i > right) || (j < left))
                break;
            swap(A[i], A[j]);
        }
        pindex = i;
        swap(A[pindex], A[right]);
        quicksort(A, left, pindex - 1);
        quicksort(A, pindex + 1, right);
    }
}

template <typename Tdata>
void quickselect(vector<Tdata> &A, int left, int k, int right)
{
    left = 0;
    right = (int)A.size() - 1;

    while (1)
    {
        srand(time(NULL));
        int random = rand() % (right - left);
        int pindex = left + random;
        Tdata pivot = A[pindex];
        if ((right - left) == 1)
        {
            if (A[right] < A[left])
            {
                swap(A[right], A[left]);
                return;
            }
        }
        if (left  < right)
        {

            swap(A[pindex], A[right]);
            int i = left - 1;
            int j = right;

            while (1)
            {
                while (A[++i] < pivot && i != right){}
                while (pivot < A[--j] && (j > left)){}
                if (i >= j || (i > right) || (j < left)) break;
                swap(A[i], A[j]);
            }
            /*
            if (right - left  == 2)
            {
                if (A[left] < A[right]) { swap(A[left], A[right]); }
            }
            */
            pindex = i;
            swap(A[pindex], A[right]);
            if (pindex  == k )
                return;
            if (k < pindex )
            {
                right = pindex - 1;
            }
            else
            {
                left = pindex + 1;
            }
        }
    }
}

template <typename Tdata>
void printlist(Tdata begin, Tdata end) // second parameter will be iterator or size ?
{
    int i = 0;
    for (; begin != end; ++begin)
    {
        cout << *begin  << endl;
        i++;
    }
}

int main(int argc, char *argv[])
{

    ifstream inFile;
    ofstream outFile;
    inFile.open(argv[2]); // open file.txt
    string line;
    vector<data> A;
    data din;
    // perform command-line error checking
    /*
    if (argc != 3)
    {
        cout << "usage: Qsort -stl | -rpivot [k0 k1] file.txt" << endl;
    }
    */
    while (inFile >> din)
    {
        A.push_back(din); // vector size here is 11 (11 line of file)
    }
    inFile.close(); //close file.txt

    if (strcmp(argv[1], "-stl") == 0)
    {
        std::sort(A.begin(), A.end());
    }

    else if (strcmp(argv[1], "-rpivot") == 0)
    {
        int N = (int)A.size();
        int k0 = 0;
        int k1 = N - 1;

        if (argc == 5)
        {
            k0 = atoi(argv[2]);
            k1 = atoi(argv[3]);
            if (k0 < 0)
            {
                k0 = 0;
            }
            if (k1 >= A.size())
            {
                k1 = A.size() - 1;
            }
            cout << " check this " << endl;
            quickselect(A, 0, k0, A.size() - 1);
            quickselect(A, k0, k1, A.size() - 1);
            quicksort(A, k0, k1);
            // if specified, update k0, k1 and apply quickselect
            // to ensure that A[0:k0-1] <= A[k0:k1] <= A[k1+1:N-1]
        }
        else
            quicksort(A, k0, k1);
    }

    printlist(A.begin(), A.end());
}
