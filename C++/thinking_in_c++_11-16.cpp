#include <iostream>
using namespace std;

class First_class
{
private:
    int number;

public:
    // 构造函数
    First_class(int n)
    {
        cout << "First_class::First_class(" << n << ")\n";
        this->number = number;
    }
    First_class(const First_class &t)
    {
        cout << "First_class::First_class(const First_class&)\n";
        number = t.number;
    }
    // 成员函数，获得参数
    int getN() const
    {
        return number;
    }
};

void func(First_class t)
{
    cout << "func(" << t.getN() << ")\n";
}

First_class func2()
{
    First_class t(2);
    return t;
}

First_class func3(int n)
{
    return n;
}

int main()
{
    First_class t1 = 1;
    func(t1);
    First_class t2 = func2();
    First_class t3 = func3(3);
}

// outputs are like these:
// First_class::First_class(1)
// First_class::First_class(const First_class&)
// func(16)
// First_class::First_class(2)
// First_class::First_class(3)