#include <iostream>
#include <string>

using namespace std;

int editDistance(const string& s1, const string& s2);

int main()
{
    string s1 = "football";
    string s2 = "cookies";
    cout << editDistance(s1, s2) << endl;
    return 0;
}

// 本题递归必须用一定的启发式，否则考虑所有情况计算量太大！
int editDistance(const string& s1, const string& s2)
{
    if (s2 == "")
        return s1.length();
    else if (s1 == "")
        return s2.length();
    else
    {
        // 当第一个字母不同，应对方法全部囊括；当第一个字母相同，应对方法也全部囊括！
        // 为什么这里不需要设置limit上限步数，而CS61A中需要？因为这里每一次递归调用都对现有问题进行了简化，向着基本情况移动了一步，因此不会无限递归！
        int add = 1 + editDistance(s1, s2.substr(1));
        int del = 1 + editDistance(s1.substr(1), s2);
        int sub = editDistance(s1.substr(1), s2.substr(1));
        if (s1[0] != s2[0])
            sub += 1;
        return min(add, min(del, sub));
    }
}