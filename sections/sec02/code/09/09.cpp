#include <iostream>
#include <string>

using namespace std;

void hanoi(int disks, int speg, int dpeg);

int main()
{
    hanoi(3, 1, 3);
    return 0;
}

void hanoi(int disks, int speg, int dpeg)
{
    int tpeg = 6 - speg - dpeg;
    if (disks == 1)
        cout << "move disk 1 from peg " << speg << " to peg " << dpeg << endl;
    else
    {
        hanoi(disks - 1, speg, tpeg);
        cout << "move disk " << disks << " from peg " << speg << " to peg " << dpeg << endl;
        hanoi(disks - 1, tpeg, dpeg);
    }
}