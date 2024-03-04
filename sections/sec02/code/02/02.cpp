#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <map>

using namespace std;

int main()
{
    ifstream infile;
    infile.open("./buddies.txt");
    // map<int, string>中itr->first是整数键，itr->second是与该键相关联的字符串值
    map<string, set<string> > result;
    string p1, p2;
    while (infile >> p1 >> p2)
    {
        auto itr = result.find(p1);
        if (itr != result.end())
            result[p1].insert(p2);
        else
        {
            // map值为set时，可以直接这样加入键值对
            result[p1] = {p2};
        }
            
        itr = result.find(p2);
        if (itr != result.end())
            result[p2].insert(p1);
        else
        {
            result[p2] = {p1};
        }
    }

    cout << "{";
    for (auto itr1 = result.begin(); itr1 != result.end(); itr1++)
    {
        cout << itr1->first << ": {";
        for (auto itr2 = itr1->second.begin(); itr2 != itr1->second.end(); itr2++)
            cout << *itr2 << " ";
        cout << "}, ";
    }
    cout << "}" << endl;
}