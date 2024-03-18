#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

int alignDNAStrands(const string& str1, const string& str2);
int alignDNAStrandsHelper(const string& str1, const string& str2, map<string, int>& cache);

int main()
{
    string str1 = "GATCGGCAT", str2 = "CAATGTGAATC";
    cout << alignDNAStrands(str1, str2);
    return 0;
}

int alignDNAStrands(const string& str1, const string& str2)
{
    map<string, int> cache;
    return alignDNAStrandsHelper(str1, str2, cache);
}

int alignDNAStrandsHelper(const string& str1, const string& str2, map<string, int>& cache)
{
    if (str1.empty())
        return -2 * str2.size();
    if (str2.empty())
        return -2 * str1.size();
    
    string key = str1 + ":" + str2;

    if (str1[0] == str2[0])
    {
        int score = alignDNAStrandsHelper(str1.substr(1), str2.substr(1), cache) + 1;
        cache[key] = score;
        return score;
    }
    else
    {
        int insert1 = alignDNAStrandsHelper(str1, str2.substr(1), cache) - 2;
        int insert2 = alignDNAStrandsHelper(str1.substr(1), str2, cache) - 2;
        int skip = alignDNAStrandsHelper(str1.substr(1), str2.substr(1), cache) - 1;
        int score = max(max(insert1, insert2), skip);
        cache[key] = score;
        return score;
    }
}