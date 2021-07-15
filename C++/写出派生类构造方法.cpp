#include <iostream>
using namespace std;
class People
{
private:
    string id;
    string name;

public:
    People(string id, string name)
    {
        this->id = id;
        this->name = name;
    }
    string getId()
    {
        return this->id;
    }
    string getName()
    {
        return name;
    }
};

class Student : public People
{想·想·
private:
    string sid;
    int score;

public:
    Student(string id, string name, string sid, int score)
        : People(id, name)
    {
        this->sid = sid;
        this->score = score;
    }

    /** 你提交的代码将被嵌在这里（替换此行） **/

    friend ostream &operator<<(ostream &o, Student &s);
};

ostream &operator<<(ostream &o, Student &s)
{
    o << "(Name:" << s.getName() << "; id:"
      << s.getId() << "; sid:" << s.sid
      << "; score:" << s.score << ")";
    return o;
}
int main()
{
    Student zs("370202X", "Zhang San", "1052102", 96);
    cout << zs << endl;
    return 0;
}