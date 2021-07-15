#include <iostream>
#include <cassert>
#include <cstddef>
using namespace std;

template <typename T>
T Fib(const T &n)
{
    const size_t sz = 100;
    static T fib[sz];

    static size_t nFilled = 2;
    fib[0] = fib[1] = 1;
    size_t int_n = size_t(n);
    assert(n < sz);

    while (int_n >= nFilled)
    {
        fib[nFilled] = fib[nFilled - 1] + fib[nFilled - 2];
        nFilled++;
    }
    return fib[int_n];
}

int main()
{
    for (double x = 8.0; x >= 0.0; x--)
    {
        cout << "Fib(" << x << ")=" << Fib(x) << endl;
    }
    cout << endl;
    for (int i = 8; i >= 0; i--)
    {
        cout << "Fib(" << i << ")=" << Fib(i) << endl;
    }
}
// output:
// Fib(8)=34
// Fib(7)=21
// Fib(6)=13
// Fib(5)=8 
// Fib(4)=5 
// Fib(3)=3 
// Fib(2)=2 
// Fib(1)=1 
// Fib(0)=1

// Fib(8)=34
// Fib(7)=21
// Fib(6)=13
// Fib(5)=8
// Fib(4)=5
// Fib(3)=3
// Fib(2)=2
// Fib(1)=1
// Fib(0)=1