#include "lexicon.h"
#include <iostream>
#include <cctype>
#include "Boggle.h"
#include "set.h"

void playOneGame(Lexicon& dictionary)
{
    using std::cout;
    using std::cin;
    using std::endl;

    // Task1: generate board
    cout << "Do you want to generate a random board?";
    char ch;
    cin.get(ch);
    ch = toupper(ch);
    while (cin.get() != '\n')
        continue;
    Boggle* boardPtr;
    if (ch == 'Y')
        boardPtr = new Boggle(dictionary);
    else
    {
        bool run = true;
        string textOnBoard;
        while (run)
        {
            cout << "Type the 16 letters to appear on the board: ";
            getline(cin, textOnBoard);
            int size = textOnBoard.size();
            run = false;
            if (size != 16)
            {
                run = true;
            }
            for (int i = 0; i < size && !run; i++)
            {
                if (!isalpha(textOnBoard[i]))
                {
                    run = true;
                    break;
                }
            }
            if (run)
            {
                cout << "That is not a valid 16-letter board string. Try again." << endl;
            }
        }
        boardPtr = new Boggle(dictionary, textOnBoard);
    }

    // Task 2: human's turn except for search
    cout << "It's your turn!" << endl;
    string input;
    Set<string> words;
    int score = 0;
    while (true)
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                cout << boardPtr->getLetter(i, j);
            }
            cout << endl;
        }
        cout << endl;

        cout << "Your words (" << words.size() << "): " << words;
        cout << "Your score: " << score << endl;
        cout << "Type a word (or Enter to stop): ";
        getline(cin, input);
        if (words.contains(input) || input.size() < 4 || !dictionary.contains(input))
            cout << "You must enter an unfound 4+ letter word from dicitonary." << endl;
        else
        {
            for (auto it = input.begin(); it != input.end(); it++)
            {
                *it = tolower(*it);
            }
            cout << "You found a new word! \"" << input << "\"" << endl;
            words.add(input);
            score += (input.size() - 3);
        }
    }
}
