#include <unistd.h>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <ctime>

struct cell
{
  int r, c;
  cell(int i = -1, int j = -1)
  {
    c = i;
    r = j;
  }
};

typedef enum direction
{
  GO_LEFT,     
  GO_UP,    
  GO_RIGHT, 
  GO_DOWN   
} DIR_T;

DIR_T get_dir(int x1, int y1, int x2, int y2)
{
  if (x1 == x2)
  {
    if (y1 < y2)
    {
      return GO_DOWN;
    }
    return GO_UP; 
  }
  if (x1 < x2)
  {
    return GO_RIGHT;
  }
  return GO_LEFT;
  
  
}

bool solve(bool ***wall, bool **iswhite, cell *stack, int *stack_int, cell *S, cell *T)
{
  cell to;
  
  iswhite[S->r][S->c] = true;
  stack[*stack_int].r = S->r;
  stack[*stack_int].c = S->c;

  *stack_int += 1;
  if (S->r == T->r && S->c == T->c)
  {
    return true;
  }

  for (int d = 0; d < 4; d++) // all possible direction
  {
    if (wall[S->r][S->c][d] == true)
    {
      continue;
    }
    else if (d == GO_LEFT)
    {
      to.r = S->r - 1;
      to.c = S->c;
    }
    else if (d == GO_RIGHT)
    {
      to.r = S->r + 1;
      to.c = S->c;
    }
    else if (d == GO_UP)
    {
      to.r = S->r;
      to.c = S->c - 1;
    }
    else if (d == GO_DOWN)
    {
      to.r = S->r;
      to.c = S->c + 1;
    }

    if (iswhite[to.r][to.c] == true)
    {
      continue;
    }
    stack[*stack_int].r = to.r;
    stack[*stack_int].c = to.c;

    if (solve(wall, iswhite, stack, stack_int, &to, T)) // recursive
    {
      return true;
    }
  }
  iswhite[S->r][S->c] = false;
  *stack_int -= 1;
  return false;
}
void delete_3d_wall(int x, int y, bool ***wall)
{
  for (int i = 0; i != y; i++)
    {
      for (int j = 0; j != x; j++)
      {
        delete[] wall[i][j];
      }
      delete[] wall[i];
    }
    delete[] wall;
}
void delete_2d_iswhite(int x, bool **iswhite)
{
  for (int i = 0; i < x ; i++){
          delete[] iswhite[i];
        }
        delete[] iswhite;
}

void allocate_3d_wall(int x, int y, bool ***wall)
{
  for (int i = 0; i < y; i++)
    {
      wall[i] = new bool *[x];
      for (int j = 0; j < x; j++)
      {
        wall[i][j] = new bool[4];
      }
    }
}
void allocate_2d_iswhite(int x, int y, bool **iswhite)
{
  for (int i = 0; i < y; i++)
  {
    iswhite[i] = new bool[x];
  }
}
int main(int argc, char *argv[])
{
  if (argc != 3)
  {
    printf("usage: ./mazesolve maze.txt path.txt\n");
    return 0;
  }

  int Nrow, Ncol;
  //open input file for reading
  FILE *fp = fopen(argv[1], "r");
  if (fp){
    //open output file for writing
    FILE *out = fopen(argv[2], "w");
    //determine Nrow,Ncol from input file
    fscanf(fp, "MAZE %d %d", &Nrow, &Ncol);
    /*
    create array of walls for each grid cell
    initialize to have boundarc walls set and
    interior walls unset
    */

    // allocate the 3d wall
    bool ***wall = new bool **[Ncol];
    allocate_3d_wall(Nrow, Ncol, wall);
    
    //allocate the 2d visited 
    bool **iswhite = new bool *[Ncol];
    allocate_2d_iswhite(Nrow, Ncol, iswhite);

    // set the boundaries wall
    for (int i = 0; i < Ncol; i++)
    {
      for (int j = 0; j < Nrow; j++)
      {
        if (i == 0)
        {
          wall[i][j][GO_LEFT] = true;
        }
        if (i == (Ncol - 1))
        {
          wall[i][j][GO_RIGHT] = true;
        }
        if (j == 0)
        {
          wall[i][j][GO_UP] = true;
        }
        if (j == (Nrow - 1))
        {
          wall[i][j][GO_DOWN] = true;
        }
      }
    }

    //read input file, set interior walls
    int x1, y1, x2, y2; 
    while (fscanf(fp, "%d %d %d %d", &y1, &x1, &y2, &x2) == 4)
    {

      wall[x1][y1][get_dir(x1, y1, x2, y2)] = true;
      wall[x2][y2][get_dir(x2, y2, x1, y1)] = true;
    }

    //DFS path

    cell source = cell(0, 0);
    cell sink = cell(Nrow - 1, Ncol - 1);
    cell stack[Nrow * Ncol];
    int stack_size = 0;

    bool success_move = solve(wall, iswhite, stack, &stack_size, &source, &sink);
    if (success_move)
    {
      fprintf(out, "PATH %d %d\n", Nrow, Ncol);
      for (int i = 0; i < stack_size; i++)
      {
        fprintf(out, "%d %d\n", stack[i].c, stack[i].r);
      }
    }
    delete_3d_wall(Nrow, Ncol, wall); // delete leak memory
    delete_2d_iswhite(Ncol, iswhite);
    
    fclose(fp);
    fclose(out);
  }
  else printf ("File is not exist\n");
}