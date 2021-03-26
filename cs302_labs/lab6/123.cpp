/*
  Name: An Phan
  CS-302
  Notes: The use of the class constructor and operator()
         The use of getting value from the table of constructor
  Improve: create a function do the calculation and call it in constructor 
            not practical to do whole calculation in constructor 
*/

#include <string.h>
#include <set>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iterator>
#include <sstream>   //istringstream
#include <iomanip>   // fixed, setprecision
#include <algorithm> // std::swap
#include <cmath>     // M_PI
#define DISTANCE 0   // global variable for distance
#define TIME 1       // global variable for time
using namespace std;

class city
{
public:
  string get_name() { return name; }
  string get_type() { return type; }
  int get_zone() { return zone; }
  float get_latitude() { return latitude; }
  float get_longitude() { return longitude; }
  int get_population() { return population; }

  friend istream &operator>>(istream &, city &);
  friend ostream &operator<<(ostream &, const city &);

private:
  string name;
  string type;
  int zone;
  float latitude;
  float longitude;
  int population;
};
/*
  Overload the input stream (aka read)
*/
istream &operator>>(istream &inFile, city &c)
{
  inFile >> c.zone >> c.name >> c.type >> c.latitude >> c.longitude >> c.population;
  return inFile;
}
// Overload the output stream (aka print)
ostream &operator<<(ostream &outFile, const city &c)
{

  outFile << setw(18) << left << c.name << setw(12) << c.type
          << setw(5) << left << c.zone << setw(10) << right << c.population
          << setw(12) << right << fixed << setprecision(2)
          << c.latitude << setw(12) << right << c.longitude
          << endl;
  return outFile;
}
void read_cityinfo(vector<city> &v_city)
{
  ifstream fin;
  fin.open("city_list.txt");
  city c;
  std::string line;
  while (getline(fin, line)) // get each line of the input file into variable line to parse
  {
    istringstream split_this(line); // parse each element of line
    if (line[0] == '#')
      continue; // if hit the #, skip this line
    if (line == "")
      continue;          // if blank line, skip this line
    split_this >> c;     // read parsed element into class c
    v_city.push_back(c); // push element into vector
  }
  fin.close(); // close file
}
void write_cityinfo(vector<city> &v_city)
{
  ofstream fout;
  fout.open("city_info.txt");
  int size = v_city.size();
  fout << " CITY INFO (N=" << size << "):" << endl;
  fout << endl;
  for (int i = 0; i < size; i++)
  {
    fout << v_city[i];
  }

  fout.close();
}
class costtable
{
public:
  vector<float> distance;    // table for distance
  vector<float> time;        // table for time
  costtable(vector<city> &c) // costtable class constructor
  {
    int N = (int)c.size();      // the size of vector c
    for (int i = 0; i < N; i++) // nested loop for i-th city
    {
      for (int j = 0; j <= i; j++) // for j-th city
      {
        float rad = 3982; // radius of Earth
        //assign the value from class city
        float deg_long1 = c[i].get_longitude();
        float deg_long2 = c[j].get_longitude();
        float deg_lat1 = c[i].get_latitude();
        float deg_lat2 = c[j].get_latitude();

        //convert to radian
        float rad_long1 = deg_long1 * (M_PI / 180);
        float rad_long2 = deg_long2 * (M_PI / 180);
        float rad_lat1 = deg_lat1 * (M_PI / 180);
        float rad_lat2 = deg_lat2 * (M_PI / 180);

        // Thee haversine formula
        float delta_long = rad_long2 - rad_long1; // calculate delta longitude
        float delta_lat = rad_lat2 - rad_lat1;    // calculate the delta latitude
        // part under square root
        float distance_calculated = pow(sin(delta_lat / 2), 2) +
                                    pow(sin(delta_long / 2), 2) *
                                        cos(rad_lat1) * cos(rad_lat2);
        float result_in_KM = rad * (2 * asin(sqrt(distance_calculated))); // final answer
        // convert to Miles from KM
        float result_in_MILES = 10.0 * round(result_in_KM / 10.0);
        distance.push_back(result_in_MILES); // push to table distance

        /* Calculate TIME 
            Goods shipped between REGIONAL cities go by ground.
            Goods shipped between REGIONAL cities and a GATEWAY city in the same zone go by air.
              Goods shipped between GATEWAY cities go by air no matter what the zone they are in.
            */
        if (c[i].get_type() == c[j].get_type() && c[i].get_type() == "REGIONAL")
        {
          time.push_back(result_in_MILES / 60); // ship by ground
        }
        else
          time.push_back(result_in_MILES / 570); // ship by air
      }
    }
  }
  float operator()(int mode, int i, int j)
  {
    if (mode == DISTANCE)
    {
      if (i < j)
      {
        swap(i, j); // if go out of bound, swap to stay in the bound
      }
      return distance[(i * (i + 1) / 2 + j)]; // return the location on the distance table
    }
    if (mode == TIME)
    {
      if (i < j)
      {
        swap(i, j); // if go out of bound, swap to stay in the bound
      }
      return time[(i * (i + 1) / 2 + j)]; // return the location of the time table
    }
    return ((i * (i + 1) / 2 + j)); // because of the warning messeage
  }
};

