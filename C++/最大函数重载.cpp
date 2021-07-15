#include <iostream>
using namespace std;
// class Max
// {
// public:
int myMax(int a, int b)
{
    return (a > b ? a : b);
}

int myMax(int a, int b, int c)
{
    int max = a > b ? a : b;
    max = a > c ? a : c;
    return max;
}

double myMax(double a, double b)
{
    return a > b ? a : b;
}
// };
int main()
{
    cout << myMax(3, 4) << endl;
    cout << myMax(3, 4, 5) << endl;
    cout << myMax(4.3, 3.4) << endl;
}