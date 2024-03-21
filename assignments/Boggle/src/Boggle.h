#ifndef _boggle_h
#define _boggle_h

#include <iostream>
#include <string>
#include "lexicon.h"
#include "grid.h"
using namespace std;

class Boggle
{
    public:
        Boggle(Lexicon& dictionary, string boardText = "");
        char getLetter(int row, int col);
        bool checkWord(string word);
        bool humanWordSearch(string word);
        Set<string> computerWordSearch();
        int getScoreHuman();
        int getScoreComputer();

        friend ostream& operator<<(ostream& out, Boggle& boggle);

    private:
        Grid<char> board;
        Lexicon& dict;
};

#endif // _boggle_h
