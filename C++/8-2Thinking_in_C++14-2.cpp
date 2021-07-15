// Create two classes, A and B, with default constructors that announce themselves. Inherit a new class called C from A, and create a member object of B in C, but do not create a constructor for C. Create an object of class C and observe the results.

#include <iostream>
using namespace std;

class A
{
public:
    double num;
    A()
    {
        this->num = 100;
        cout << "Constructing A:" << num << endl;
    }

    void ShowInforA()
    {
        cout << num << endl;
    }
};
class B
{
public:
    string name;
    B()
    {
        this->name = "zhangsan";
        cout << "Constructing B:" << name << endl;
    }

    void ShowInforB()
    {
        cout << name << endl;
    }
};

class C : public A
{
public:
    B b;
};

int main()
{

    A a;
    a.ShowInforA();
    cout << "--------------" << endl;
    C c;
    c.ShowInforA();
    cout << "--------------" << endl;
    c.b.ShowInforB();
}

// outputs are like this:
// Constructing A:100
// 100
// --------------
// Constructing A:100
// Constructing B:zhangsan
// 100
// --------------
// zhangsan