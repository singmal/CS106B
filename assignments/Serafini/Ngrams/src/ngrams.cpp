// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "console.h"
#include "strlib.h"
#include "map.h"

using namespace std;

// 不断提示输入直到成功的两种写法
void PromptForFile(ifstream& infile);
bool PromptForN(int &num);
void ConstructMap(ifstream& infile, Map<vector<string>, vector<string>> map);


int main()
{
    ifstream inFile;
    PromptForFile(inFile);

    int N;
    while(!PromptForN(N));

    Map<vector<string>, vector<string>> map;



    return 0;
}

void PromptForFile(ifstream& infile)
{
    string file_name;
    while (true)
    {
        cout << "Input file name?";
        getline(cin, file_name);
        infile.open(file_name);

        if (!infile.fail())
            break;

        infile.clear();
        cout << "Unable to open that file. Try again." << endl;
    }
}

bool PromptForN(int &num)
{
    cout << "Value of N?";
    string n_str;
    getline(cin, n_str);

    int i = 0;
    for (char ch : n_str)
    {
        if (i == 0 && ch == '-')
            continue;
        if (!isdigit(ch))
        {
            cout << "Illegal interger format. Try again." << endl;
            return false;
        }
    }

    num = stringToInteger(n_str);
    if (num < 2)
    {
        cout << "N must be 2 or greater." << endl;
        return false;
    }

    return true;
}

void ConstructMap(ifstream& infile, Map<vector<string>, vector<string> > map)
{
    string word;
    vector<string> window;

    while (infile >> word)
    {
        if (window.size() < 2)
            window.push_back(word);
    }
}
