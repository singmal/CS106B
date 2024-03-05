#include <iostream>
#include <string>

using namespace std;

bool isSubsequence(string s1, string s2);

int main()
{
    cout << isSubsequence("computer", "core") << endl;
    cout << isSubsequence("computer", "cope") << endl;
    cout << isSubsequence("computer", "computer") << endl;

    return 0;
}

bool isSubsequence(string s1, string s2)
{
    if (s2 == "")
        return true;
    char cur = s2[0];

    for (int i = 0; i < s1.length(); i++)
    {
        if (s1[i] == cur)
        {
            string next_s1 = s1.substr(i + 1);
            string next_s2 = s2.substr(1);
            return isSubsequence(next_s1, next_s2);
        }
    }

    return false;
}

/*
答案的版本更好
bool isSubsequence(string &big, string &small)
{
    if (small == "")
    {
        return true;
    }
    else if (big == "")
    {
        return false;
    }
    else
    {
        if (big[0] == small[0])
        {
            return isSubsequence(big.substr(1), small.substr(1));
        }
        else
        {
            return isSubsequence(big.substr(1), small);
        }
    }
}
*/