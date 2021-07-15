#include <iostream>
#include <ctime>
using namespace std;

class Base
{
public:
    void nonvirt();
    virtual void virt();
};

void Base::nonvirt() {}
void Base::virt() {}

class Derived : public Base
{
};

double measure(Base *bp, void (Base::*f)())
{
    clock_t start = clock();
    for (int i = 0; i < 1e8L; ++i)
        (bp->*f)();
    clock_t stop = clock();
    return static_cast<double>(stop - start) / CLOCKS_PER_SEC;
}

int main()
{
    Derived d;
    cout << measure(&d, &Base::nonvirt) << endl;
    cout << measure(&d, &Base::virt) << endl;
}
// output：
// 0.168
// 0.196
// from the output, we can know that using virtual function to call is a little slower than using non virtual one.
