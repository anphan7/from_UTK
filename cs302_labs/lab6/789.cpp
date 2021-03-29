#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <math.h>
#include <sstream>
#include <string>
#include <limits.h>
#include <limits>
#include <stack>

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
    friend ostream &operator<<(ostream &, city &);

private:
    string name;
    string type;
    int zone;
    float latitude;
    float longitude;
    int population;
};

istream &operator>>(istream &in, city &c)
{
    in >> c.zone >> c.name >> c.type >> c.latitude >> c.longitude >> c.population;
    c.latitude *= (M_PI / 180);
    c.longitude *= (M_PI / 180);
    return in;
}
ostream &operator<<(ostream &out, city &c)
{
    out << left << setw(18) << c.name << setw(12) << c.type << setw(2) << c.zone << right << setw(10) << c.population
        << setw(8) << fixed << setprecision(2) << (c.latitude * (180 / M_PI)) << setw(8) << fixed << setprecision(2) << (c.longitude * (180 / M_PI)) << '\n';
    return out;
}

class costtable
{
public:
    costtable(vector<city> &cvect)
    {
        for (int i = 0; i < (int)cvect.size(); i++)
        {
            for (int j = 0; j < i; j++)
            {
                if (i != j)
                {
                    //for distance
                    float dlat = (cvect[i].get_latitude() - cvect[j].get_latitude());
                    if (dlat < 0)
                    {
                        dlat *= -1;
                    }
                    float dlong = (cvect[i].get_longitude() - cvect[j].get_longitude());
                    if (dlong < 0)
                    {
                        dlong *= -1;
                    }
                    float a = pow(sin(dlat / 2), 2) + pow(sin(dlong / 2), 2) * cos(cvect[i].get_latitude()) * cos(cvect[j].get_latitude());
                    float rad = 3982;
                    float c = 2 * asin(sqrt(a));
                    float distance = (10 * round((rad * c) / 10));
                    distance_table.push_back(distance);

                    //fortime
                    if (cvect[i].get_type() == cvect[j].get_type() && cvect[i].get_type() == "REGIONAL")
                    {
                        time_table.push_back(distance / 60);
                    }
                    else
                    {
                        time_table.push_back(distance / 570);
                    }
                }
            }
        }
    }
    float operator()(int m, int i, int j)
    {
        if (m == 0)
        {
            if (i < j)
            {
                swap(i, j);
            }
            i -= 1;
            return distance_table[i * (i + 1) / 2 + j];
        }
        if (m == 1)
        {
            if (i < j)
            {
                swap(i, j);
            }
            i -= 1;
            return time_table[i * (i + 1) / 2 + j];
        }
        return 0.0;
    }

private:
    vector<float> distance_table;
    vector<float> time_table;
};

void read_cityinfo(vector<city> &cvect, string filename)
{
    ifstream fin;
    fin.open(filename.c_str());
    city obje;
    string line;
    while (getline(fin, line))
    {
        if (line[0] != '#' && line != "")
        {
            istringstream iss(line);
            iss >> obje;
            cvect.push_back(obje);
        }
    }
    fin.close();
}
void write_cityinfo(vector<city> &cvect, string newfile)
{
    ofstream fout;
    fout.open(newfile.c_str());

    fout << "CITY INFO (N=" << cvect.size() << "):" << '\n'
         << '\n';
    for (int i = 0; i < (int)cvect.size(); i++)
    {
        fout << right << setw(3) << setfill(' ') << i << " ";
        fout << cvect[i];
    }
    fout.close();
}

void write_distancetable(vector<city> &cvect, costtable &obj)
{
    ofstream fout;
    fout.open("city_distancetable.txt");
    fout << "DISTANCE TABLE:" << '\n';
    for (int i = 0; i < (int)cvect.size(); i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (i != j)
            {
                fout << setw(3) << setfill(' ') << i << " " << cvect[i].get_name() << " to "
                     << left << setw(34 - cvect[i].get_name().length())
                     << setfill('.') << cvect[j].get_name() + ' ';
                fout << right << setw(7) << setfill(' ') << fixed << setprecision(1) << obj(0, i, j) << " miles" << '\n';
            }
        }
        fout << '\n';
    }

    fout.close();
}
void write_timetable(vector<city> &cvect, costtable &obj)
{
    ofstream fout;
    fout.open("city_timetable.txt");
    fout << "TIME TABLE:" << '\n';
    for (int i = 0; i < (int)cvect.size(); i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (i != j)
            {
                fout << right << setw(3) << setfill(' ') << i << " " << cvect[i].get_name() << " to "
                     << left << setw(34 - cvect[i].get_name().length())
                     << setfill('.') << cvect[j].get_name() + ' ';
                fout << right << setw(5) << setfill(' ') << fixed << setprecision(1) << obj(1, i, j) << " hours" << '\n';
            }
        }
        fout << '\n';
    }

    fout.close();
}

