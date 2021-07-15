// Create two classes called Traveler and Pager without default constructors, but with constructors that take an argument of type string, which they simply copy to an internal string variable. For each class, write the correct copy-constructor and assignment operator. Now inherit a class BusinessTraveler from Traveler and give it a member object of type Pager. Write the correct default constructor, a constructor that takes a string argument, a copy-constructor, and an assignment operator.

#include <iostream>
using namespace std;

class Traveler
{
    string str;

public:
    Traveler(string s) : str(s) {}
    Traveler(const Traveler &t) : str(t.str) {}
    Traveler &operator=(const Traveler &t)
    {
        if (this != &t)
            str = t.str;
        return *this;
    }
    string getString() const
    {
        return str;
    }
};
class Pager
{
    string str;

public:
    Pager(string s) : str(s)
    {
    }
    Pager(const Pager &p) : str(p.str) {}
    Pager &operator=(const Pager &p)
    {
        if (this != &p)
            str = p.str;
        return *this;
    }
    string getString() const
    {
        return str;
    }
};
class BusinessTraveler : public Traveler
{
    Pager pager;

public:
    BusinessTraveler() : Traveler(""), pager("") {}
    BusinessTraveler(string t, string p) : Traveler(t), pager(p) {}
    BusinessTraveler(const BusinessTraveler &b) : Traveler(b), pager(b.pager) {}
    BusinessTraveler &operator=(const BusinessTraveler &b)
    {
        if (this != &b)
        {

            Traveler::operator=(b);
            pager = b.pager;
        }
        return *this;
    }
    friend ostream &operator<<(ostream &os, const BusinessTraveler &b)
    {
        return os << "{\"" << b.getString() << "\",\"" << b.pager.getString() << "\"}";
    }
};
int main()
{
    BusinessTraveler b1("BT1", "P1");
    cout << b1 << endl;
    BusinessTraveler b2("BT2", "P2");
    cout << b2 << endl;
    BusinessTraveler b3;
    cout << b3 << endl;
    BusinessTraveler b4(b1);
    cout << b4 << endl;
    b3 = b2;
    cout << b3 << endl;
}
