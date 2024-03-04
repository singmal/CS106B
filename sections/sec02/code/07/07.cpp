#include <iostream>
#include <stack>

using namespace std;

void stutterStack(stack<int>& s);

int main()
{
    stack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);
    stutterStack(s);
    while (!s.empty())
    {
        int tmp = s.top();
        s.pop();
        cout << tmp << endl;
    }
}

void stutterStack(stack<int>& s)
{
    if (s.empty())
        return;
    int next = s.top();
    s.pop();
    stutterStack(s);
    s.push(next);
    s.push(next);
}