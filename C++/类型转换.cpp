#include <iostream>
#include <math.h>

using namespace std;

class Complex
{
private:
    double m_r;
    double m_i;

public:
    Complex(double r = 0.0, double i = 0.0)
    {
        m_r = r;
        m_i = i;
    }
    // Complex operator+(const Complex &c) const
    // {
    //     return Complex(m_r + c.m_r, m_i + c.m_i);
    // }
    double operator[](int i) const
    {
        return ((i == 0) ? m_r : m_i);
    }
    operator double const()
    {
        return sqrt(m_r * m_r + m_i * m_i);
    }
    friend Complex operator+(const Complex &c1, const Complex &c2);
    friend ostream &operator<<(ostream &, const Complex &);
};
ostream &operator<<(ostream &out, const Complex &c)
{
    return out << c.m_r << "+" << c.m_i << "i";
}

Complex operator+(const Complex &c1, const Complex &c2)
{
    return Complex(c1[0] + c2[0], c1[1] + c2[1]);
}
int main()
{
    const Complex c1(3.0, 4.0), c2(2.0, 5.0);
    Complex c;

    c = c1 + c2;
    c = 4.0 + c1;

    cout << c << endl;
    cout << c[0] << endl;
    cout << c[1] << endl;
    cout << c1 << endl;
    // cout << double (c1) << endl; // c1 is a const, so it can't be transfromed into double
    cout << double(c) << endl;
}