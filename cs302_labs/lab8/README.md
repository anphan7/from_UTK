# COSC 302--Lab 8 (Spring 2021) 

## Getting Motivated
In this lab, you will use the dynamic programming based algorithm covered in class for determining the longest common subsequence given two strings to implement "Diff8" which is a scaled-back version of the Unix diff command. The program shows the user if two text files are different and if so, how to edit one into the other: which lines to delete, which lines to add, and which lines to change (replace).

### Assignment Details

To help you get started, run the Hydra script /home/cosc302/labs/lab8/copy to obtain the following files: sdiff8 (Hydra solution executable), Diff8.cpp (skeleton driver program source code), a makefile, and two test files called original.txt and modified.txt. The text is based on a poem for 6th graders written by Kenn Nesbitt (2005).

Create a class called LCS which has public member functions for adding text to two private buffers called text1 and text2 as well as for public member functions for computing the dynamic programming based alignment and subsequently reporting the difference between the files.

Public member function compute_alignment() uses a cost function that associates deletions and insertions with a cost of 1, sets the cost of a perfect match to 0 and doesn't allow substitutions. These edit operations apply to lines of text, not symbols. That is, the goal is determine the fewest number of lines that need to be deleted from text1 and inserted from text2 in order to make the two become identical. Thus, a match only occurs when two lines of text are identical.

Public member function report_difference() is conveniently implemented as wrapper for a recursive private member function of the same name that uses link information provided by compute_alignment() to extract the the sequence of edit operations that solves the alignment problem. While many such sequences may exist, we are only interested in one. The sdiff8 solution executable chooses a match if possible followed first by a deletion and then an insertion. If the three operations all have different costs, the order in which we consider them doesn't matter. Occasionally, two or more will cost the same, and then a different order will produce a different unique edit sequence. **Be sure to use the above mentioned order of comparisons to be consistent with the solution code (which may or may not be consistent with the Unix version of diff).**

Once the trace, which represents the sequence of edit opeations, has been extracted, you need to parse it. That is, the program output should ultimately reflect edits based on sequences of deletions (remove text from file1), insertions (add text from file2), and changes (replace text from file1 with text from file2). For example, the edit sequence DELETE, DELETE, MATCH, INSERT, INSERT, DELETE, MATCH, MATCH, INSERT, MATCH should be condensed to DELETE two lines from file1, CHANGE one line from file1 into two lines from file2, and INSERT one line from file2 with explicit reference to the lines involved. Once you think about it, you quickly realize that the MATCH operations determine the start and end of these sequences. You will find an example included below. Study it carefully. Then study it again. If the output confuses you, read descriptions of the Unix command diff which produces similar type of output. (The man page may not be very helpful -- Google will return links to more informative explanations). Consider using a private member function to handle printing of the edit


### Data and executable output example
#### Data: raw and sorted
```
cat -n original.txt

     1	
     2	My computer ate my homework.
     3	Yes, it's troublesome, but true.
     4	Though it didn't gnaw or nibble
     5	and it didn't chomp or chew.
     6	
     7	It devoured days of typing,
     8	every picture, chart and graph,
     9	but the worst thing about it 
    10	was I thought I heard it laugh.
    11	
    12	But I found a good solution
    13	and I smiled to hear the crash,
    14	when I chucked it out the window
    15	and it landed in the trash.
    16	
    17	H. Iznogood

unix> cat -n modified.txt

     1	Poem by Ivana Bedone
     2	
     3	My computer ate my homework.
     4	Yes, it's troublesome, but true.
     5	I thought I knew what I was doing,
     6	but it's clear I had no clue.
     7	
     8	It wiped out days of typing,
     9	every keystroke that I'd made,
    10	What really got me though, 
    11	was it could have all been saved
    12	
    13	But I found a good solution
    14	and I smiled to hear the crash,
    15	when I chucked it out the window
    16	and it landed in the trash.

unix> ./Diff8 original.txt modified.txt

0a1
> Poem by Ivana Bedone
4,5c5,6
< Though it didn't gnaw or nibble
< and it didn't chomp or chew.
---
> I thought I knew what I was doing,
> but it's clear I had no clue.
7,10c8,11
< It devoured days of typing,
< every picture, chart and graph,
< but the worst thing about it
< was I thought I heard it laugh.
---
> It wiped out days of typing,
> every keystroke that I'd made,
> What really got me though,
> was it could have all been saved
16,17d16
<
< H. Iznogood
```


```
25: Main program including reading of files
25: Compute_alignment() -- subset of dpalign code from class
50: Report_difference() -- output must match solution code
```




















