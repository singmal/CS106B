#include <iostream>
#include <string>

using namespace std;

string starString(int n);

int main()
{
    cout << starString(4);
    return 0;
}

string starString(int n)
{
    if (n < 0)
        throw "Invalid input.";
    else if (n == 0)
        return "*";
    else
    {
        string star = starString(n - 1);
        return star + star;
    }
}