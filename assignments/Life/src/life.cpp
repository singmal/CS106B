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

int NumNeighbourCell(Grid<char> &col, int r, int c)
{
    int num = 0;
    for (int i = -1; i < 2; i++)
    {
        for (int j = -1; j < 2; j++)
        {
            if (i == 0 && j == 0)
                continue;
            int new_r = r + i;
            int new_c = c + j;
            if (col.inBounds(new_r, new_c) && col[new_r][new_c] == 'X')
                num += 1;
        }
    }
    return num;
}

int NumNeighbourCellWrap(Grid<char> &col, int r, int c)
{
    int num = 0;
    for (int i = -1; i < 2; i++)
    {
        for (int j = -1; j < 2; j++)
        {
            if (i == 0 && j == 0)
                continue;
            int new_r = (r + i + col.numRows()) % col.numRows();
            int new_c = (c + j + col.numCols()) % col.numCols();
            if (col[new_r][new_c] == 'X')
                num += 1;
        }
    }
    return num;
}

void GenerNext(Grid<char> &col, bool wrap)
{
    Grid<char> next = col;
    int neighbour = 0;
    for (int r = 0; r < col.numRows(); r++)
    {
        for (int c = 0; c < col.numCols(); c++)
        {
            if (wrap)
                neighbour = NumNeighbourCellWrap(col, r, c);
            else
                neighbour = NumNeighbourCell(col, r, c);
            switch (neighbour)
            {
                case 0:
                case 1:
                    next[r][c] = '-';
                    break;
                case 2:
                    next[r][c] = col[r][c];
                    break;
                case 3:
                    next[r][c] = 'X';
                    break;
                default:
                    next[r][c] = '-';
            };
        }
    }
    col = next;
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
    GenerNext(colony, wrap);
    ShowGrid(colony);

    return 0;
}
