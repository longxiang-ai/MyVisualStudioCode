
#include <iostream>
using namespace std;
class A
{
    static int k;
    int m;

public:
    A(int k = 111, int m = 222)
    {
        A::k = k;
        A::m = m;
    }
    static int GetK()
    {
        return k;
    }
    int GetM() const
    {
        return m;
    }
};
int m2 = 200;
int *F(int i)
{
    int m = 100;
    // static int m = 100;
    int n = 100;
    cout << m++ << endl;
    cout << n++ << endl;

    m += i;
    n += i;

    return &m;
}

int A::k = 99999;

int main()
{
    int *ip = F(3);
    cout << *ip << endl;
    cout << A::GetK() << endl;
    A a1(111, 333), a2(222, 444);
    cout << A::GetK() << endl;
    cout << sizeof(a1) << endl;
    cout << "----------" << endl;
    cout << a1.GetK() << endl;
    cout << a1.GetM() << endl;
    cout << "----------" << endl;
    cout << a2.GetK() << endl;
    cout << a2.GetM() << endl;
    cout << "----------" << endl;
    cout << A::GetK() << endl;
    // cout << A::GetM() << endl;  // (it's not permitted)
}