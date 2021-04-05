#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <iostream>
#include "dset.h"
using namespace std;

struct cell
{
  cell()
  {
    r = 0;
    c = 0;
  }
  int r;
  int c;
};

void swap(cell &c1, cell &c2)
{
  cell temp = c1;
  c1 = c2;
  c2 = temp;
}

int main(int argc, char *argv[])
{
  if (argc != 4)
  {
    printf("usage: \n ");
    return 0;
  }

  FILE *fin;
  fin = fopen(argv[3], "w"); // Open output file for writing (argv[3])

  if (fin == NULL)
  {
    printf("File failed to open \n");
  }
  else
  {
    int Nrow = atoi(argv[1]);
    int Ncol = atoi(argv[2]);
    fprintf(fin, "MAZE %d  %d \n", Nrow, Ncol);
    int k = 0;
    int N = ((Ncol - 1) * Nrow) + ((Nrow - 1) * Ncol); //number of interior grid walls

    cell wall[N][2]; // [0] for current cell, [1] for adjacent cell
        
        //populate wall[][] with interior grid walls

    for (int i = 0; i < Ncol - 1; i++) 
    {
      for (int j = 0; j < Nrow; j++) 
      {
        wall[k][0].r = i; 
        wall[k][0].c = j; 
        wall[k][1].r = i + 1;
        wall[k][1].c = j;
        k++;
      }
    }
    for (int i = 0; i < Ncol; i++) 
    {
      for (int j = 0; j < Nrow - 1; j++) 
      {
        wall[k][0].r = i; 
        wall[k][0].c = j; 
        wall[k][1].r = i;
        wall[k][1].c = j + 1;
        k++;
      }
    }
    srand(time(NULL));
    //randomly perturb list order: swap based

    for (int i = N - 1; i > 0; --i)
    {
      int a = rand() % (i+1);
      swap (wall[i], wall[a]);

    }
    dset DS(Nrow * Ncol);

    //write MAZE, Nrow, Ncol header
    int i = 0;
    for (; i < N; i++)
    {
      int ii = wall[i][0].c + (wall[i][0].r * Nrow);
      int jj = wall[i][1].c + (wall[i][1].r * Nrow);

      //printf ("ii = %d, jj = %d\n", ii, jj);
      if (DS.find(ii) != DS.find(jj)) //pair of cells given by wall[k][] are not connected (belong to different disjoint sets),merge them
      {
        DS.merge(ii, jj);
      }
      else //write wall location to file as two pairs of cell indices: i0 j0 i1 j1
      {
        fprintf(fin, "  %d ", wall[i][0].c);
        fprintf(fin, "  %d ", wall[i][0].r);
        fprintf(fin, "  %d ", wall[i][1].c);
        fprintf(fin,"  %d \n", wall[i][1].r);
      }

      if (DS.size() == 1)
        break; // all cells belong to the same set, break
    }
    i++;
    for (; i < N; i++) //write any remaining walls to file
    {
      fprintf(fin,"  %d ", wall[i][0].c);
      fprintf(fin,"  %d ", wall[i][0].r);
      fprintf(fin,"  %d ", wall[i][1].c);
      fprintf(fin,"  %d \n", wall[i][1].r);
    }
    fclose(fin); //close output file
  }
}
