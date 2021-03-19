
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>    // std::swap
#include <cmath>      // M_PI
#define DISTANCE 0
#define TIME 1
using namespace std;

class city
{
  public:

  string get_name() {return name;}
  string get_type() {return type;}
  int get_zone() {return zone;}
  float get_latitude() {return latitude;}
  float get_longitude() {return longitude;}
  int get_population() {return population;}

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
istream &operator>>(istream &inFile, city &c) 
{ 
  inFile >> c.zone >> c.name >> c.type
         >> c.latitude >> c.longitude
         >> c.population;
  return inFile;
}
ostream &operator<<(ostream &outFile, const city &c) 
{ 
  
  outFile << setw(18) << left << c.name << setw(12) << c.type 
          << setw(5) << left << c.zone << setw(10) << right << c.population 
          << setw(12) << right << fixed << setprecision(2)
          << c.latitude << setw(12) << right << c.longitude
          << endl; 
  return outFile;
}
void read_cityinfo(vector <city> &v_city) 
{
  ifstream fin;
  fin.open("city_list.txt");
  ofstream fout;
  city c;
  std::string line;
  while(getline(fin, line)) 
  {
    istringstream split_this(line);	
    if (line[0] == '#') continue;
    if (line == "") continue;
    split_this >> c;
    v_city.push_back(c);

  }
  fin.close();
}
void write_cityinfo(vector <city> &v_city) 
{ 
  ofstream fout;
  fout.open("city_info.txt");
  int size = v_city.size();
  fout << " CITY INFO (N=" << size << "):" << endl;
  fout << endl; 
  for (int i = 0; i < size; i++){
    fout << v_city[i] ;
  }

  fout.close();
}

class costtable
{
  public:
    vector <float> distance;
    costtable(vector <city> &c)
    {
      int N = (int)c.size();
      //int diagonal_matrix = (N * (N+1) / 2); // = 594 (N=34)
      for (int i = 0; i < N; i++)
      {
        for (int j = 0; j <= i; j++)
        {
          
            float rad = 3982; 
            float deg_long1 = c[i].get_longitude();
            float deg_long2 = c[j].get_longitude();
            float deg_lat1 = c[i].get_latitude();
            float deg_lat2 = c[j].get_latitude();

            //convert to radian
            float rad_long1 = deg_long1 * (M_PI / 180);
            float rad_long2 = deg_long2 * (M_PI / 180);
            float rad_lat1 = deg_lat1 * (M_PI / 180);
            float rad_lat2 = deg_lat2 * (M_PI / 180);

            float delta_long = rad_long2 - rad_long1;
            float delta_lat =  rad_lat2 - rad_lat1;

            float distance_calculated = pow(sin(delta_lat / 2), 2) +  
                                    pow(sin(delta_long / 2), 2) *  
                                    cos(rad_lat1) * cos(rad_lat2);  
            float result_in_KM = rad * (2 * asin(sqrt(distance_calculated)));
            float result_in_MILES = 10.0 * round(result_in_KM / 10.0);
            distance.push_back(result_in_MILES);
          
        }
      }
      
    }


    float  operator() (int mode, int i, int j)
    {
      if (mode == DISTANCE)
      {         
        if (i < j)
        { 
          swap (i, j);   // if go out of bound, swap to stay in the bound
        }
        return distance[ (i*(i+1)/2+j) ];
      }
    }

};
void write_distancetable(vector <city> &c) 
{ 
  ofstream outFile;
  outFile.open("city_distancetable.txt");
  int N = (int)c.size();
  costtable c_t(c);  //set up costtables
  string line;
  for (int i = 0; i < N ; i++)
  {
    for (int j = 0; j <= i; j++)
    {
      if (i != j)
      {
       line  = c[i].get_name() + " to " + c[j].get_name() ;
       outFile << setfill('.') << setw(39) << left << line 
               << right << setw(10) << fixed << setprecision(1) << c_t(DISTANCE, i, j) 
               << right << " miles" << endl;
      }
    }
  }

  outFile.close();
}
void write_timetable() 
{ 
  ofstream outFile;
  outFile.open("city_timetable.txt");


  outFile.close();
}


/*
create_citygraph() { }
write_citygraph() { }

dijkstra_route() { }
*/

int main(int argc, char *argv[])
{

  string mode = argv[1];//commandline option decoding

  //city graph declarations
  vector <city> v_city;
  //costtable c_t(v_city);  //set up costtables



  read_cityinfo(v_city);
  write_cityinfo(v_city);
 // create_citygraph()

  if (mode == "-graphinfo") {
    write_cityinfo(v_city);

   write_distancetable(v_city);
   write_timetable();

	  //write_citygraph();

    // return from program
  }
/*
  while (not done) {
  	enter> from, to cities
    dijkstra_route(costmode,from,to) 
  }
*/
}
