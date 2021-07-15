#include <iostream>
using namespace std;

class A
{
    int x;
};

class Derived : public A
{
    float y;
};

void SizeOf(A a)
{
    cout << "SizeOf:" << sizeof(a) << endl;
}

int main()
{
    A a;
    Derived d;
    cout << "sizeof(a) = " << sizeof(a) << endl;
    cout << "sizeof(d) = " << sizeof(d) << endl;
    SizeOf(a);
    SizeOf(d);
}
// output :
// sizeof(a) = 4
// sizeof(d) = 8
// SizeOf:4
// SizeOf:4
// we can know that when using derived class, the sizeof(d) are based on the class A(which is stored by stack), but when using external function to call,
// the output are normally 4,which is just the size of the derived class.