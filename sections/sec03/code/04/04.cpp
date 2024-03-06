#include <iostream>
#include <string>

using namespace std;

string longestCommonSubsequence(const string& str1, const string& str2);

int main()
{
   cout << longestCommonSubsequence("leslie", "wesley") << endl;
   cout << longestCommonSubsequence("chris", "anupama") << endl;
   cout << longestCommonSubsequence("she sells", "seashells") << endl;
   return 0;
}

string longestCommonSubsequence(const string& str1, const string& str2)
{
    if (str1 == "" || str2 == "")
        return "";
    else if (str1[0] == str2[0])
        return str1[0] + longestCommonSubsequence(str1.substr(1), str2.substr(1));
    else
    {
        string choice1 = longestCommonSubsequence(str1.substr(1), str2);
        string choice2 = longestCommonSubsequence(str1, str2.substr(1));
        if (choice1.length() > choice2.length())
            return choice1;
        else
            return choice2;
    }
}