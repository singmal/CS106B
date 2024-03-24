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
        for (int i = 0; i < board.numRows(); i++)
        {
            for (int j = 0; j < board.numCols(); j++)
            {
                boardText = shuffle(CUBES[board.numCols() * i + j]);
                board[i][j] = boardText[0];
            }
        }
    }
    else
    {
        for (int i = 0; i < board.numRows(); i++)
        {
            for (int j = 0; j < board.numCols(); j++)
            {
                char ch = boardText[board.numCols() * i + j];
                board[i][j] = toupper(ch);
            }
        }
    }
}

char Boggle::getLetter(int row, int col)
{
    if (!board.inBounds(row, col))
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
        return true;
    }
}

bool Boggle::humanWordSearch(string word)
{
    for (int i = 0; i < board.numRows(); i++)
    {
        for (int j = 0; j < board.numCols(); j++)
        {
            Grid<char> mark(board.numRows(), board.numCols());
            mark.fill('o');
            if (humanWordSearchHelper(word, i, j, 0, mark))
                return true;
        }
    }
    return false;
}

bool Boggle::humanWordSearchHelper(string word, int i, int j, int idx, Grid<char> mark)
{
    int size = word.size();
    if (idx == size)
    {
        wordsFound.add(word);
        humanScore += (size - 3);
        return true;
    }
    string substr = word.substr(0, idx + 1);
    if (board.inBounds(i, j) && word[idx] == board[i][j] && !mark[i][j]!='x' && dict.containsPrefix(substr))
    {
        mark[i][j] = 'x';
        return humanWordSearchHelper(word, i - 1, j - 1, idx + 1, mark) ||
                    humanWordSearchHelper(word, i - 1, j, idx + 1, mark) ||
                    humanWordSearchHelper(word, i - 1, j + 1, idx + 1, mark) ||
                    humanWordSearchHelper(word, i, j - 1, idx + 1, mark) ||
                    humanWordSearchHelper(word, i, j + 1, idx + 1, mark) ||
                    humanWordSearchHelper(word, i + 1, j - 1, idx + 1, mark)||
                    humanWordSearchHelper(word, i + 1, j, idx + 1, mark)||
                    humanWordSearchHelper(word, i + 1, j + 1, idx + 1, mark);
    }
    else
        return false;

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
    for (int i = 0; i < boggle.board.numRows(); i++)
    {
        for (int j = 0; j < boggle.board.numCols(); j++)
        {
            out << boggle.getLetter(i, j);
        }
        out << endl;
    }
    return out;
}
