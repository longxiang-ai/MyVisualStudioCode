// 设计一个学校在册人员类（Person）。数据成员包括：
//  身份证号（IdPerson）
//  姓名（Name）
//  性别（Sex）
//  生日（Birthday）
// 成员函数包括人员信息的录入和显示，还包括构造函数与拷贝构造函数。此外，设计一个合适的初始值。
#include <iostream>
using namespace std;
class Person
{
    string IdPerson;
    string Name;
    string Sex;
    string Birthday;

public:
    // 构造函数
    Person()
    {
        IdPerson = "110000190001010000";
        Name = "zhangsan";
        Sex = "male";
        Birthday = "19000101";
    }
    // 拷贝函数
    Person(const Person &person)
    {
        this->IdPerson = person.IdPerson;
        this->Name = person.Name;
        this->Sex = person.Sex;
        this->Birthday = person.Birthday;
    }
    void setBirthday(string date)
    {
        this->Birthday = date;
    }
    void setIdPerson(string dataIn)
    {
        this->IdPerson = dataIn;
    }
    void setName(string dataIn)
    {
        this->Name = dataIn;
    }
    void setSex(string dataIn)
    {
        this->Sex = dataIn;
    }

    void showInfo()
    {
        cout << "IdPerson : " << IdPerson << "  Name : " << Name << "  Sex : " << Sex << "  Birthday : " << Birthday << endl;
    }
};
int main()
{
    Person a;
    a.showInfo();
    Person b(a);
    b.showInfo();
    b.setBirthday("19210701");
    b.setIdPerson("10101019210701000X");
    b.setName("wangwu");
    b.setSex("female");
    b.showInfo();
}