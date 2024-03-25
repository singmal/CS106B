#include "lexicon.h"
#include <iostream>
#include <cctype>
#include "Boggle.h"
#include "console.h"
#include "bogglegui.h"

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

    // Task 2 & 3: human's turn
    cout << "It's your turn!" << endl;
    string input;
    Set<string> words;
    while (true)
    {
        cout << (*boardPtr);
        cout << endl;

        words = boardPtr->getHumanWordsFound();
        cout << "Your words (" << words.size() << "): " << words << endl;
        cout << "Your score: " << boardPtr->getScoreHuman() << endl;
        cout << "Type a word (or Enter to stop): ";
        getline(cin, input);
        for (auto it = input.begin(); it != input.end(); it++)
        {
            *it = toupper(*it);
        }
        if (input.empty())
        {
            cout << endl;
            break;
        }
        else
        {
            clearConsole();
            BoggleGUI::clearHighlighting();
            if (!boardPtr->checkWord(input))
                cout << "You must enter an unfound 4+ letter word from dicitonary." << endl;
            else
            {
                if (boardPtr->humanWordSearch(input))
                {
                    cout << "You found a new word! \"" << input << "\"" << endl;
                    BoggleGUI::recordWord(input, BoggleGUI::HUMAN);
                }
                else
                {
                    cout << "That word can't be formed on this board." << endl;
                }
            }
        }
    }

    // Task 4: computer's turn except for search
    cout << "It's my turn!" << endl;
    words = boardPtr->computerWordSearch();
    cout << "My words (" << words.size() << "): " << words << endl;
    for (string word: words)
    {
        BoggleGUI::recordWord(word, BoggleGUI::COMPUTER);
    }
    cout << "My score: " << boardPtr->getScoreComputer() << endl;

    if (boardPtr->getScoreComputer() > boardPtr->getScoreHuman())
        cout << "Ha ha ha, I destroyed you. Better luck next time, puny human!" << endl;
    else
        cout << "WOW, you defeated me! Congratulations!" << endl;
}
