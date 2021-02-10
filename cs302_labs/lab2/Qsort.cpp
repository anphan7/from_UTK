/*
    Name: An Phan
    Class: CS 302
    Program's Description: Similar to Lab 1, you will define a class for storing multi-column data consisting of a firstname, a lastname,
                            and a phone number (all made up, but you knew that), read unspecified amounts of such data 
                            from a given file and apply the std::sort algorithm 
                            before you print the result to stdout. Then the real work begins by you implementing a variant of the quicksort algorithm described 
                            in class that in its basic form replaces std::sort and in a more advanced version based on the quickselect algorithm that 
                            allows partitioning of the data followed by sorting within a given range.


*/
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
#define TRUE 1;
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
    // formated the output
    string fullName = r.lastname + ", " + r.firstname; // concatenated the first, name
    out << left << setw(25) << fullName << r.phonenum; // 
    return out;
}

template <typename Tdata>
void quicksort(vector<Tdata> &A, int left, int right)
{
    if ((right - left) == 1)    // if right and left are next to each other
    {
        if (A[right] < A[left]) // compare if left element still larger than right element
        {
            swap(A[right], A[left]);  // if yes then swap the place
        }
                                     // if no then do nothing
    }
    if (left < right)           // if the left element is smaller than the right element 
    {
        srand(time(NULL));      // generate the random number 
        int random = rand() % (right - left + 1);   // random number from the range left and right 
        int pindex = left + random;             // find the place of pindex to make pivot
        Tdata pivot = A[pindex];                // make pivot

        swap(A[pindex], A[right]);              // swap the pivot and the right element 
        int i = left - 1;
        int j = right;

        while (1)
        {
            while (A[++i] < pivot && i != right) {}         // from left side and moving to the pivot, still smaller than pivot, and not cross the right side
            while (pivot < A[--j] && (j > left)){}          // from right side and moving back to the pivot, still larger than pivot, and not cross the left side
            if (i >= j || (i > right) || (j < left)) break; // if they cross each other, break the while loop
                                                            // the loop will stop if the conditions reached (the place of element will be mark)            
            swap(A[i], A[j]);                               // if those conditions stop, then swap the marked element 
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
    srand(time(NULL));  // generate the random number
    while (1)
    {
        int random = rand() % (right - left + 1); // random number from the range left and right 
        if (right - left == 0){                     // my program sometime make left and right equal each other
                                                    // this if statment will catch it and set the left = 0 and right = the side of the vector 
            left = 0;
            right = A.size() - 1;
        }
  

        if ((right - left) == 1)        // if right and left are next to each other
        {
            if (A[right] < A[left]) // compare if left element still larger than right element
            {
                swap(A[right], A[left]);// if yes then swap the place
                return;
            }
                                         // if no then do nothing
        }

        if (left < right)       // if the left element is smaller than the right element
        {
            int pindex = left + random;             // find the place of pindex to make pivot
            Tdata pivot = A[pindex];                // make pivot
            swap(A[pindex], A[right]);              // swap the pivot and the right element 

            int i = left - 1;
            int j = right;

            while (1)
            {
                while (A[++i] < pivot && i != right) {}         // from left side and moving to the pivot, still smaller than pivot, and not cross the right side
                while (pivot < A[--j] && (j > left)){}          // from right side and moving back to the pivot, still larger than pivot, and not cross the left side
                if (i >= j || (i > right) || (j < left)) break; // if they cross each other, break the while loop
                                                            // the loop will stop if the conditions reached (the place of element will be mark)            
                swap(A[i], A[j]);                               // if those conditions stop, then swap the marked element 
            }

            // from the handout   
            pindex = i;
            swap(A[pindex], A[right]);

            if (pindex == k)
                return;
            if (k < pindex)
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
void printlist(Tdata begin, Tdata end) // function for printing the iretator 
{
    for (; begin != end; ++begin)       // print until reach end
    {
        cout << *begin << endl;
    }
}

int main(int argc, char *argv[])
{

    ifstream inFile;
    ofstream outFile;
    inFile.open(argv[argc - 1]); // open file.txt. If I set the open file from argv[2], argv[2] will make my vector empty.
                                //  Because the argv at this option (./Qsort -rpviot 3 5 list1.txt ) = 3 and it make the vector empty
                                // Since the program asking for the last argv = the name of the file. SO I set the argc - 1 so it can get 
                                // the file everytime. 
    vector<data> A;       // created vector A    
    data din;             // name of class
    string mode;           // mode for ease use
    mode = argv[1];         // set for the argv[1] for easier coding 
    // perform command-line error checking
    
    if (argc < 3 || argc > 5 || argc == 4) // if the argument count must = 3 or 5. 
    {
        cout << "usage: Qsort -stl | -rpivot [k0 k1] file.txt" << endl;     // error 
    }
    
    while (inFile >> din)       // read the file until end of file
    {
        A.push_back(din); // vector size here is 11 (11 line of file)
    }
    inFile.close(); //close file.txt

    if (mode == "-stl")         // the option one ./Qsort "-stl" list1.txt
    {
        std::sort(A.begin(), A.end());  // sort function from STL - it sorted the data with the operator< wrote above
        printlist(A.begin(), A.end());  // print the sorted list
    }

    else if (mode == "-rpivot") // the option 2 and 3 ./Qsort "-rpivot" ...
    {
        int N = (int)A.size();      // make the N = vector's size ==> easier to code
        int k0 = 0;                 //  k0-th element
        int k1 = N - 1;             //  k1-th element

        if (argc == 3)              // the option 2 ./Qsort "-rpivot" list1.txt (the argument count = 3)
        {
            quicksort(A, k0, k1);   // using the quicksort function to sort the vector 
        }
        else if (argc == 5)     // the option 2 ./Qsort "-rpivot" k0 k1 list1.txt (the argument count = 5)
        {
            k0 = atoi(argv[2]);     // convert the argv[2 and 3] to int
            k1 = atoi(argv[3]);

            if (k0 < 0)             // if the left < 0 set it = 0
            {
                k0 = 0;
            }
            if (k1 >= N)            // if the right > 0 set it = vector's size
            {
                k1 = N - 1;
            }

            quickselect(A, 0, k0, N - 1); // to put the k0-th element in its proper location and partition the data in A accordingly
            quickselect(A, k0, k1, N - 1);  //to put the k1-th element in its proper location and partition the data in A accordingly
            quicksort(A, k0, k1);  //quicksort() function to sort the data in the k0 thru k1 index range

            

            // if specified, update k0, k1 and apply quickselect
            // to ensure that A[0:k0-1] <= A[k0:k1] <= A[k1+1:N-1]
        }
        printlist(A.begin(), A.end()); //print here for both option 2 and 3

    }


    return 0;
}
