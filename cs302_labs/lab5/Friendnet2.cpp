#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <set>
#include <stdlib.h>     /* srand, rand */
#include <iterator> // for iterators 
#include <iomanip>      // std::setw
#include <algorithm>    // std::sort

using namespace std;

void set_oldfriends(vector <string> &name, vector< vector <int> > &friends, int M0, int M1) {
  int N = (int)name.size(); // N = 1321 
  //initialize 2D-vector-array friends (hint: use vector::assign())
  friends.resize(N); 

  for (int i=0; i<N; i++) {
	  set <int> doknow; //declare std::set called doknow

	  int M = M0 + rand() % M1; //initialize M (random number of friends: function of M0, M1)
    
    while ((int)doknow.size() < M) {
       int j = rand() % N; //  compute j (random friend index: hint j != i)
       if (j != i)    
        doknow.insert(j);
	  }
    /*
	  use iterator to sweep thru doknow set
	  update the corresponding pairs of friends entries
    */
    for (std::set<int>::iterator it = doknow.begin(); it != doknow.end(); ++it)
    {
      friends[i].push_back(*it);
      friends[*it].push_back(i);
      sort(friends[*it].begin(), friends[*it].end());
      sort(friends[i].begin(), friends[i].end());
      unique(friends[*it].begin(), friends[*it].end() );
      unique(friends[i].begin(), friends[i].end() );
    }
  }
}

void set_newfriends(vector< vector <int> > &friends, vector< vector <int> > &new_friends) {
  int N = (int)friends.size();
  new_friends.resize(N);   
  std::vector<int>::iterator it;
  std::vector<int>::iterator temp;
  for (int i=0; i<N; i++) 
  {
    for (int j = 0; j < N; j++) 
    {
      it = find(friends[i].begin(), friends[i].end(), j); // j friend at location i
      if (it != friends[i].end())
      {
        for (int k = 0; k < N; k++)
        {
          temp = find(friends[j].begin(), friends[j].end(), k);  // k friend at location j
          if (k != i  && temp != friends[j].end())
          {
              new_friends[k].push_back(i);
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
  int count = 0;  // keep 
  //determine max name length
  std::vector<int>::iterator it;
 

  if (outFile.is_open())
  {
    for (int i=0; i<N ; i++) {
      outFile << name[i] << right << setw(15 - name[i].size()) << " : ";  // print names
      for ( it = friends[i].begin(); it != friends[i].end(); ++it) //each adjacent friend: friends[i][j] == 1) 
      { 
            if (count % 8 == 0 && count > 0)
            {
              outFile << endl;
              outFile << name[i] << right << setw(15 - name[i].size()) << " : ";  // print names

            }
            outFile << left << name.at(*it);    // print friends
            outFile << setw(12 - name.at(*it).size()) << left  << " "; 
            count++;
          
      }  //pretty-print name[i] and name[j] (see assignment) 
        outFile << endl;
        count = 0;
    }
  }
  outFile.close(); //close file
}

int main(int argc, char *argv[]) {
  //parse argc, argv arguments
  //print usage message and exit if invalid
  string mode_seed = argv[1];
  if (argc != 3 || (argc != 1 && mode_seed != "-seed"))
  {
    cout << "Usage: cat datafile.txt | ./Friendnet1 [-seed N]" << endl;
    return 0;
  }

  ifstream inFile;
  string name;
  vector<string> v_name;
  while (cin >> name)
  {
    v_name.push_back(name);
    name.clear();
  }

  if (argc == 1 || argc == 2)
    srand(time(NULL));
  else{
    int seed = atoi(argv[2]) ; //seed random number generator
    srand(seed);
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

}
