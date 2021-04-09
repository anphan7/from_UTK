#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <iostream>

#include "dset.h"
//#include "array_memory.h"
using namespace std;

struct cell{ 
	cell(){ r = 0; c = 0; }
	//cell( int i, int j ){ r = j; c = i; }
	int r;
	int c;
};

void swap( cell &c1, cell &c2 ){ 
	cell temp = c1;
	c1 = c2;
	c2 = temp;
}

int main(int argc, char *argv[]) {
	if (argc != 4) {
		//print usage error message to stderr
		fprintf( stderr, "Usage: ./mazemake nrows ncols maze.txt\n" ); 
		return 0;
	}

	int Nrow = atoi(argv[1]);
	int Ncol = atoi(argv[2]);

  // Grid wall:     (i0,j0) | (i1,j1)
  // Horizontal wall: (i,j) | (i+1,j)
  // Vertical wall:   (i,j) | (i,j+1)

  //int N = number of interior grid walls
	int N = ((Ncol-1)*Nrow) + ((Nrow-1)*Ncol);
  //cell wall[N][2];
    cell wall[N][2];


  //populate wall[][] with interior grid walls
	int k = 0;
	for( int i=0; i<Ncol-1; i++ ){
		for( int j=0; j<Nrow; j++ ){
			wall[k][0].r = i;
			wall[k][0].c = j;
			wall[k][1].r = i+1;
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
	for( int i=N-1; i > 0; --i ){
		int a = rand() % (i+1);
		swap( wall[i], wall[a] );
	}
	dset DS( Nrow*Ncol );
  //open output file for writing (argv[3])
	FILE* fout;
	fout = fopen(argv[3], "w" );
	
  //write MAZE, Nrow, Ncol header 
	fprintf( fout, "MAZE %i %i\n", Nrow, Ncol );
	int ii = 0, jj = 0;
	for (k=0; k<N; k++) {
		ii=wall[k][0].c + (wall[k][0].r*Ncol);
		jj=wall[k][1].c + (wall[k][1].r*Ncol);
    //if: pair of cells given by wall[k][] are not
	//connected (belong to different disjoint sets),
	//merge them
		if( DS.find(ii)	!= DS.find(jj) ){
			DS.merge( ii, jj );
		}
	//else: write wall location to file as two pairs 
	//of cell indices: i0 j0 i1 j1
		else{
			fprintf( fout, "% 3i % 3i % 3i % 3i\n", 
					wall[k][0].c, wall[k][0].r,
					wall[k][1].c, wall[k][1].r );
		}
    //if: all cells belong to the same set, break
		if( DS.size() == 1 )
			break;
  //write any remaining walls to file
	}
	k++;
	for( ; k<N; k++ ){
		fprintf( fout, "% 3i % 3i % 3i % 3i\n", 
				wall[k][0].r, wall[k][0].c,
				wall[k][1].r, wall[k][1].c );
	}

  //close output file
	fclose( fout );
}