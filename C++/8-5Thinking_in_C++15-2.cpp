// Create a simple ¡°shape¡± hierarchy: a base class called Shape and derived classes called Circle,** Square**, and Triangle. In the base class, make a virtual function called draw( ), and override this in the derived classes. Make an array of pointers to Shape objects that you create on the heap (and thus perform upcasting of the pointers), and call draw( ) through the base-class pointers, to verify the behavior of the virtual function. If your debugger supports it, single-step through the code.

#include <iostream>
using namespace std;

class Shape
{

public:
    Shape()
    {
    }
    virtual void draw()
    {
        cout << "Shape" << endl;
    }
};
class Circle : public Shape
{
    double r;

public:
    Circle()
    {
        this->r = 1.0;
    }
    const double PI = 3.14159;
    void draw()
    {
        cout << PI * r * r << endl;
    }
};
class Square : public Shape
{
    double a;

public:
    Square()
    {
        a = 4.0;
    }
    void draw()
    {
        cout << a * a << endl;
    }
};

class Triangle : public Shape
{
    double a, b, c;

public:
    Triangle()
    {
        a = 3;
        b = 4;
        c = 5;
    }
    void draw()
    {
        cout << a * b * c << endl;
    }
};

int main()
{
    Shape s;
    s.draw();
    Shape a[3];
    a[0].draw();

    Circle c;
    c.draw();
    Square squ;
    squ.draw();
    Triangle tri;
    tri.draw();
    Shape *pt[3] = {&c, &squ, &tri};
    for (int i = 0; i < 3; i++)
    {
        pt[i]->draw();
    }
}
// outputs are like this
// Shape
// Shape
// 3.14159
// 16
// 60
// 3.14159
// 16
// 60