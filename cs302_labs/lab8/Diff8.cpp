#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <stack>

using namespace std;

template <typename T>
class matrix
{
  public:
    matrix(int n_Nrows = 0, int n_Ncols = 0)
    {
      Nrows = n_Nrows;
      Ncols = n_Ncols;

      buf = new T *[Nrows];
      buf[0] = new T[Nrows * Ncols];
      for (int i = 1; i < Nrows; i++)
        buf[i] = buf[i - 1] + Ncols;
    }
    ~matrix()
    {
      delete[] buf[0];
      delete[] buf;
    }

    void assign(int n_Nrows = 0, int n_Ncols = 0)
    {
      Nrows = n_Nrows;
      Ncols = n_Ncols;

      buf = new T *[Nrows];
      buf[0] = new T[Nrows * Ncols];
      for (int i = 1; i < Nrows; i++)
        buf[i] = buf[i - 1] + Ncols;
    }

    T *operator[](int i) { return buf[i]; }

    int get_Nrows() const { return Nrows; }
    int get_Ncols() const { return Ncols; }

  private:
    int Nrows, Ncols;
    T **buf;
};

class LCS
{
  public:
    LCS()
    {
      VERT = 1;
      HORZ = 2;
      DIAG = 4;
    }
    void text1_push_back(string push) { text1.push_back(push); }
    void text2_push_back(string push) { text2.push_back(push); }
    void compute_alignment();
    void report_difference();
    void print_verbose();

  private:
    // support functions
    matrix<int> cost; // edit costs
    matrix<int> link; // alignment info

    //need a private recursive function
    int report_difference(int, int);
    void print_edits(int, int, int, int);
    int VERT;
    int HORZ;
    int DIAG;
    vector<int> trace;
    vector<string> text1; // text1 buffer
    vector<string> text2; // text2 buffer
};

void LCS::compute_alignment()
{
  int m = text1.size();
  int n = text2.size();
  cost.assign((m + 1), (n + 1));
  link.assign((m + 1), (n + 1));

  cost[0][0] = 0;
  link[0][0] = 0;

  for (int i = 1; i <= m; i++)
  {
    cost[i][0] = i;
    link[i][0] = VERT;
  }

  for (int j = 1; j <= n; j++)
  {
    cost[0][j] = j;
    link[0][j] = HORZ;
  }

  for (int i = 1; i <= m; i++)
  {
    for (int j = 1; j <= n; j++)
    {
      if (text1[i - 1] == text2[j - 1])
      {
        cost[i][j] = cost[i - 1][j - 1] + 0;
        link[i][j] = DIAG;
      }

      else
      {
        if (cost[i - 1][j] < cost[i][j - 1])
        {
          cost[i][j] = cost[i - 1][j] + 1;
          link[i][j] = VERT;
        }

        else
        {
          cost[i][j] = cost[i][j - 1] + 1;
          link[i][j] = HORZ;
        }
      }
    }
  }

  //print_verbose();
}
void LCS::print_verbose()
{
  int m = text1.size();
  int n = text2.size();
  //check to make sure cost matrix and link matrix match solution
  cout << "cost matrix: " << endl;
  for (int i = 0; i <= n + 1; i++)
  {
    for (int j = 0; j < m; j++)
    {
      cout << setw(4) << cost[i][j] << " ";
    }
    cout << endl;
  }
  cout << "link matrix: " << endl;
  for (int i = 0; i <= n + 1; i++)
  {
    for (int j = 0; j < m; j++)
    {
      cout << setw(4) << link[i][j] << " ";
    }
    cout << endl;
  }
}
void LCS::report_difference()
{
  report_difference(text1.size(), text2.size());
}

int LCS::report_difference(int x, int y)
{

  if (x == 0 && y == 0)
  {
    int del_num = 0;
    int inst_num = 0;

    int i = 0, j = 0; // del_num counter and inst_num counter
    for (int k = (int)trace.size(); k >= 0; k--)
    {
      if (trace[k] == DIAG)
      {
        print_edits(i, j, del_num, inst_num);
        del_num = 0;
        i++;
        inst_num = 0;
        j++;
      }
      else if (trace[k] == HORZ)
      {
        inst_num++;
        j++;
      }
      else if (trace[k] == VERT)
      {
        del_num++;
        i++;
      }
    }
    print_edits(i, j, del_num, inst_num);
  }

  int direction = link[x][y];

  if (direction == 4)
  {
    trace.push_back(direction);
    report_difference(x - 1, y - 1);
  }
  else if (direction == 2)
  {
    trace.push_back(direction);
    report_difference(x, y - 1);
  }
  else if (direction == 1)
  {
    trace.push_back(direction);
    report_difference(x - 1, y);
  }

  return 0;
}

void LCS::print_edits(int i, int j, int del_num, int inst_num)
{

  int print_i;
  print_i = i - del_num;
  int print_j;
  print_j = j - inst_num;
  //check for insertions
  if (inst_num != 0 && del_num == 0)
  {
    //if only one insertion
    if (inst_num == 1)
    {
      cout << i << "a" << j << endl;
      cout << "> " << text2[print_j] << endl;
    }
    else
    {
      cout << i << "a";
      cout << j - inst_num + 1 << "," << j;
      cout << endl;
      for (int k = 0; k < inst_num; k++)
      {
        cout << "> " << text2[print_j] << endl;
        print_j++;
      }
    }
  }
  else if (del_num != 0 && inst_num == 0)
  {

    if (del_num == 1)
    {
      cout << i << "d" << j << endl;
      cout << "< " << text1[print_i] << endl;
    }
    else
    {
      cout << i - del_num + 1 << "," << i;
      cout << "d" << j << endl;
      for (int k = 0; k < del_num; k++)
      {
        cout << "< " << text1[print_i] << endl;
        print_i++;
      }
    }
  }
  else if (del_num != 0 && inst_num != 0)
  {
    //del_numetes then inserts
    if (del_num == 1)
    {
      cout << i;
    }
    else
    {
      cout << i - del_num + 1 << "," << i;
    }
    cout << "c";
    if (inst_num == 1)
    {
      cout << j;
    }
    else
    {
      cout << j - inst_num + 1 << "," << j;
    }
    cout << endl;

    for (int k = 0; k < del_num; k++)
    {
      cout << "< " << text1[print_i] << endl;
      print_i++;
    }
    cout << "---\n";
    for (int k = 0; k < inst_num; k++)
    {
      cout << "> " << text2[print_j] << endl;
      print_j++;
    }
  }

}

int main(int argc, char *argv[])
{
  // check two input files are specified on command line

  if (argc != 3)
  {
    cerr << "./Diff8 file1.txt file2.txt\n";
    return 1;
  }

  LCS lcs;

  ifstream inFile1;
  ifstream inFile2;

  // open the file from the argument 
  inFile1.open(argv[1]);  
  inFile2.open(argv[2]);
  
  string file1 = argv[1];
  string file2 = argv[2];
  
  if (inFile1.fail())
  {
    cerr << "File: " << file1 << " is empty or not exist " << endl;
    return 0;
  }
  if (inFile2.fail())
  {
      cerr << "File: " << file2 << " is empty or not exist " << endl;
      return 0;
  }

  while (getline(inFile1, file1))   // read the text from file1 into the lcs.text1 buffer
  {  
    lcs.text1_push_back(file1);
  }
  while (getline(inFile2, file2))   // read the text from file2 into the lcs.text2 buffer
  { 
     lcs.text2_push_back(file2);
  }

  lcs.compute_alignment();
  lcs.report_difference();
}