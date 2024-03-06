#include <iostream>
#include <vector>

using namespace std;

bool partitionable(const vector<int>& vec);
bool partitionableHelper(const vector<int>& vec, int sum1, int sum2);

int main()
{
   vector<int> nums = {1, 4, 5, 6};
   cout << partitionable(nums) << endl;
   return 0;
}

bool partitionable(const vector<int>& vec)
{
    return partitionableHelper(vec, 0, 0);
}

bool partitionableHelper(const vector<int>& vec, int sum1, int sum2)
{
    if (vec.empty())
        return sum1 == sum2;
    else
    {
        vector<int> vec_new = vec;
        int adder = vec_new[0];
        vec_new.erase(vec_new.begin());
        return partitionableHelper(vec_new, sum1 + adder, sum2) ||
                partitionableHelper(vec_new, sum1, sum2 + adder);
    }
}