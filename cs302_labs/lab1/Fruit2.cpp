/*
	Name : An Phan
	CS 302 ---- Lab1
	Description: read the file into linked list
				 set the command line -inorder|-sortall|-sortone
				 -inorder: print the list 
				 -sortall: print the list with same name of fruit
				 -sortone: like sortall but combine the name and the quantity
*/

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>
using namespace std;

struct fruit_t{
	 // data declarations
	 string fruit_name;		// name of fruit
	 double quantity;		
	 double price;             
	
    bool operator<=(const fruit_t &f1) const{
        if (fruit_name <= f1.fruit_name){
            return true;
        }
        return false;
    }

    bool operator==(const fruit_t &f1) const{
        if (fruit_name == f1.fruit_name){
            return true;
        }
        return false;
    }
    void operator+=(fruit_t &f1){quantity = (f1.quantity + quantity);}  
};

struct node_t{
    fruit_t f;	//data declarations
    node_t *next; // constructor
};
void deleteList(node_t** head){
	node_t* current = *head;
	node_t* next;
	while(current != NULL){
		next = current -> next;
		delete(current);
		current = next;
	}
	*head = NULL;
}

int main(int argc, char *argv[]){
    
    //prog -inorder|sortall|sortone file.txt
    //set program mode from command line arg
    string mode;
    mode = argv[1];				//command line = mode for easy use
    fstream inFile;				// declare the input file name
    inFile.open(argv[2]);       //open file
    string line;		
	fruit_t fruit;
    node_t *list = NULL;       //declare linked_list<fruit_t>
    node_t *head;				// head of list
    node_t *curPtr;				// current pointer of list
    double total_price = 0;		
    double price_per_lbs = 0;
    while (getline(inFile, line)){     //while (reading more data)
        head = new node_t;				// create a new node every time in the loop
        istringstream split_this(line);		// split the line into specific variable
        split_this >> fruit.fruit_name >> fruit.quantity >> fruit.price;
        head->f = fruit;		
        head->next = NULL;				
        if (list == NULL){list = head;}
        else {
            curPtr = list;
            while (curPtr->next != NULL){
                curPtr = curPtr->next;
            }
            curPtr->next = head;
        }
    }
    inFile.close();

    //store data INORDER | SORTALL | SORTONE
    curPtr = list;
    fruit_t temp;
        if(argc != 3 || mode != "-inorder" && mode != "-sortall" && mode != "-sortone" ){
			cout << "ERROR " << endl;
			cout << "Command = 2" << endl; 
			cout << "Enter your command as: ./Fruit2 -inorder|-sortall|-sortone file.txt" << endl;
			return 0;
        }
        else {
            if (mode == "-sortall" || mode == "-sortone"){
                while (curPtr->next != NULL){
                    if (curPtr -> f.fruit_name > curPtr->next->f.fruit_name){ // find the node that > than the other
						// swap the nodes 
						temp = curPtr->f;
                        curPtr->f = curPtr->next->f;
                        curPtr->next->f = temp;
                        curPtr = list;
                    }
                    else { curPtr = curPtr->next;}
                }
                curPtr = list;
            }
            node_t *temp_node;
            if (mode == "-sortone") { // combine the quantity here 
                while (curPtr->next != NULL){
                    if (curPtr->f.fruit_name == curPtr->next->f.fruit_name){
                        curPtr->f.quantity += curPtr->next->f.quantity;
                        temp_node = curPtr->next;
                        curPtr->next = temp_node->next;
                        delete temp_node; // free memory
                    }
                    else{curPtr = curPtr->next;}
                }
                curPtr = list;

			}
			// pretty-print linked list content to stdout
            while (curPtr != NULL){
                price_per_lbs = curPtr->f.quantity * curPtr->f.price;
                total_price += price_per_lbs;
                cout << fixed;
                cout << setprecision(2);
                cout << setfill('.')  << setw(20) << left << curPtr -> f.fruit_name;
                cout << setfill (' ') << setw (5) << right << curPtr -> f.quantity
                                      << setw (9) << right << curPtr -> f.price<< " = "
                                      << setw (7) << right << price_per_lbs << "  :  "
                                      << setw (8) << right << total_price << endl;
                curPtr = (curPtr->next);
            }
			deleteList(&list); // free memory
			return 0;
        }
}
