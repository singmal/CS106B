#include <iostream>
#include <vector>

using namespace std;

void insertSort(vector<int>& vec);

int main()
{
   vector<int> nums = {29, 17, 3, 94, 46, 8, -4, 12};
   insertSort(nums);
   return 0;
}

void insertSort(vector<int>& vec)
{
    int size = vec.size();
    if (size <= 1)
        return;
    else
    {
        for (int i = 1; i < size; i++)
        {
            int j = i;
            
            // 问题1：vec[j]多次调用，应该放在一个变量中
            // 问题2：不需要每比较一次就交换两个数据！找到当前想插入的值tmp应该在的位置再放进去，节省步骤
            // while (j >= 1 && vec[j - 1] > vec[j])
            // {
            //     int tmp = vec[j];
            //     vec[j] = vec[j - 1];
            //     vec[j - 1] = tmp;
            //     j--;
            // }

            // 改正版本
            int tmp = vec[j];
            while (j >= 1 && vec[j - 1] > tmp)
            {
                vec[j] = vec[j - 1];
                j--;
            }
            vec[j] = tmp;

            for (auto iter = vec.begin(); iter != vec.end(); iter++)
            {
                cout << *iter << " ";
            }
            cout << endl;
        }
    }
}