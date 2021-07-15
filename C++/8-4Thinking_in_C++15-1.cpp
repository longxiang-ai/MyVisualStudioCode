// Modify Exercise 8-4 so draw( ) is a pure virtual function. Try creating an object of type Shape. Try to call the pure virtual function inside the constructor and see what happens. Leaving it as a pure virtual, give draw( ) a definition.
#include <iostream>
#include <math.h>
using namespace std;
// ³éÏóÀà
class Shape
{
public:
    virtual void draw() = 0;
    // virtual string getName() = 0;
};

class Circle : public Shape
{
    double r;
    string name;

public:
    Circle()
    {
        this->r = 1.0;
        this->name = "Circle";
    }
    const double PI = 3.14159;
    void draw()
    {
        cout << name << ":" << PI * r * r << endl;
    }
};

class Square : public Shape
{
    double a;
    string name;

public:
    Square()
    {
        a = 4.0;
        this->name = "Square";
    }
    void draw()
    {
        cout << name << ":" << a * a << endl;
    }
};

class Triangle : public Shape
{
    double a, b, c;
    string name;

public:
    Triangle()
    {
        a = 3;
        b = 4;
        c = 5;
        this->name = "Triangle";
    }
    void draw()
    {
        double p = (a + b + c) / 2.0;
        double s = sqrt(p * (p - a) * (p - b) * (p - c));
        cout << name << ":" << s << endl;
    }
};

int main()
{
    // Shape s;
    // s.draw();
    // Shape a[3];
    // a[0].draw();
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
// When not commenting out the first four lines in the main function, the compiler will report errors which prohibit to establish a abstract class
// When they are commented out, outputs are like this:
// Circle:3.14159
// Square:16
// Triangle:6
// Circle:3.14159
// Square:16
// Triangle:6
