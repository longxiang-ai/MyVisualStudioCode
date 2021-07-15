#include <iostream>
#include <cmath>
using namespace std;

/* 请在这里填写答案 */
class Circle
{
public:
    double r;
    void setR(double rin)
    {
        r = rin;
    }
    double getR()
    {
        return r;
    }
    double getArea()
    {
        return 3.1415926 * r * r;
    }
};
int main()
{
    Circle c;
    double r;
    cin >> (r);
    c.setR(r);
    cout << "Circle's r is " << c.getR() << endl;
    cout << "Circle's area is " << c.getArea() << endl;
    return 0;
}