void create_citygraph(vector<city> &cvect, costtable &obj, vector<vector<int> > &graph)
{
    graph.resize((int)cvect.size());
    for (int i = 0; i < (int)cvect.size(); i++)
    {
        graph[i].resize((int)cvect.size());
        for (int j = 0; j < (int)cvect.size(); j++)
        {
            graph[i][j] = 0;
        }
    }
    for (int i = 0; i < (int)cvect.size(); i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (i != j)
            {
                if (cvect[i].get_type() == "REGIONAL" && cvect[j].get_type() == "REGIONAL")
                {
                    if (cvect[i].get_zone() == cvect[j].get_zone())
                    {
                        graph[i][j] = 1;
                        graph[j][i] = 1;
                    }
                }

                else if (cvect[i].get_type() == "GATEWAY" && cvect[j].get_type() == "GATEWAY")
                {
                    if (cvect[i].get_zone() == cvect[j].get_zone())
                    {
                        graph[i][j] = 1;
                        graph[j][i] = 1;
                    }
                }
            }
        }
    }
    int temp = 0;
    int temp2 = 0;
    float distance = 0;
    for (int k = 0; k < (int)graph.size(); k++)
    {
        for (int l = 0; l < (int)graph[k].size(); l++)
        {
            if (k != l)
            {
                if (distance == 0 && cvect[k].get_zone() == cvect[l].get_zone() && cvect[k].get_type() == "REGIONAL" &&
                    cvect[k].get_type() != cvect[l].get_type())
                {
                    temp = k;
                    temp2 = l;

                    distance = obj(0, k, l);
                }
                else
                {
                    if (distance > obj(0, k, l) && cvect[k].get_zone() == cvect[l].get_zone() && cvect[k].get_type() == "REGIONAL" &&
                        cvect[k].get_type() != cvect[l].get_type())
                    {
                        temp = k;
                        temp2 = l;

                        distance = obj(0, k, l);
                    }
                }
            }
        }
        if (temp != temp2)
        {
            graph[temp][temp2] = 1;
            graph[temp2][temp] = 1;
            distance = 0;
        }
    }

    distance = 0;
    for (int zone = 1; zone < 7; zone++)
    {
        for (int k = 0; k < (int)graph.size(); k++)
        {
            for (int l = 0; l < (int)graph[k].size(); l++)
            {
                if (k != l)
                {
                    if (distance == 0 && cvect[k].get_zone() != cvect[l].get_zone() && cvect[k].get_type() == "GATEWAY" &&
                        cvect[l].get_type() == "GATEWAY" && zone == cvect[l].get_zone())
                    {
                        temp = k;
                        temp2 = l;

                        distance = obj(0, k, l);
                    }
                    else
                    {
                        if (distance > obj(0, l, k) && cvect[k].get_zone() != cvect[l].get_zone() && cvect[k].get_type() == "GATEWAY" &&
                            cvect[l].get_type() == "GATEWAY" && zone == cvect[l].get_zone())
                        {
                            temp = k;
                            temp2 = l;

                            distance = obj(0, k, l);
                        }
                    }
                }
            }
            if (distance <= 5200)
            {
                if (distance != 0)
                {
                    graph[temp][temp2] = 1;
                    graph[temp2][temp] = 1;
                }
            }
            distance = 0;
        }
    }
}

void write_citygraph(vector<city> &cvect, costtable &obj, vector<vector<int> > &graph)
{
    ofstream fout;
    fout.open("city_graph.txt");
    fout << "CITY GRAPH:" << '\n'
         << '\n';

    for (int i = 0; i < (int)graph.size(); i++)
    {
        for (int j = 0; j < (int)graph[i].size(); j++)
        {
            if (j == 0)
            {
                fout << right << setw(3) << setfill(' ') << i << " " << cvect[i].get_name() << '\n';
            }
            if (graph[i][j] == 1)
            {
                fout << right << setw(6) << setfill(' ') << j << " " << setw(20) << setfill(' ') << left << cvect[j].get_name()
                     << right << setw(6) << setfill(' ') << fixed << setprecision(1) << obj(0, j, i) << " "
                     << "miles " << right << setw(5) << setfill(' ') << fixed << setprecision(1) << obj(1, j, i) << " hours" << '\n';
            }
        }
        if ((i + 1) != (int)graph.size())
        {
            fout << '\n';
        }
    }
}

