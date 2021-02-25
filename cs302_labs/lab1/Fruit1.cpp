/*
	Name: An Phan
	CS 302 - Lab1
	Description: read the file into array_list (vector)
				 set command line = -inorder|-sortall|-sortone
				 -inorder: print the list 
				 -sortall: print the list with same name of fruit
				 -sortone: like sortall but combine the name and the quantity
*/
// list all headers needed 
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string.h>
#include <algorithm>
#include <vector>
#include <iterator>
#include <set>
const int MAX_LENGTH = 256;
using namespace std;

struct fruit_t {

  //--------Data declarations--------------
  	char fruit_name[MAX_LENGTH];					// name of fruit
  	float quantity;							// in lbs
 	float price; 							// price tag of the fruit
	float new_quantity;
	friend	bool operator< (const fruit_t& f1, const fruit_t& f2){           //overload operator <
           return (strcmp (f1.fruit_name, f2.fruit_name) < 0);
        }


};
void print (vector<fruit_t>,int i, int count); 		// print function
int main(int argc, char *argv[]){

 //prog -inorder|sortall|sortone file.txt
  //set program mode from command line arg
        vector<fruit_t> fruit;  	// array_list vector fruit
        ifstream inFile;		// file name
		int count = 0;			
        float total_price = 0;
        inFile.open("list1.txt");                                       //open file
		int i = 0;
        while (true){                                     //read in the file is true
	        fruit.push_back(fruit_t());						// push the variables to the vector
            inFile >> fruit[i].fruit_name;
            inFile >> fruit[i].quantity;       
            inFile >> fruit[i].price;
            if (inFile.eof() ) break;				// break if is end of file	
	    i++;			  // place in the vector, +1 every time in loop
	    count++;          // count how many line read in
           
        
		}
		string mode = argv[1];
		if(argc != 3 || mode != "-inorder" && mode != "-sortall" && mode != "-sortone" ){
				cout << "ERROR " << endl;
				cout << "Command = 2" << endl; 
				cout << "Enter your command as: ./Fruit2 -inorder|-sortall|-sortone file.txt" << endl;
				return 0;
        }
		if (strcmp(argv[1], "-inorder") == 0){                  // store data INORDER
			int j = 0;
			print(fruit, j, count );        
        }
        else if ((strcmp (argv[1], "-sortall") == 0) || (strcmp (argv[1], "-sortone") == 0) ){
			if (strcmp (argv[1], "-sortall") == 0){         
				stable_sort(fruit.begin(), fruit.end()); // sort the vector     
				int k = 1;
				print (fruit, k, fruit.size());		// print
			}
			else if (strcmp (argv[1], "-sortone") == 0){
				stable_sort (fruit.begin(), fruit.end()); //sort the vector
				for (int z = 0; z < count; z++){		// compare the 2 fruit_name next to each other. If =, combine quantity
					for (int k = z + 1; k < count; k++) {
						if (strncmp (fruit[z].fruit_name,fruit[k].fruit_name, MAX_LENGTH) == 0){
							fruit[z].quantity += fruit[k].quantity;
						}	
					}
				}
			set <fruit_t> s;	// declare set
			unsigned size = fruit.size();
			for ( unsigned a = 1; a < size; a++) s.insert(fruit[a] ); // insert each variables with unique name inside the for loop
			fruit.assign (s.begin(), s.end() );
				for ( i = 0;i < 1 ; i++){
					print (fruit, i, fruit.size());	     
				}	
			}	
        }
	fruit.clear(); // free the vector
	inFile.close();
	return (0);
}


void print (vector<fruit_t> fruit,int i, int count){                // print function
	float total_price=0;
	 for ( i; i < count; i++){
            cout << fixed;
            cout << setprecision(2);
            float price_per_lbs = fruit[i].quantity * fruit[i].price;
            total_price += price_per_lbs;
            cout << setfill('.') << setw(20) << left << fruit[i].fruit_name;
            cout << setfill (' ') << setw (5) << right << fruit[i].quantity
                 << setw (9) << right << fruit[i].price << " = "
                 << setw (7) << right << price_per_lbs << "  :  "
                 << setw (8) << right << total_price << endl;

          }


}

