#include <iostream>
#include <iomanip>
using namespace std;

class TDVector
{
private:
    double x;
    double y;

public:
    TDVector()
    {
        x = y = 0;
    }
    TDVector(double xin, double yin)
    {
        x = xin;
        y = yin;
    }
    double getX()
    {
        return x;
    }
    double getY()
    {
        return y;
    }
    void setX(double xin)
    {
        x = xin;
    }
    void setY(double yin)
    {
        y = yin;
    }
    TDVector operator+(TDVector &a)
    {
        TDVector b;
        b.x = this->x + a.x;
        b.y = this->y + a.y;
        return b;
    }
};
// TDVector operator+(const TDVector &, const TDVector &);
int main()
{
    TDVector a;
    double x, y;
    cin >> x >> y;
    TDVector b(x, y);
    cin >> x >> y;
    TDVector c;
    c.setX(x);
    c.setY(y);
    TDVector d;
    d = a + b + c;
    cout << fixed << setprecision(2) << d.getX() << ' ' << d.getY();
    return 0;
}