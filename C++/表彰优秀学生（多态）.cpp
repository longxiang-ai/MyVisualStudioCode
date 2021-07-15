// 以Student为基类，构建GroupA, GroupB和GroupC三个类

#include <iostream>
#include <string>
using namespace std;

class Student
{
protected:
    string num;
    string name;
    int s1, s2, s3, s4, s5;
    char grade;

public:
    static double max;
    Student()
    {
        s1 = s2 = s3 = s4 = s5 = 0;
        num = "";
        name = "";
    }
    virtual void display() = 0;
};

double Student ::max = 0;
class GroupA : public Student
{
public:
    GroupA(string num, string name, int s1, int s2)
    {
        this->num = num;
        this->name = name;
        this->s1 = s1;
        this->s2 = s2;
        if (s1 + s2 > max)
        {
            max = s1 + s2;
        }
    }

    void display()
    {
        if ((s1 + s2) == max)
            cout << num << " " << name << endl;
    }
};

class GroupB : public Student
{
public:
    GroupB(string num, string name, int s1, int s2, char grade)
    {
        this->num = num;
        this->name = name;
        this->s1 = s1;
        this->s2 = s2;
        this->grade = grade;
        if (s1 + s2 > max)
        {
            max = s1 + s2;
        }
    }
    void display()
    {

        if ((s1 + s2) >= max * 0.7 && grade == 'A' || (s1 + s2) >= max)
            cout << num << " " << name << endl;
    }
};

class GroupC : public Student
{
public:
    GroupC(string num, string name, int s1, int s2, int s3, int s4, int s5)
    {
        this->num = num;
        this->name = name;
        this->s1 = s1;
        this->s2 = s2;
        this->s3 = s3;
        this->s4 = s4;
        this->s5 = s5;
    }
    void display()
    {

        if ((s1 + s2 + s3 + s4 + s5) / 5.0 >= max / 2.0 * 0.9)
            cout << num << " " << name << endl;
    }
};

/* 请在这里填写答案 */

int main()
{
    const int Size = 50;
    string num, name;
    int i, ty, s1, s2, s3, s4, s5;
    char gs;
    Student *pS[Size];
    int count = 0;
    for (i = 0; i < Size; i++)
    {
        cin >> ty;
        if (ty == 0)
            break;
        cin >> num >> name >> s1 >> s2;
        switch (ty)
        {
        case 1:
            pS[count++] = new GroupA(num, name, s1, s2);
            break;
        case 2:
            cin >> gs;
            pS[count++] = new GroupB(num, name, s1, s2, gs);
            break;
        case 3:
            cin >> s3 >> s4 >> s5;
            pS[count++] = new GroupC(num, name, s1, s2, s3, s4, s5);
            break;
        }
    }
    for (i = 0; i < count; i++)
    {
        pS[i]->display();
        delete pS[i];
    }
    return 0;
}