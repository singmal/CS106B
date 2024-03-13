/*
 * File: grammarsolver.cpp
 * --------------------------
 * Name:
 * Section leader:
 * This file contains grammar generating code for CS106B.
 */

#include "grammarsolver.h"
#include "Map.h"
#include "strlib.h"
#include "random.h"

using namespace std;

void generMap(Map<string, Vector<string> >& map, istream& input);
string generRandomExp(string symbol, Map<string, Vector<string> >& map);

/**
 * Generates grammar for a given symbol a certain number of times given
 * a BNF input file.
 *
 * This will be called by grammarmain.cpp.
 *
 * @param input - Input stream of BNF file.
 * @param symbol - Symbol to generate
 * @param times - Number of times grammar is generated
 * @return Vector of strings of size times with random generations of symbol
 */
Vector<string> grammarGenerate(istream& input, string symbol, int times)
{
    if (symbol == "")
    {
        throw "Empty symbol to generate!";
    }
    else if (times <= 0)
    {
        return {};
    }
    else
    {
        Map<string, Vector<string> > map;
        generMap(map, input);
        Vector<string> result;
        for (int i = 0; i < times; i++)
        {
            result.add(generRandomExp(symbol, map));
        }
        return result;
    }
}

void generMap(Map<string, Vector<string> >& map, istream& input)
{
    string line;
    while (getline(input, line))
    {
        Vector<string> pairs = stringSplit(line, "::=");
        string key = pairs[0];
        if (map.containsKey(key))
        {
            throw "Two lines of same non-terminal!";
        }
        Vector<string> values = stringSplit(pairs[1], "|");
        map[key] = values;
    }
}

string generRandomExp(string symbol, Map<string, Vector<string> >& map)
{
    if (!map.containsKey(symbol))
    {
        return symbol;
    }
    else
    {
        Vector<string> candidates = map[symbol];
        int idx = randomInteger(0, candidates.size() - 1);
        string next_symbol = candidates[idx];
        Vector<string> split_space = stringSplit(next_symbol, " ");
        string result;
        int size = split_space.size();
        for (int i = 0; i < size; i++)
        {
            result += generRandomExp(split_space[i], map);
            if (i == size - 1)
            {
                break;
            }
            else
            {
                result += " ";
            }
        }
        return result;
    }
}
