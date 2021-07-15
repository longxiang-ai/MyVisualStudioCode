#include <iostream>
using namespace std;
class Publication
{
protected:
    string title; //名称
    float price;  //原价
    int day;      //租期
public:
    Publication()
    {
        ;
    }
    Publication(string titlein, float pricein, int dayin)
    {
        title = titlein;
        price = pricein;
        day = dayin;
    }
    virtual void display() = 0; //打印价格清单
};

class Book : public Publication
{
    double quality;

public:
    Book(string titlein, float pricein, int dayin, double qualityin) : Publication(titlein, pricein, dayin)
    {
        quality = qualityin;
    }
    virtual void display()
    {
        cout << title << " ";
        printf("%.1f", day * 1.2);
        if (day * 1.2 > price * quality * 2)
            printf(" %.1f R", price * quality * 2);
        cout << endl;
    }
};

class Tape : public Publication
{
    int quality;

public:
    Tape(string titlein, float pricein, int dayin, double qualityin) : Publication(titlein, pricein, dayin)
    {
        quality = qualityin;
    }
    virtual void display()
    {
        cout << title << " ";
        printf("%.1f", day * 1.2);
        if (day * 1.2 > (price / (quality / 3 + 1)) * 2)
            printf(" %.1f R", (price / (quality / 3 + 1)) * 2);
        cout << endl;
    }
};
int main()
{
    int type;
    cin >> type;
    string name;
    double price;
    int day;
    double quality;
    do
    {
        Publication *pp;
        cin >> name >> price >> day >> quality;
        if (type == 1)
        {
            pp = new Book(name, price, day, quality);
        }
        else if (type == 2)
        {
            pp = new Tape(name, price, day, quality);
        }
        pp->display();
        delete pp;
        cin >> type;
    } while (type != 0);
}