#include <iostream>
using namespace std;
class Car;
class Boat;

class Boat
{
private:
    int weight;

public:
    Boat(int weight)
    {
        this->weight = weight;
    }
    friend int getTotalWeight(Boat &boat, Car &car);
};

class Car
{
private:
    int weight;

public:
    Car(int weight)
    {
        this->weight = weight;
    }
    friend int getTotalWeight(Boat &boat, Car &car);
};

int getTotalWeight(Boat &boat, Car &car)
{
    return (boat.weight + car.weight);
}

int main()
{
    int n, m;
    cin >> n >> m;
    Boat boat(n);
    Car car(m);
    cout << "������������" << getTotalWeight(boat, car) << "��" << endl;
}