/*
  Write from distance table to file 
*/
void write_distancetable(vector<city> &c)
{
  ofstream outFile;
  outFile.open("city_distancetable.txt");
  int N = (int)c.size();
  costtable c_t(c); //set up costtables
  string line;
  outFile << "DISTANCE TABLE:" << endl;
  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j <= i; j++)
    {
      if (i != j)
      {
        line = c[i].get_name() + " to " + c[j].get_name();
        outFile << i << "  " << setfill('.') << setw(39) << left << line
                << right << setw(10) << fixed << setprecision(1) << c_t(DISTANCE, i, j)
                << right << " miles" << endl;
      }
    }
    outFile << endl;
  }

  outFile.close();
}
/*
  Write from time table to file 
*/
void write_timetable(vector<city> &c)
{
  ofstream outFile;
  outFile.open("city_timetable.txt");
  int N = (int)c.size();
  costtable c_t(c);
  string line;
  outFile << "TIME TABLE" << endl;
  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j <= i; j++)
    {
      if (i != j)
      {
        line = c[i].get_name() + " to " + c[j].get_name();
        outFile << i << "  " << setfill('.') << setw(39) << left << line
                << right << setw(10) << fixed << setprecision(1) << c_t(TIME, i, j)
                << right << " hours" << endl;
      }
    }
    outFile << endl;
  }
  outFile.close();
}

void create_citygraph(vector<city> &c, vector<vector<int> > &c_graph)
{
  int N = (int)c.size();
  costtable c_t(c);
  c_graph.resize(N);
  set<int> regional;
  set<int> gateway;
  set<int>::iterator it;
  set<int>::iterator it2;
  vector< pair<int, int> > dist;
  vector<pair<float, int> > dist_temp;

  for (int i = 0; i <  N; i++)
  {
    c_graph[i].resize(N);
  }
  for (int i = 0; i < N; i++)
  {
    if (c[i].get_type() == "REGIONAL")
      regional.insert(i);
    else
      gateway.insert(i);
  }

  for (it = regional.begin(); it != regional.end(); it++)
  {
    for (it2 = regional.begin(); it2 != regional.end(); it2++)
    {
      if (*it != *it2)
      {  
        if (c[*it].get_zone() == c[*it2].get_zone())
        {
          c_graph[*it].push_back(*it2);
          //c_graph[*it2].push_back(*it);
       
        }
      }
    }
  }
  for (it = gateway.begin(); it != gateway.end(); it)
  {
    for (it2 = gateway.begin(); it2 != gateway.end(); ++it2)
    {
      if (*it != *it2)
      { 
        if (c[*it].get_zone() == c[*it2].get_zone())
        {
          c_graph[*it].push_back(*it2);
          //c_graph[*it2].push_back(*it);
        }
      
        if (*it != *it2 && c[*it].get_zone() != c[*it2].get_zone())
        {
          float distance = c_t(DISTANCE, *it, *it2);
          if (distance <= 5200)
          {
            c_graph[*it].push_back(*it2);
            //c_graph[*it2].push_back(*it);

          }
        }
      }
    }
  }
  float distance ;
  for (it = gateway.begin(); it != gateway.end(); ++it)
  {
    for (it2 = gateway.begin(); it2 != gateway.end(); ++it2)
    {
      if ( *it != *it2)
      {
          if (c[*it].get_zone() == c[*it2].get_zone())
          {
            distance = c_t(DISTANCE, *it, *it2);
            dist.push_back(make_pair(distance, *it2));
          }
      }
    }
    std::sort(dist.begin(), dist.end());
    //c_graph[*it].push_back(dist[0].second);
    c_graph[dist[0].second].push_back(*it);
    
  }

}

