#include <iostream>
#include <new>
using namespace std;

int *Mynew(int size)
{
    int *p;
    if (size <= 10)
    {
        p = (int *)operator new(sizeof(size));
    }
    else
    {
        throw -1;
    }
    return p;
}
int main()
{
    int i = 1;
    try
    {
        while (i++)
        {
            cout << "i = " << i << endl;
            int *p = Mynew(i);
            free(p);
        }
        cout << i << endl;
    }
    catch (int)
    {
        cout << "run out of memory";
    }
}
// outputs are like this
// i = 2
// i = 3
// i = 4
// i = 5
// i = 6
// i = 7
// i = 8
// i = 9
// i = 10
// i = 11
// run out of memory