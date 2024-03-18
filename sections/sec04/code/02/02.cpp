#include <iostream>
#include <vector>

using namespace std;

void mergeSort(vector<int>& v);

int main()
{
    vector<int> nums = {29, 17, 3, 94, 46, 8, -4, 12};
    mergeSort(nums);
    for (auto iter = nums.begin(); iter != nums.end(); iter++)
    {
        cout << *iter << " ";
    }
    cout << endl;
    return 0;
}

void mergeSort(vector<int>& v)
{
    int size = v.size();
    if (size <= 1)
        return;
    else
    {
        vector<int> lv;
        vector<int> rv;

        int partition = size / 2;

        for (int i = 0; i < partition; i++)
        {
            lv.push_back(v[i]);
        }
        for (int i = partition; i < size; i++)
        {
            rv.push_back(v[i]);
        }

        mergeSort(lv);
        mergeSort(rv);

        // 以下版本代码的问题：先跑完的一端数组会越界！
        // int i = 0, j = 0;
        // for (int id = 0; id < size; id++)
        // {
        //     if (lv[i] <= rv[j])
        //     {
        //         v[id] = lv[i++];
        //     }
        //     else
        //     {
        //         v[id] = rv[j++];
        //     }
        // }

        v.clear();
        int n1 = lv.size();
        int n2 = rv.size();
        int p1 = 0, p2 = 0;
        while (p1 < n1 && p2 < n2)
        {
            if (lv[p1] <= rv[p2])
            {
                v.push_back(lv[p1++]);
            }
            else
            {
                v.push_back(rv[p2++]);
            }
        }

        while (p1 < n1)
        {
            v.push_back(lv[p1++]);
        }

        while (p2 < n2)
        {
            v.push_back(rv[p2++]);
        }
    }
}