void write_citygraph(vector<city> &c, vector<vector<int> > &c_graph)
{
  ofstream outFile;
  int N = (int)c.size();
  costtable c_t(c);
  vector<int>::iterator it;

  outFile.open("city_graph.txt");
  outFile << "CITY GRAPH:" << endl;
  outFile << endl;
  for (int i = 0; i < N; i++)
  {
    std::sort(c_graph[i].begin(), c_graph[i].end());
    outFile << i << " " << c[i].get_name() << endl;
    for (it = c_graph[i].begin(); it != c_graph[i].end(); ++it)
    {
      sort(c_graph[*it].begin(), c_graph[*it].end());

      outFile << setw(6) << *it << " " << c[*it].get_name()
              << right << setw(25 - c[*it].get_name().length()) << fixed << setprecision(1) << c_t(DISTANCE, i, *it) << right << " miles"
              << right << setw(10) << fixed << setprecision(1) << c_t(TIME, i, *it) << right << " hours" << endl;
    }
    outFile << endl;
  }
}

template <typename Tkey, typename Twgt>
class graph
{    
public:    
  void dijkstra_route(Tkey &, Tkey &);
private:
  void dijkstra_route(int, int);
  void show_route(int, int);
  typedef enum
  {
    WHITE,
    BLACK
  } vcolor_t;
  vector<vcolor_t> vcolor;
  vector<Twgt> vdist;
  vector<int> vlink;
};
/*
template <typename Tkey, typename Twgt>
void graph<Tkey,Twgt>::dijkstra_route(int source, int sink) 
{  
  vcolor.assign(V.size(), WHITE);
  vdist.assign(V.size(), numeric_limits<Twgt>::max());
  vdist[source] = 0;
  vlink.assign(V.size(), -1);
  vlink[source] = source;
  while (1)
  {
    int next_i = -1;
    Twgt mindist = numeric_limits<Twgt>::max();
    for (int i = 0; i < (int)vcolor.size(); i++)
    {
      if (vcolor[i] == WHITE && mindist > vdist[i])
      {
        next_i = i;
        mindist = vdist[i];
      }
    }
    int i = next_i;
    if (i == -1)
      return;
    vcolor[i] = BLACK;
    if (i == sink)
      break;
    for (int k = 0; k < (int)E[i].size(); k++)
    {
      int j = E[i][k];
      Twgt wij = W[i][k];
      if (vcolor[j] == WHITE)
      {
        if (vdist[j] > vdist[i] + wij)
        {
          vdist[j] = vdist[i] + wij;
          vlink[j] = i;
        }
      }
    }
  }
}
*/
int main(int argc, char *argv[])
{
  string mode_graphinfo;
  string source, sink;

  if (argc == 2 && (strcmp(argv[1], "-graphinfo") == 0))
  {
    vector<city> v_city; //city graph declarations
    vector<vector<int> > c_graph;

    read_cityinfo(v_city);
    write_cityinfo(v_city);
    create_citygraph(v_city, c_graph);
    if (strcmp(argv[1], "-graphinfo") == 0)
    {
      write_cityinfo(v_city);

      write_distancetable(v_city);
      write_timetable(v_city);

      write_citygraph(v_city, c_graph);

      // return from program
    }
  }  
  else if (argc == 2 && (strcmp(argv[1], "-distance") == 0 || strcmp(argv[1], "-time") == 0) )
  {
    while (!cin.eof()) 
    {
      //enter> from, to cities
      cout << "Enter> ";
      cin >> source >> sink;
     // dijkstra_route(costmode,from,to) 
    }
  }
  
  else
    cout << "usage: ./Citysim1 -distance|time|graphinfo" << endl;
}
