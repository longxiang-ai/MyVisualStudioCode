#include <iostream>
using namespace std;

// 创建基类
class Base
{
public:
    virtual ~Base() {}
    // 基类中定义克隆的虚函数，返回一个新的基类地址
    virtual Base *clone() const
    {
        return new Base(*this);
    }
    virtual void f()
    {
        cout << "Base::f()\n";
    }
};
// 派生类以基类base为公有继承
class Derived : public Base
{
public:
    // 派生类中也定义同样的克隆虚函数
    virtual Derived *clone() const
    {
        return new Derived(*this);
    }
    virtual void f()
    {
        cout << "Derived::f()\n";
    }
};
// 调用派生类中的f函数，然后删除这个派生类
void func(Derived *d)
{
    d->f();
    delete d;
}

int main()
{
    Base a;
    a.f();
    Derived d;
    Base *d2 = d.clone();
    d2->f();
    delete d2;
    // 将派生类对象d的clone传入invoke函数中，观察结果
    func(d.clone());
}

// output:
// Base::f()
// Derived::f()
// Derived::f()
// 可以看出两次删除的结果调用的f均是派生类的输出函数f，
// 派生类中的clone函数返回的类型其实是derived*类型，而不是base类型，
// 所以在某些特别需要返回dirived* 类型的函数时(如本题中的func函数），这样的派生类中的f即是有用的
//