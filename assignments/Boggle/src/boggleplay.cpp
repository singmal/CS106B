#include "lexicon.h"
#include <iostream>
#include <cctype>
#inlcude "Boggle.h"

void playOneGame(Lexicon& dictionary)
{
    using std::cout;
    using std::cin;
    using std::endl;

    // Task1: generate board
    cout << "Do you want to generate a random board?";
    char ch;
    cin.get(ch);
    ch = toUpper(ch);
    while (cin.get() != '\n')
        continue;
    if (ch == 'Y')
        Boggle board = Boggle(dictionary);
    else
    {
        bool run = true;
        while (run)
        {
            cout << "Type the 16 letters to appear on the board: ";
            string textOnBoard;
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
        Boggle board = Boggle(dictionary, textOnBoard);
    }

    // Task 2: human's turn except for search
    cout << "It's your turn!" << endl;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            cout << board.getLetter(i, j);
        }
        cout << endl;
    }
    cout << endl;
}
