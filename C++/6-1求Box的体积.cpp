#include <iostream>
using namespace std;
class Box
{
public:
    double a;
    double b;
    double c;

    void get_value()
    {
        cin>>a>>b>>c;
    }
    void display()
    {
        cout<<a*b*c;
    }
};
int main()
{
    Box box2;
    box2.get_value();
    box2.display();
    return 0;
}

/* 请在这里填写答案 */