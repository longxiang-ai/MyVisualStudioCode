#include <iostream>
#include <typeinfo.h>
using namespace std;

class A
{
public:
    virtual ~A() {}
};

class B : public A
{
};

int main()
{
    A *ap = new B;
    cout << typeid(*ap).name() << endl;

    B *bp;
    // 动态的类型转换
    bp = dynamic_cast<B *>(ap);
    // 静态的类型转换
    bp = static_cast<B *>(ap);
    // 毫无关系两个类之间类型转换（甚至不需要B继承A)
    bp = reinterpret_cast<B *>(ap);

    const A *cp = ap;
    // 强制转成const类型
    A *ap2 = const_cast<A *>(cp);
    return 0;
}
// output:
// when A is not polymorphic class
// 1A
// when A is polymorphic class
// 1B
