#include <iostream>
#include "Rational.h"
using namespace std;

// Rational 类的实现

Rational::Rational()
{
    denominator = 1;
    numerator = 0;
}
Rational::Rational(int nume, int deno)
{
    denominator = deno;
    numerator = nume;
}
Rational::Rational(const Rational &r)
{
    this->numerator = r.numerator;
    this->denominator = r.denominator;
}

Rational::~Rational()
{
}

int Rational::GetGcd(int m, int n)
{
    int temp;
    while (n)
    {
        temp = n;
        n = m % n;
        m = temp;
    }
    return m;
}

void Rational::Simplify()
{
    int gcd = GetGcd(numerator, denominator);
    numerator /= gcd;
    denominator /= gcd;
}

int Rational::GetNumerator()
{
    return numerator;
}
int Rational::GetDenominator()
{
    return denominator;
}

Rational Rational::add(const Rational &r1, const Rational &r2) const
{
    int deno = r1.denominator * r2.denominator;
    int nume = r1.numerator * r2.denominator + r2.numerator * r1.denominator;
    Rational r(nume, deno);
    r.Simplify();
    return r;
}
Rational Rational::sub(const Rational &r1, const Rational &r2) const
{
    int deno = r1.denominator * r2.denominator;
    int nume = r1.numerator * r2.denominator - r2.numerator * r1.denominator;
    Rational r(nume, deno);
    r.Simplify();
    return r;
}
Rational Rational::multiply(const Rational &r1, const Rational &r2) const
{
    int deno = r1.denominator * r2.denominator;
    int nume = r1.numerator * r2.numerator;
    Rational r(nume, deno);
    r.Simplify();
    return r;
}
int Rational::CompareTo(const Rational &r1, const Rational &r2) const
{
    double m = r1.ToDouble();
    double n = r2.ToDouble();
    if (m < n)
    {
        return -1;
    }
    else if (m == n)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

double Rational::ToDouble() const
{
    return double(numerator) / double(denominator);
}

bool Rational::operator<(const Rational &r2) const
{
    if (CompareTo(*this, r2) < 0)
    {
        return true;
    }
    else
        return false;
}
bool Rational::operator>(const Rational &r2) const
{
    if (CompareTo(*this, r2) > 0)
    {
        return true;
    }
    else
        return false;
}
bool Rational::operator<=(const Rational &r2) const
{
    if (CompareTo(*this, r2) <= 0)
    {
        return true;
    }
    else
        return false;
}
bool Rational::operator>=(const Rational &r2) const
{
    if (CompareTo(*this, r2) >= 0)
    {
        return true;
    }
    else
        return false;
}
bool Rational::operator==(const Rational &r2) const
{
    if (this->numerator == r2.numerator && this->denominator == r2.denominator)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int &Rational::operator[](int index)
{
    if (index == 0)
    {
        return numerator;
    }
    else
    {
        return denominator;
    }
}

Rational &Rational::operator+=(const Rational &r2)
{
    *this = add(*this, r2);
    return *this;
}

Rational Rational::operator-()
{
    return Rational(-numerator, denominator);
}

Rational &Rational::operator++()
{
    numerator += abs(denominator);
    return *this;
}

Rational Rational::operator++(int dummy)
{
    Rational temp(numerator, denominator);
    numerator += abs(denominator);
    return temp;
}

Rational::operator double()
{
    return ToDouble();
}
Rational::Rational(int nume)
{
    numerator = nume;
    denominator = 1;
}
const Rational &Rational::operator=(const Rational &r)
{
    return Rational(numerator, denominator);
}

int main()
{
    cout << "Hello world" << endl;
    Rational r1(3, 5);
    Rational r2(4, 5);
    cout << (r1 < r2) << endl;
    cout << (r1++).ToDouble() << endl;
    cout << r1.ToDouble() << endl;
    cout << (++r1).ToDouble() << endl;

    double a = double(r1);
    cout << a << endl;
}