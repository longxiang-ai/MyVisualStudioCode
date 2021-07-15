#include <iostream>
using namespace std;

class One
{
private:
    int x;

public:
    // 构造函数，带初始参数
    One(int x)
    {
        this->x = x;
    }
    // 构造函数，拷贝
    One(const One &i2)
    {
        x = i2.x;
        cout << "One::One(const One&)\n";
    }
    // 返回参数值
    int getX() const
    {
        return x;
    }
};

class Two
{
    One m;
    int n;

public:
    Two(int x, int newn) : m(x), n(newn) {}
    void print()
    {
        cout << '(' << m.getX() << ',' << n << ")\n";
    }
};

int main()
{
    Two o1(1, 2);
    o1.print();
    Two o2(o1);
    o2.print();
}
// 从输出很容易看出，Two的拷贝函数中自动调用了One中的拷贝函数
// output:
// (1,2)
// One::One(const One&)
// (1,2)
