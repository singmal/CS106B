#include <iostream>
#include <vector>
#include <set>

using namespace std;

int main()
{
    vector<int> origin = {1, 3, 1, 4, 3, 7, -2, 0, 7, -2, -2, 1};
    // C++中系统能根据元素的值自动对set进行排序
    set<int> one, two, more;
    for (int i = 0; i < origin.size(); i++)
    {
        int value = origin[i];
        auto itr1 = more.find(value);
        if (itr1 != more.end())
        {
            continue;
        }

        auto itr2 = two.find(value);
        if (itr2 != two.end())
        {
            two.erase(value);
            more.insert(value);
            continue;
        }

        auto itr3 = one.find(value);
        if (itr3 != one.end())
        {
            one.erase(value);
            two.insert(value);
            continue;
        }

        one.insert(value);
    }

    for (auto itr = two.begin(); itr != two.end(); itr++)
    {
        cout << *itr << endl;
    }
    return 0;
}