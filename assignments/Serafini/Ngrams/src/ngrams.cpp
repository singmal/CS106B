// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include "vector.h"
#include "console.h"
#include "strlib.h"
#include "map.h"
#include "random.h"

using namespace std;

// 不断提示输入直到成功的两种写法
void PromptForFile(ifstream& infile);
bool PromptForN(int &num);
void ConstructMap(ifstream& infile, Map<Vector<string>, Vector<string> >& map, int N);
void MapInsertKey(Map<Vector<string>, Vector<string> >& map, Vector<string>& window, string word);
void WindowUpdate(Vector<string>& window, string word);
bool PromptForWordsToGener(int& num, int N);


int main()
{
    ifstream inFile;
    PromptForFile(inFile);

    int N;
    while(!PromptForN(N));

    Map<Vector<string>, Vector<string> > map;
    ConstructMap(inFile, map, N);

    while (true)
    {
        cout << endl;
        int num;
        while(!PromptForWordsToGener(num, N));
        if (num == 0)
        {
            cout << "Exiting.";
            return 0;
        }

        Vector<Vector<string> > Keys = map.keys();
        int map_key_length = Keys.size();
        int index = randomInteger(1, map_key_length) - 1;
        Vector<string> window = Keys[index];

        cout << "... ";
        for (string word : window)
        {
            cout << word << " ";
        }
        for (int i = 0; i < num; i++)
        {
            Vector<string> candidate = map[window];
            int length = candidate.size();
            int idx = randomInteger(1, length) - 1;
            string next_word = candidate[idx];
            cout << next_word << " ";
            window.remove(0);
            window.push_back(next_word);
        }
        cout << "..." << endl;
    }

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

void ConstructMap(ifstream& infile, Map<Vector<string>, Vector<string> >& map, int N)
{
    string word;
    Vector<string> window;
    Vector<string> save_head;

    while (infile >> word)
    {
        if (window.size() < N - 1)
        {
            window.push_back(word);
            save_head.push_back(word);
            continue;
        }

        MapInsertKey(map, window, word);
        WindowUpdate(window, word);
    }

    for (int i = 0; i < N - 1; i++)
    {
        string word = save_head[i];
        MapInsertKey(map, window, word);
        WindowUpdate(window, word);
    }
}

void MapInsertKey(Map<Vector<string>, Vector<string> >& map, Vector<string>& window, string word)
{
    if (map.containsKey(window))
    {
        map[window].push_back(word);
    }

    else
    {
        Vector<string> tmp;
        tmp.push_back(word);
        map[window] = tmp;
    }
}

void WindowUpdate(Vector<string>& window, string word)
{
    window.remove(0);
    window.push_back(word);
}

bool PromptForWordsToGener(int& num, int N)
{
    cout << "# of random words to generate (0 to quit)?";
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
    if (num < N && num != 0)
    {
        cout << "Must be at least " << N << " words." << endl << endl;
        return false;
    }

    return true;
}
