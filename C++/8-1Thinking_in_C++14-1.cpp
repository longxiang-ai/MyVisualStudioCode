// Creat a class called Car so that it also inherits from a class called Vehicle, placing appropriate member functions in Vehicle (that is, make up some member functions). Add a nondefault constructor to Vehicle, which you must call inside Car's constructor.

#include <iostream>
using namespace std;

class Vehicle
{
public:
    double weight;
    string type;
    string color;
    Vehicle(double weight, string type, string color)
    {
        this->weight = weight;
        this->type = type;
        this->color = color;
    }

    void ShowInfor()
    {
        cout << weight << " " << type << " " << color << endl;
    }
};

class Car : public Vehicle
{
public:
    string place;
    Car(string place, double weight, string type, string color) : Vehicle(weight, type, color)
    {
        this->place = place;
    }
};

int main()
{
    Vehicle a(1.5, "����", "��ɫ");
    a.ShowInfor();
    Car c("China", 1.8, "С�γ�", "��ɫ");
    c.ShowInfor();
}

// outputs are like this:
// 1.5 ���� ��ɫ
// 1.8 С�γ� ��ɫ