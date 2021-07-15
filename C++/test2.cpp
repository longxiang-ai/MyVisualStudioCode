#include <iostream>
using namespace std;

class A {
public:
    A() { cout << 1; }
} a;

int main()
{
    cout << 2;
    A a;

    return 0;
}