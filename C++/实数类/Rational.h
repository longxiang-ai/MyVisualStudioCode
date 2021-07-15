#ifndef RATIONAL_H
#define RATIONAL_H
#include <iostream>
class Rational
{
public:
    Rational();
    Rational(int nume, int deno);
    Rational(const Rational &r);
    ~Rational();
    int GetNumerator();
    int GetDenominator();
    int DoubleValue();
    Rational add(const Rational &r1, const Rational &r2) const;
    Rational sub(const Rational &r1, const Rational &r2) const;
    Rational multiply(const Rational &r1, const Rational &r2) const;
    int CompareTo(const Rational &r1, const Rational &r2) const;
    double ToDouble() const;

    // 运算符重载
    bool operator<(const Rational &r2) const;
    bool operator>(const Rational &r2) const;
    bool operator<=(const Rational &r2) const;
    bool operator>=(const Rational &r2) const;
    bool operator==(const Rational &r2) const;
    int &operator[](int index);
    Rational &operator+=(const Rational &r2);
    Rational operator-();
    Rational &operator++();
    Rational operator++(int dummy);

    // friend ostream &operator<<(ostream &out, const Rational &r);
    operator double();
    const Rational& operator=(const Rational &r);
    Rational(int nume);

private:
    int numerator;
    int denominator;
    int GetGcd(int m, int n);
    void Simplify();
};

// ostream &operator<<(ostream &out, const Rational &r)
// {
//     out << r.numerator << "/" << r.denominator;
//     return out;
// }

#endif