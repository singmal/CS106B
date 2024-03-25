#ifndef _boggle_h
#define _boggle_h

#include <iostream>
#include <string>
#include "lexicon.h"
#include "grid.h"
#include "set.h"
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
        Set<string> getHumanWordsFound();
        Set<string> getComputerWordsFound();

        friend ostream& operator<<(ostream& out, Boggle& boggle);

    private:
        Grid<char> board;
        Lexicon& dict;
        Set<string> humanWordsFound;
        Set<string> computerWordsFound;
        int humanScore;
        int computerScore;

        bool humanWordSearchHelper(string word, int i, int j, int idx, Grid<char>& mark);
        void computerWordSearchHelper(string word, int i, int j, Grid<char>& mark);
};

#endif // _boggle_h
