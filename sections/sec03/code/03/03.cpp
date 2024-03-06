#include <iostream>
#include <vector>

using namespace std;

void printSquares(int sum, int cur, vector<int>& result);

int main()
{
   vector<int> result;
   printSquares(200, 1, result);
}

void printSquares(int sum, int cur, vector<int>& result)
{
    if (sum == 0)
    {
        int last = result[result.size() - 1];
        for (int num : result)
        {
            if (last != num)
                cout << num << "^2 + ";
            else
                cout << num << "^2" << endl;
        }
    }
    else
    {
        for (int i = cur; i * i <= sum; i++)
        {
            result.push_back(i);
            printSquares(sum - (i * i), i + 1, result);
            result.pop_back();
        }
    }
}