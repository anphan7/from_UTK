/*
  Name: An Phan
  CS-302
  Description: Dense matrix 
*/

#include <iostream>
#include <vector>
#include <fstream>
#include <set>
#include <stdlib.h>     /* srand, rand */
#include <iterator> // for iterators 
#include <iomanip>      // std::setw
#include <string.h>


using namespace std;

void set_oldfriends(vector <string> &name, vector< vector <int> > &friends, int M0, int M1) {
  int N = (int)name.size(); // N = 1321 
  //initialize 2D-vector-array friends (hint: use vector::assign())
  friends.resize(N);  // extent the size to = name.vector

  for ( int i = 0; i < N; i++)
    friends[i].assign(N, 0);   // assign all value of Column to 0

  for (int i=0; i<N; i++) {
	  set <int> doknow; //declare std::set called doknow

	  int M = M0 + rand() % M1; //initialize M (random number of friends: function of M0, M1)
    
    while ((int)doknow.size() < M) {
       int j= rand() % N; //  compute j (random friend index: hint j != i)
       if (j != i)    // make sure they are not friends with themselves :(
        doknow.insert(j); // insert into the doknow queue
	  }
    /*
	  use iterator to sweep thru doknow set
	  update the corresponding pairs of friends entries
    */
    for (std::set<int>::iterator it = doknow.begin(); it != doknow.end(); ++it) // extract from the doknow set
    {
      friends[i][*it] = 1;    // if found at the specific location, set is to 1 for later use
      friends[*it][i] = 1;    // 2-way relationship
    }
  }
}

void set_newfriends(vector< vector <int> > &friends, vector< vector <int> > &new_friends) {
  int N = (int)friends.size();
  new_friends.resize(N);    // extent the size to = name.vector

  for (int i = 0; i < N; i++)
    new_friends[i].assign(N, 0);             //initialize 2D-vector-array new_friends (hint: use vector::assign())

  for (int i=0; i<N; i++)   // loop to find A
  {
    for (int j = 0; j < N; j++) // loop to find B
    {
      if (friends[i][j] == 1)   // if A and B are friend 
      {
        for (int k = 0; k < N; k++)   // loop to find B's friends
        {
          if (friends[j][k] == 1)     // if B know C -> A know C
          {
            if( k!= i && friends[i][k] == 0)// if (k-is-not-i && k-is-not-friend-of-i)
              new_friends[i][k] = 1;            //update the corresponding pairs of new_friends entries
                                                // 1 way relationship (mightknow)
          }
        }
      }
    }
  }
}

void writetofile(const char *fname, vector<string> &name, vector< vector <int> > &friends) {
  ofstream outFile; //open file
  outFile.open(fname);
  int N = (int)name.size();
  int count = 0;  // keep track of name per line
  
  if (outFile.is_open())
  {
    for (int i=0; i<N ; i++) {
      outFile << name[i] << right << setw(15 - name[i].size()) << " : ";  // print names and determine max name length
      for (int j = 0; j < N;  j++) //each adjacent friend: friends[i][j] == 1) 
      { 
          if (friends[i][j] == 1)   // found one
          {
            if (count % 8 == 0 && count > 0)  // print 8 name at a line
            {
              outFile << endl;
              outFile << name[i] << right << setw(15 - name[i].size()) << " : ";  // print names

            }
            outFile << left << name[j];    // print adjacent friends
            outFile << setw(12 - name[j].size()) << left  << " "; 
            count++;  // keep track to print 8 name only
          }
        }  //pretty-print name[i] and name[j] (see assignment) 
        outFile << endl;
        count = 0;    // reset to 0
    }
  }
  outFile.close(); //close file
}

int main(int argc, char *argv[]) {
  //parse argc, argv arguments
  //print usage message and exit if invalid
  if (argc != 3 && argc != 1)   
  {
    cout << "Usage: cat datafile.txt | ./Friendnet1 [-seed N]" << endl;
  }
  if (argc == 2 || argc > 3){return 0;}
  string name;
  vector<string> v_name;
  
  int seed;
  if (argc == 3){ seed = atoi(argv[2]); } //seed random number generator
  if (argc == 1) {seed = time(NULL);}     // seed = NULL if no given
  srand(seed);  
  
  while (cin >> name)  // cin whatever file name
  {
    v_name.push_back(name); // push to vector of name.vector
    name.clear();
  }
 

  //read strings from stdin into name vector

  int M0 = 1; // min number of friends
  int M1 = 3; // max number of friends
 
  vector< vector<int> > friends;//declare 2D-vector-array called friends
  vector< vector<int> > new_friends;//declare 2D-vector-array called new_friends

  set_oldfriends(v_name, friends, M0, M1);
  writetofile("doknow1.txt", v_name, friends);

  set_newfriends(friends, new_friends);
  writetofile("mightknow1.txt", v_name, new_friends);
  return 0;
}
