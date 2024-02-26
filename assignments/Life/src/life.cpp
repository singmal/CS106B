#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "console.h"
#include "filelib.h"
#include "grid.h"
#include "gwindow.h"
#include "simpio.h"
#include "strlib.h"
#include "lifegui.h"
using namespace std;

void InputGridData(Grid<char> &col)
{
    string filename;
    cout << "Grid input file name? ";
    cin >> filename;

    ifstream infile;
    infile.open(filename);
    int h, w;
    infile >> h >> w;

    col.resize(h, w);
    char ch;
    for (int r = 0; r < col.numRows(); r++)
    {
        infile.get(ch);
        for (int c = 0; c < col.numCols(); c++)
        {
            infile.get(ch);
            col[r][c] = ch;
        }
    }

    infile.close();
}

void ShowGrid(Grid<char> &col)
{
    for (int r = 0; r < col.numRows(); r++)
    {
        for (int c = 0; c < col.numCols(); c++)
        {
            cout << col[r][c];
        }
        cout << endl;
    }
}

int main()
{
    Grid<char> colony;
    InputGridData(colony);

    bool wrap;
    cout << "Should the simulation wrap around the grid (y/n)? ";
    char ch;
    cin >> ch;
    if (ch == 'y' || ch == 'Y')
        wrap = true;
    else
        wrap = false;

    ShowGrid(colony);

    return 0;
}
