#include <iostream>
using namespace std;
class Animal
{
public:
    int age;

    Animal(int age = 0)
    {
        this->age = age;
    }

    int getAge()
    {
        return this->age;
    }
};

class Dog : public Animal
{
public:
    string color;
    Dog(int age, string color)
    {
        this->age = age;
        this->color = color;
    }
    void showInfor()
    {
        // cout << "infor of dog:" << endl;
        cout << "age:" << age << endl
             << "color:" << color << endl;
    }
};

int main()
{
    Animal ani(5);
    cout << "age of ani:" << ani.getAge() << endl;
    Dog dog(5, "black");
    cout << "infor of dog:" << endl;
    dog.showInfor();
}
