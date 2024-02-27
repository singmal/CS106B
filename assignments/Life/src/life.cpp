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
    ifstream infile;
    while (true)
    {
        string filename;
        cout << "Grid input file name? ";
        cin >> filename;
        infile.open(filename);

        if (infile.is_open())
            break;
        else
        {
            infile.clear();
            cout << "Unable to open that file. Try again." << endl;
        }
    }

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

    while (cin.get() != '\n')
        continue;

    ShowGrid(colony);
    GenerNext(colony, wrap);
    ShowGrid(colony);

    cout << "a)nimate, t)ick, q)uit? ";
    while (cin.get(ch))
    {
        while (cin.get() != '\n')
            continue;

        bool over = false;
        switch(ch)
        {
            case 'a':
            case 'A':
                {
                    string frames;
                    while (true)
                    {
                        cout << "How many frames? ";
                        cin >> frames;

                        while (cin.get() != '\n')
                            continue;

                        bool all_num = true;
                        if (frames.length() == 0)
                            all_num = false;
                        for (char f : frames)
                        {
                            if (!isdigit(f))
                                all_num = false;
                        }
                        if (all_num)
                        {
                            int iters = stringToInteger(frames);
                            for (int i = 0; i < iters; i++)
                            {
                                GenerNext(colony, wrap);
                                ShowGrid(colony);
                                pause(50);
                                clearConsole();
                            }
                            break;
                        }
                    }
                    break;
                }
            case 't':
            case 'T':
                GenerNext(colony, wrap);
                ShowGrid(colony);
                break;
            case 'q':
            case 'Q':
                over = true;
                break;
        }
        if (over)
            break;
        cout << "a)nimate, t)ick, q)uit? ";
    }

    return 0;
}
