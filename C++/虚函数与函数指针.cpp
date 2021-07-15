// 构建一个二维图形（Shape）的基类，至少包含一个成员函数，打印图形名称和面积。
// 在基类的基础上衍生出圆（Circle）、长方形（Rectangle）、三角形（Triangle）三
// 个子类，要求分别包括计算面积必须的要素（数据成员）、打印图形信息的函数（成员
// 函数）。再构建一个二维图形的链表，三种节点按固定顺序排列（二维图形->圆->长方
// 形->三角形->二维图形......）。给出链表头节点，自动打印出所有节点信息。要求分别
// 用虚函数和函数指针实现。
#include <iostream>
#include <math.h>
#include <vector>
using namespace std;
class Shape
{
private:
public:
    virtual void printInfo() = 0;
};

class Circle : public Shape
{
private:
    double radius = 0;

public:
    Circle(double r)
    {
        radius = r;
    }
    void printInfo()
    {
        cout << "Name : "
             << "Circle"
             << " Area : " << 3.14159265 * radius * radius << endl;
    }
};

class Rectangle : public Shape
{
private:
    double length = 0;

public:
    Rectangle(double a)
    {
        length = a;
    }
    void printInfo()
    {
        cout << "Name : "
             << "Rectangle"
             << " Area : " << length * length << endl;
    }
};

class Triangle : public Shape
{
private:
    double a = 0;
    double b = 0;
    double c = 0;

public:
    Triangle(double a, double b, double c)
    {
        this->a = a;
        this->b = b;
        this->c = c;
    }
    void printInfo()
    {
        cout << "Name : "
             << "Triangle"
             << " Area : " << sqrt((a + b + c) / 2 * ((a + b + c) / 2 - a) * ((a + b + c) / 2 - b) * ((a + b + c) / 2 - c)) << endl;
    }
};

typedef struct node
{
    double *data;                // 存储所需的数据
    void (*printNode)(double *); // 打印当前节点的函数指针
    node *next;                  // 指向下一个节点的指针
} node;
void printShape(double data[])
{
    cout << "Name : Shape " << endl;
}

void printCircle(double data[])
{
    double radius = data[0];
    cout << "Name : "
         << "Circle"
         << " Area : " << 3.14159265 * radius * radius << endl;
}

void printRectangle(double data[])
{
    double length = data[0];
    cout << "Name : "
         << "Rectangle"
         << " Area : " << length * length << endl;
}

void printTriangle(double data[])
{
    double a = data[0], b = data[1], c = data[2];
    cout << "Name : "
         << "Triangle"
         << " Area : " << sqrt((a + b + c) / 2 * ((a + b + c) / 2 - a) * ((a + b + c) / 2 - b) * ((a + b + c) / 2 - c)) << endl;
}

void printListInfo(node *head)
{
    cout << "begin to print the list" << endl;
    node *pre = head;
    while (pre)
    {
        pre->printNode(pre->data);
        pre = pre->next;
    }
    cout << "print list over" << endl;
}

// testing function
int main()
{
    // virtual function
    cout << "using virtual function" << endl;
    Circle c(3);
    c.printInfo();
    Rectangle r(5);
    r.printInfo();
    Triangle t(3, 4, 5);
    t.printInfo();
    cout << "virtual function over" << endl;
    cout << endl;
    // function pointer
    cout << "using function pointer" << endl;
    // initial the list
    node *head = (node *)malloc(sizeof(node));
    head->data = NULL;
    head->printNode = printShape;
    head->next = NULL;
    node *pre = head;
    // construct the list
    for (int count = 1; count <= 12; count++)
    {
        // cout << "count = " << count << endl;
        node *p = (node *)malloc(sizeof(node));
        if (count % 4 == 1)
        {
            p->data = (double *)malloc(1 * sizeof(double));
            p->data[0] = count;
            p->printNode = printCircle;
        }
        else if (count % 4 == 2)
        {
            p->data = (double *)malloc(1 * sizeof(double));
            p->data[0] = count;
            p->printNode = printRectangle;
        }
        else if (count % 4 == 3)
        {
            p->data = (double *)malloc(3 * sizeof(double));
            p->data[0] = count;
            p->data[1] = count;
            p->data[2] = count;
            p->printNode = printTriangle;
        }
        else if (count % 4 == 0)
        {
            p->data = NULL;
            p->printNode = printShape;
        }
        pre->next = p;
        pre = p;
    }
    pre->next = NULL;
    // print the list
    printListInfo(head);
}

// output :
// using virtual function      
// Name : Circle Area : 28.2743
// Name : Rectangle Area : 25  
// Name : Triangle Area : 6    
// virtual function over       

// using function pointer      
// begin to print the list     
// Name : Shape
// Name : Circle Area : 3.14159
// Name : Rectangle Area : 4
// Name : Triangle Area : 3.89711
// Name : Shape
// Name : Circle Area : 78.5398
// Name : Rectangle Area : 36
// Name : Triangle Area : 21.2176
// Name : Shape
// Name : Circle Area : 254.469
// Name : Rectangle Area : 100
// Name : Triangle Area : 52.3945
// Name : Shape
// print list over