#include <iostream>
#include <string>
#include <cstring>

using namespace std;

class Str
{
    char *m_s;
    int m_size;

public:
    Str(char *s)
    {
        m_size = strlen(s);
        m_s = new char[m_size + 1];
        strcpy(m_s, s);
    }
    ~Str()
    {
        delete[] m_s;
    }
    char *operator++()
    {
        return ++m_s;
    }
    char *operator++(int)
    {
        return m_s++;
    }
    char operator[](int i) const
    {
        return m_s[i];
    }
    char &operator[](int i)
    {
        return m_s[i];
    }
    void Print() const
    {
        cout << m_s << endl;
    }
    friend ostream &operator<<(ostream &out, const Str &s);
};

ostream &operator<<(ostream &out, const Str &s)
{
    return out << s.m_s << endl;
}

int main()
{
    Str *ps = new Str("Hi");
    const Str s2("Hello");
    s2.Print();
    cout << s2[1] << endl;
    (*ps)[0] = 'h';
    ps->Print();
    delete ps;
}