#include <iostream>

using namespace std;

class CPoint
{
    double x, y;

public:
    //构造函数
    CPoint(double x, double y)
    {
        this->x = x;
        this->y = y;
    }
    //复制构造函数
    CPoint(const CPoint &C)
    {
        this->x = C.x;
        this->y = C.y;
    }
    virtual double GetArea(){}
    virtual double GetVolume(){}
    void print()
    {
        cout << "Center:(" << x << "," << y << ")" << endl;
    }
};

class Circle : public CPoint
{
    double radius;

public:
    // 构造函数
    Circle(double radius, double x, double y) : CPoint(x, y)
    {
        this->radius = radius;
    }
    // 复制构造函数
    Circle(const Circle &C) : CPoint(C)
    {
        this->radius = C.radius;
    }
    double GetArea()
    {
        const double PI = 3.14159265;
        return PI * radius * radius;
    }
    double GetRadius()
    {
        return radius;
    }
    double GetVolume()
    {
        const double PI = 3.14159265;
        return 3 * PI * radius * radius * radius / 4;
    }
    void print()
    {
        cout << "radius=" << radius << endl;
    }
};

class Ccylinder : public Circle
{
    double height;

public:
    Ccylinder(double height, double radius, double x, double y) : Circle(radius, x, y)
    {
        this->height = height;
    }
    Ccylinder(const Ccylinder &C) : Circle(C)
    {
        this->height = C.height;
    }
    double GetArea()
    {
        const double PI = 3.14159265;
        return (2 * PI * GetRadius() * GetRadius() + 2 * PI * GetRadius() * height);
    }
    double GetVolume()
    {
        const double PI = 3.14159265;
        return PI * GetRadius() * GetRadius() * height;
    }
    double GetHeight()
    {
        return height;
    }
    void print()
    {
        const double PI = 3.14159265;
        cout << "height:" << GetHeight() << endl;
        cout << "BasalArea:" << PI * GetRadius() * GetRadius() << endl;
        cout << "SupfaceArea:" << GetArea() << endl;
        cout << "Volume:" << GetVolume() << endl;
    }
};

int main()
{
    double x, y, radius, height;
    cin >> x >> y >> radius >> height;
    CPoint CP(x, y);
    CP.print();
    Circle Cir(radius, x, y);
    Cir.print();
    Ccylinder Ccy(height, radius, x, y);
    Ccy.print();
}