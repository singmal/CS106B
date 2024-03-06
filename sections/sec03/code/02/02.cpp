#include <iostream>
#include <vector>

using namespace std;

void makeChange(int target, vector<int>& coins);
void makeChangeHelper(int target, vector<int>& coins, vector<int>& usage);

int main()
{
    vector<int> coins = {1, 5, 10};
    makeChange(15, coins);
}

void makeChange(int target, vector<int>& coins)
{
    vector<int> usage;
    makeChangeHelper(target, coins, usage);
}

void makeChangeHelper(int target, vector<int>& coins, vector<int>& usage)
{
    if (coins.empty())
    {
        if (target == 0)
        {
            for (int i : usage)
                cout << i << " ";
            cout << endl;
        } 
    }
    // 实践证明有if的地方最好在if对立面加上else，比如这里不加else前面if容易忘记return，导致执行完if又去执行后面的代码！
    // if逻辑要注意！前面if条件如果给if (coins.empty() && target == 0)，那么一旦coins为空而target为负数，也会跑到下面的代码中！
    else
    {
        int coin = coins[0];
        coins.erase(coins.begin());
        for (int i = 0; i <= (target / coin); i++)
        {
            usage.push_back(i);
            makeChangeHelper(target - (i * coin), coins, usage);
            usage.pop_back();
        }
        coins.insert(coins.begin(), coin);
    }
}