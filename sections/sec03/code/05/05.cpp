#include <iostream>
#include <vector>

using namespace std;

void waysToClimb(int stairs);
void waysToClimbHelper(int stairs, vector<int>& result);

int main()
{
   waysToClimb(4);
}

void waysToClimb(int stairs)
{
    vector<int> result;
    waysToClimbHelper(stairs, result);
}

void waysToClimbHelper(int stairs, vector<int>& result)
{
    if (stairs < 0)
        return;
    else if (stairs == 0)
    {
        for (int i : result)
            cout << i << " ";
        cout << endl;
    }
    else
    {
        result.push_back(1);
        waysToClimbHelper(stairs - 1, result);
        result.pop_back();
        result.push_back(2);
        waysToClimbHelper(stairs - 2, result);
        result.pop_back();
    }
}