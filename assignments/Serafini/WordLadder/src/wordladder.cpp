// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>
#include "console.h"
#include "set.h"
#include "stack.h"
#include "queue.h"
#include "lexicon.h"

using namespace std;

void WelcomeInfo();
void LoadDict(Lexicon& dict);
void InputWord(int n, string& word);
void FindLadder(Lexicon& dict, string& word1, string& word2);
void PrintWordsFound(Stack<string>& words);

int main()
{
    WelcomeInfo();

    Lexicon dict;
    LoadDict(dict);

    // 有什么避免两次复制粘贴的代码重用好办法？
    string word_start, word_end;
    InputWord(1, word_start);
    if (word_start.length() == 0)
    {
        cout << "Have a nice day.";
        return 0;
    }
    InputWord(2, word_end);
    if (word_end.length() == 0)
    {
        cout << "Have a nice day.";
        return 0;
    }

    FindLadder(dict, word_start, word_end);

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
    getline(cin, filename);

    infile.open(filename);
    string word;
    while(getline(infile, word))
    {
        dict.add(word);
    }

    cout << endl;
}

void InputWord(int n, string& word)
{
    cout << "Word #" << to_string(n) << " (or Enter to quit): ";
    getline(cin, word);
    transform(word.begin(), word.end(), word.begin(), tolower);
}

void FindLadder(Lexicon& dict, string& word1, string& word2)
{
    Queue<Stack<string>> frontier;
    Set<string> explored_set;
    Stack<string> init;
    init.push(word1);
    explored_set.add(word1);
    if (word1 == word2)
    {
        PrintWordsFound(init);
        return;
    }
    frontier.enqueue(init);

    while (!frontier.isEmpty())
    {
        Stack<string> ladder = frontier.dequeue();
        string word = ladder.peek();
        for (int i = 0; i < word.length(); i++)
        {
            char old_letter = word[i];
            for (int j = 0; j < 24; j++)
            {
                char new_letter = 'a' + j;
                word[i] = new_letter;

                if (dict.contains(new_letter) && old_letter != new_letter && !explored_set.contains(word))
                {
                    ladder.push(word);
                    frontier.enqueue(ladder);
                    explored_set.add(word);

                    if (word == word2)
                    {
                        PrintWordsFound(ladder);
                        return;
                    }
                }
            }
            word[i] = old_letter;
        }
    }
}

void PrintWordsFound(Stack<string>& words)
{
    while (!words.isEmpty())
    {
        cout << words.pop() << " ";
    }
    cout << endl;
}
