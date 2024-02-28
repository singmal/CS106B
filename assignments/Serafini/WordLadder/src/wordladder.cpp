// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include "console.h"
#include "lexicon.h"

using namespace std;

void WelcomeInfo();
void LoadDict(Lexicon& dict);

int main()
{
    WelcomeInfo();

    Lexicon dict;
    LoadDict(dict);

    return 0;
}

void WelcomeInfo()
{
    cout << "Welcome to CS 106B Word Ladder." << endl;
    cout << "Please give me two English words, and I will change the" << endl;
    cout << "first into the second by changing one letter at a time." << endl;
    cout << endl;
}


void LoadDict(Lexicon& dict)
{
    ifstream infile;
    cout << "Dictionary file name? ";
    string filename;
    cin >> filename;

    infile.open(filename);
    string word;
    while(getline(infile, word))
    {
        dict.add(word);
    }

    cout << endl;
}
