#include <iostream>
#include <string>

using namespace std;

string reverse(const string str);

int main()
{
    string input;
    cin >> input;
    cout << reverse(input);
    return 0;
}

// 答案写的更好！！！逆向思维总是没有！！！
string reverse(const string str)
{
    int l = str.length();
    if (l < 2)
        return str;
    else
        // 反转不需要每次头尾同时去掉一个元素！
        return str[l - 1] + reverse(str.substr(1, l - 2)) + str[0];
}