void dijkstra_route(vector<city> &cvect, costtable &obj, vector<vector<int> > &graph, string mode, string from, string to)
{
    vector<bool> vcolor;
    vector<float> vdist;
    vector<int> vlink;
    vector<vector<int> > E;
    vector<int> index;
    E.resize((int)graph.size());
    for (int i = 0; i < (int)graph.size(); i++)
    {
        for (int j = 0; j < (int)graph[i].size(); j++)
        {
            if (graph[i][j] == 1)
            {
                E[i].push_back(j);
            }
        }
        index.push_back(i);
    }
    cout << index.size() << endl;
    cout << (int)graph.size() << endl;
    int startingindex, endingindex;
    for (int i = 0; i < (int)cvect.size(); i++)
    {
        if (cvect[i].get_name() == from)
        {
            startingindex = i;
        }
        if (cvect[i].get_name() == to)
        {
            endingindex = i;
        }
    }
    vcolor.assign(index.size(), 0);
    vdist.assign(index.size(), numeric_limits<float>::max());
    vdist[startingindex] = 0;
    vlink.assign(index.size(), -1);
    vlink[startingindex] = startingindex;

    while (1)
    {
        int next_i = -1;
        float mindist = numeric_limits<float>::max();
        for (int i = 0; i < (int)vcolor.size(); i++)
        {
            if (vcolor[i] == 0 && mindist > vdist[i])
            {
                next_i = i;
                mindist = vdist[i];
            }
        }
        int i = next_i;
        if (i == -1)
        {
            return;
        }
        vcolor[i] = 1;

        if (i == endingindex)
        {
            break;
        }

        for (int k = 0; k < (int)E[i].size(); k++)
        {
            int j = E[i][k];
            float wij;
            if (mode == "-distance")
            {
                wij = obj(0, i, j);
            }
            if (mode == "-time")
            {
                wij = obj(1, i, j);
            }

            if (vcolor[j] == 0)
            {
                if (vdist[j] > vdist[i] + wij)
                {
                    vdist[j] = vdist[i] + wij;
                    vlink[j] = i;
                }
            }
        }
    }

    if (vdist[endingindex] == numeric_limits<float>::max())
    {
        cout << "No path from " << cvect[startingindex].get_name() << " to " << cvect[endingindex].get_name() << '\n';
        return;
    }

    stack<int> s;
    for (int p = endingindex; p != startingindex; p = vlink[p])
        s.push(p);
    s.push(startingindex);

    float fin = 0.0;
    int temp = 0;
    if (mode == "-distance")
    {
        while (!s.empty())
        {
            int p = s.top();
            s.pop();
            cout << right << setw(7) << setfill(' ') << fixed << setprecision(1) << vdist[p] << " miles"
                 << right << setw(6) << setfill(' ') << fixed << setprecision(1) << fin << " hours : "
                 << right << setw(2) << setfill(' ') << p << " " << left << setw(18) << setfill(' ')
                 << cvect[p].get_name();
            if (fin != 0)
            {
                cout << " " << right << setw(6) << setfill(' ') << fixed << setprecision(1) << obj(0, p, temp) << " miles"
                     << right << setw(6) << setfill(' ') << fixed << setprecision(1) << obj(1, p, temp) << " hours" << '\n';
            }
            if (fin == 0)
            {
                cout << '\n';
            }

            temp = p;

            if (!s.empty())
            {
                fin += obj(1, p, s.top());
            }
        }
    }

    if (mode == "-time")
    {
        while (!s.empty())
        {
            int p = s.top();
            s.pop();
            cout << right << setw(7) << setfill(' ') << fixed << setprecision(1) << fin << " miles"
                 << right << setw(6) << setfill(' ') << fixed << setprecision(1) << vdist[p] << " hours : "
                 << right << setw(2) << setfill(' ') << p << " " << left << setw(18) << setfill(' ')
                 << cvect[p].get_name();
            if (fin != 0)
            {
                cout << " " << right << setw(6) << setfill(' ') << fixed << setprecision(1) << obj(0, p, temp) << " miles"
                     << right << setw(6) << setfill(' ') << fixed << setprecision(1) << obj(1, p, temp) << " hours" << '\n';
            }
            if (fin == 0)
            {
                cout << '\n';
            }

            temp = p;

            if (!s.empty())
            {
                fin += obj(0, p, s.top());
            }
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc > 2)
    {
        cerr << "Usage: " << argv[0] << " [-distance|time|graphinfo] file.txt" << '\n';
        return 1;
    }
    string mode;
    if (argc == 2)
    {
        mode = argv[1];
    }
    //city graph declarations
    vector<vector<int> > graph;

    vector<city> cvect;
    read_cityinfo(cvect, "city_list.txt");

    //set up costtables
    costtable object(cvect);
    create_citygraph(cvect, object, graph);

    if (mode == "-graphinfo")
    {
        write_cityinfo(cvect, "city_info.txt");

        write_distancetable(cvect, object);
        write_timetable(cvect, object);
        write_citygraph(cvect, object, graph);

        //return from program
        return 0;
    }
    string from, to;
    cout << "Enter> ";
    while (cin >> from >> to)
    {
        if (mode == "-distance")
        {
            dijkstra_route(cvect, object, graph, mode, from, to);
        }

        if (mode == "-time")
        {
            dijkstra_route(cvect, object, graph, mode, from, to);
        }
        cout << '\n'
             << "Enter> ";
    }
    cout << '\n';
}