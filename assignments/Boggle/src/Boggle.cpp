#include "Boggle.h"
#include "shuffle.h"
#include <cctype>

// letters on all 6 sides of every cube
static string CUBES[16] = {
    "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
    "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
    "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
    "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};

// letters on every cube in 5x5 "Big Boggle" version (extension)
static string BIG_BOGGLE_CUBES[25] = {
   "AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM",
   "AEEGMU", "AEGMNN", "AFIRSY", "BJKQXZ", "CCNSTW",
   "CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT",
   "DHHLOR", "DHLNOR", "EIIITT", "EMOTTT", "ENSSSU",
   "FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"
};

Boggle::Boggle(Lexicon& dictionary, string boardText) : dict(dictionary)
{
    board.resize(4, 4);
    wordsFound = {};
    humanScore = 0;
    if (boardText.empty())
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                boardText = shuffle(CUBES[4 * i + j]);
                board[i][j] = boardText[0];
            }
        }
    }
    else
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                char ch = boardText[4 * i + j];
                board[i][j] = toupper(ch);
            }
        }
    }
}

char Boggle::getLetter(int row, int col)
{
    if (row < 0 || row > 4 || col < 0 || col > 4)
        throw 100;
    return board[row][col];
}

bool Boggle::checkWord(string word)
{
    int size = word.size();
    for (int i = 0; i < size; i++)
    {
        word[i] = tolower(word[i]);
    }
    if (size < 4 || wordsFound.contains(word) || !dict.contains(word))
    {
        return false;
    }
    else
    {
        wordsFound.add(word);
        humanScore += (size - 3);
        return true;
    }
}

bool Boggle::humanWordSearch(string word) {
    // TODO: implement
    return false;   // remove this
}

int Boggle::getScoreHuman()
{
    return humanScore;
}

Set<string> Boggle::computerWordSearch() {
    // TODO: implement
    Set<string> result;   // remove this
    return result;        // remove this
}

int Boggle::getScoreComputer() {
    // TODO: implement
    return 0;   // remove this
}

Set<string> Boggle::getWordsFound()
{
    return wordsFound;
}

ostream& operator<<(ostream& out, Boggle& boggle)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            cout << boggle.getLetter(i, j);
        }
        cout << endl;
    }
    return out;
}
