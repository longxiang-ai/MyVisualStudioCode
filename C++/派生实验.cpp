#include <iostream>
using namespace std;
class A
{

public:
    // int x = 0, y = 0;

    virtual int add(int x, int y)
    {
        return x + y;
    }
};

class D : public A
{
public:
    // int x = 1, y = 1, z = 1;
    int add(int x, int y, int z)
    {
        return (x + y + z);
    }
};

int main()
{
    class A a;
    cout << a.add(1, 2) << endl;
    class D d;
    cout << d.add(1, 2, 3) << endl;
    cout << d.add(1, 3) << endl;
}
// #include <iostream>
// using namespace std;
// class A
// {
// public:
//     A(int i) { x = i; }
//     void dispa()
//     {
//         cout << x << ',';
//     }

// private:
//     int x;
// };
// class B : public A
// {
// public:
//     B(int i) : A(i + 10)
//     {
//         x = i;
//     }
//     void dispb()
//     {
//         dispa();
//         cout << x << endl;
//     }

// private:
//     int x;
// };
// int main()
// {
//     B b(2);
//     b.dispb();
//     return 0;
// }