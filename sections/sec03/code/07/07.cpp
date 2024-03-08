#include <iostream>
#include <set>

using namespace std;

struct domino
{
    int first;
    int second;

    bool operator<(const domino& rhs) const
    {
        if (first != rhs.first)
            return first < rhs.first;
        else
            return second < rhs.second;
    }
};

bool chainExists(set<domino>& domes, int id1, int id2);

int main()
{

    set<domino> dominoes = {
        {1, 4},
        {2, 6},
        {4, 5},
        {1, 5},
        {3, 5}
    };

    cout << chainExists(dominoes, 6, 2) << endl;
    cout << chainExists(dominoes, 5, 5) << endl;
    cout << chainExists(dominoes, 1, 6) << endl;

}

bool chainExists(set<domino>& domes, int id1, int id2)
{
    if (id1 == id2)
        return true;
    else
    {
        for (auto iter = domes.begin(); iter != domes.end(); iter++)
        {
            domino cur = *iter;
            domes.erase(cur);
            if ((cur.first == id1 && chainExists(domes, cur.second, id2)) || 
                (cur.second == id1 && chainExists(domes, cur.first, id2)))
            {
                return true;
            }
            domes.insert(cur);
        }
        return false;
    }
}