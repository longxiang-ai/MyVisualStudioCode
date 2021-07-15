#include <iostream>
using namespace std;

class Student
{
public:
    int num;
    string name;
    char gender;
    Student(int num_in, string name_in, char gender_in)
    {
        num = num_in;
        name = name_in;
        gender = gender_in;
    }
    void display()
    {
        cout << "Constructor called." << endl;
        cout << "num:" << num << endl;
        cout << "name:" << name << endl;
        cout << "sex:" << gender << endl;
        cout << endl;
    }
    ~Student()
    {
        cout << "Destructor called." << endl;
    }
};

int main()
{
    Student stud1(10010, "Wang_li", 'f');
    stud1.display();
    Student stud2(10011, "Zhang_fun", 'm');
    stud2.display();
    return 0;
}