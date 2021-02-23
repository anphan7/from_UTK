#include <fstream>
#include <string>
#include <stdio.h>
#include <iostream>

using namespace std;
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "usage: %s filename\n", argv[0]);
        fprintf(stderr, "i know this is dumb but the easiest way to code this is to ignore the .ppm at the end of the filename, so don't include the .ppm in the command-line args\nfor example, %s truck instead of %s truck.ppm", argv[0], argv[0]);
    }

    std::string file = argv[1];
    std::ifstream fin((file).c_str());
    std::ofstream fout((file + "_conv.ppm").c_str());

    std::string id;
    int ncols, nrows;
    int maxval;

    fin >> id >> ncols >> nrows >> maxval;
    fout << id << '\n' << ncols << ' ' << nrows << '\n' << maxval << '\n';

    while (fin.get() != '\n');

    int nrgb_read;
    int npixels_read = 0;
    unsigned char *rgb_ptr;
    unsigned char buf[15];

    char text[80];

    while (1)
    {
        fin.read((char *)buf, 15);
        cout << buf << endl;
        nrgb_read = fin.gcount() / 3;
        if (nrgb_read == 0 && fin.eof())
            break;

        sprintf(text, "%07d ", npixels_read);
        fout << text;

        rgb_ptr = buf;
        for (int i = 0; i < nrgb_read; i++) 
        {
            fout << ' ';
            for (int j = 0; j < 3; j++)
            {
                sprintf(text, " %03u", *rgb_ptr++);
                fout << text;
            }
        }
        fout << '\n';

        npixels_read += nrgb_read;
    }
    fin.close();
    fout.close();

    return 0;
}