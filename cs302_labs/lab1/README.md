# COSC 302--Lab 1 (Spring 2021) 

## Getting Motivated
WELCOME to your first CS302 lab. During the semester, you will be taken through a sequence of increasingly more difficult programming assignments. They will be challenging but matched to your programming skills which will become better and better as we go along. In case you find yourself spending too much time on an assignment, be sure to seek help from the TAs or the instructor (in that order). You can also post questions to the class using Piazza (post conceptual questions as opposed to detailed code). The important thing is for you not to back yourself into a corner where you get so frustrated that you give up.
You should find this first assigment (relatively) easy to do as it evolves around concepts you learned and practiced in CS140. If you took CS140 using Windows, use this lab to become familiar with Unix as all your programs must compile and run on a Hydra machine.


## Getting Started
Each day, the folks at Josephine's Juice Bar buy a lot of fruit for their smoothies. Management would like to know the quantity purchased of each different type of fruit (all fruit is purchased by weight) and at what cost plus the total cost. Your job is write two C++ programs that solve the problem based respectively on an array list and a linked list. Kidding aside, the real task, of course, is to get you back in the programming saddle before we get deep into new data structures and algorithms. Those of you not used to "word problems" will also gain some experience deciphering what lab assignments ask you to do.
Run the script /home/cosc302/labs/lab1/copy to obtain two Hydra executables called sfruit1 and sfruit2, data files called list1.txt, list2.txt, and list3.txt, skeleton programs called Fruit1.cpp and Fruit2.cpp, and a makefile for compiling them into Hydra executables (once properly fleshed out).

### Assignment Details

**Fruit1 -- 50 pts**
Write a program called "Fruit1" that reads a sequence of fruit purchases from file. 
Each purchase consists of the name of a fruit, the quantity purchased, and the unit cost. 
Store the purchases in an array list, e.g., std::vector< >, in one of three ways before you pretty-print the content to stdout as decribed below. Develop your program incrementally.

**Vers 1** Create a struct called fruit that can the hold the relevant data, namely, the name of the fruit, the quantity purchased, and the unit cost. Read a data file from stdin using a while loop. Enter the data in a fruit struct which you store in the array list in the order read from file. Print the name, quantity, unit cost, product purchase cost, and cumulative total purchase cost to stdout.

**Vers 2** Update the output formatting to appear like shown below. To make your life easier, the field widths used are: name (20), quantity (5), unit cost (4), product purchase cost (7), and total purchase cost (8). Be forewarned there may be an additional white space or two between the fields. All floating point numbers are printed to an accuracy of 2 decimal places.

**Vers 3** Add commandline argument processing to allow selection of three mode options, namely, inorder, sortall, and sortone. See call pattern and associated output below. You must check that the correct number of arguments is given, and that the first argument is one the three mentioned (preceeded by a dash).

**Vers 4** Add code needed to support option sortall which causes the data to be sorted in lexicographical order with respect to the fruit name. Similar named entries must appear in the same order as when read from file. To do this, overload operator< for struct fruit and apply std::stable_sort (more about this algorithm in class). Your pretty-print output code should work unchanged.

**Vers 5** Add code needed to support option sortone which combines entries of the same named fruit into one by adding the quantities. When done, shrink the array list to contain just these entries. Your pretty-print output code should work unchanged.

**Fruit2 -- 70 pts**
Write a program called "Fruit2" that reads a sequence of fruit purchases from file. Each purchase consists of the name of a fruit, the quantity purchased, and the unit cost. Store the purchases in a linked list, the implemention of which you write yourself. That is, DO NOT use std::list< >. Again, process data in one of three ways before you pretty-print the content to stdout as decribed above. Develop your program incrementally. Keep your list code as simple as possible. Do NOT place it in a class. Rather, write the code "in-place" where used (e.g., inserting node with new data, printing data from nodes, deleting nodes from list when deallocating memory at the end).

**Vers 1** Copy the code from Fruit1.cpp to Fruit2.cpp while maintaing the skeleton code comments for the latter. Bring the code back to Vers 3. Declare a struct node as the basic building block for the linked list replacing the array list. Consider using a double-linked list but feel free to keep it single-linked if you prefer. Either way, you must use a dataless header node to refer to the list. Read data from file as before only this time incrementally build a linked list that stores it. Hint: To preserve the order of the data, new data must be inserted at the end of the list. Update the print loop to sweep thru the linked list nodes while printing the data to stdout using the same format as before. Add code to deallocate list memory when done. 

**Vers 2** Update the code to either insert new data in the order read from file OR sorted in lexicographical order with respect to the fruit name. You must add code for explictly making this happen. Do NOT rely on a sorting algorithm. Instead, find the correct place in the list for each new data entry as it gets inserted. Hint: Consider updating struct fruit to also overload operator<=. Your pretty-print output code should work unchanged. Same goes for the linked list cleanup code.

**Vers 3** Update the code to either insert new data in the order read from file, sorted in lexicographical order with respect to the fruit name, OR doing the latter while consolidating similar name entries. You must once again add code for explictly making this happen. That is, find the correct place in the list for a data entry as it gets inserted. If the fruit has been purchased before, increment the quantity by the new amount. Otherwise, create and insert a new node. Hint: Consider updating struct fruit to also overload operator== and operator+= where the latter adds the quantity value associated with the new data to that of the existing old data. Your pretty-print output code should work unchanged. Same goes for the linked list cleanup code.

These verbal descriptions may seem confusing. If so, take look at the data and output examples shown below. If you still don't quite understand what needs to be done, ask questions on Piazza and in lab. You may also find making drawings of what needs to happen to be helpful.


### Data and executable output example
#### Data: raw and sorted
unix> cat list1.txt

melon_cantaloupe     2.60     2.99 <br />
apples_gala          1.80     1.21 <br />
bananas              2.88     0.49 <br /> 
oranges_naval        2.63     0.99 <br />
apples_gala          3.00     1.21 <br />
raspberries          4.76     3.25 <br />
apples_gala          1.45     1.21 <br />
mango                4.07     1.20 <br />
blueberries          3.85     2.50 <br />
oranges_honeybell    4.20     1.08 <br />
apples_jazz          4.39     2.69 <br />
oranges_honeybell    4.22     1.08 <br />

