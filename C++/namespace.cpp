// namespace
#include <iostream>
using namespace std;
int m;
namespace A
{
    int m;
    namespace B
    {
        int m;
        int n;
        void F()
        {
            m = 3;
            n = 4;
        }
    }
    void F()
    {
        B::m += 7;
        m = 23;
    }
}

namespace B
{
    int m;
}

int main()
{
    int m;

    m = 8;
    A::m = 9;
    B::m = 10;
    A::B::m = 15;
    B::m = 111;

    cout << m << endl;
    cout << B::m << endl;

    A::B::F();
    cout << B::m << endl;
    using namespace A;
    F();
    cout << A::B::m << endl;
    cout << ::m << endl;
}