#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define Nmax 10
typedef struct Node *PtrToNode;
struct Node
{
    int Coefficient;
    int Exponent;
    PtrToNode Next;
};
typedef PtrToNode Polynomial;
Polynomial Read();                          //读入一个多项式，返回dummy head的指针
void Print(Polynomial p);                   //链表形式打印出多项式p
Polynomial Add(Polynomial a, Polynomial b); //合并两个多项式,返回表头指针
int main()
{
    Polynomial a, b;
    a = Read();
    Print(a);
    b = Read();
    Print(b);
    Polynomial c;
    c = Add(a, b);
    Print(c);
    return 0;
}
Polynomial Read()
{
    Polynomial head = (Polynomial)malloc(sizeof(struct Node));
    head->Coefficient = 0;
    head->Exponent = 0;
    head->Next = NULL;
    //申请头结点空间，赋值
    int a;
    scanf("%d", &a); //读入接下来多项式a的项数
    int num1, num2;
    char nums[Nmax];
    Polynomial pre = head;      //现在的节点
    for (int i = 0; i < a; i++) //先读入a
    {
        scanf("%d %d", &num1, &num2);
        Polynomial thisnode = (Polynomial)malloc(sizeof(struct Node));

        thisnode->Coefficient = num1;
        thisnode->Exponent = num2;
        pre->Next = thisnode;
        pre = thisnode;
    }
    pre->Next = NULL;

    return head;
}
void Print(Polynomial head)
{
    Polynomial pre = head->Next; //现在的节点
    while (pre != NULL)          //先读入a
    {
        printf("%dx^(%d)+", pre->Coefficient, pre->Exponent);
        pre = pre->Next;
    }
    printf("\n");
    return;
}
Polynomial Add(Polynomial a, Polynomial b)
{
    Polynomial prea = a->Next;
    Polynomial preb = b->Next;
    int coe, e;                                                //每一项的数和指数
    Polynomial head = (Polynomial)malloc(sizeof(struct Node)); //创建头结点
    head->Coefficient = 0;
    head->Exponent = 0;
    head->Next = NULL;
    Polynomial pre = head;
    while (prea != NULL && preb != NULL)
    {
        if (prea->Exponent == preb->Exponent)
        {
            coe = prea->Coefficient + preb->Coefficient;
            e = prea->Exponent;
            prea = prea->Next;
            preb = preb->Next;
        }
        else if (prea->Exponent > preb->Exponent)
        {
            coe = prea->Coefficient;
            e = prea->Exponent;
            prea = prea->Next;
        }
        else if (prea->Exponent < preb->Exponent)
        {
            coe = preb->Coefficient;
            e = preb->Exponent;
            preb = preb->Next;
        }
        Polynomial thisnode = (Polynomial)malloc(sizeof(struct Node));
        thisnode->Coefficient = coe;
        thisnode->Exponent = e;
        pre->Next = thisnode;
        pre = thisnode;
    }
    if (prea != NULL)
    {
        while (prea != NULL)
        {
            Polynomial thisnode = (Polynomial)malloc(sizeof(struct Node));
            thisnode->Coefficient = prea->Coefficient;
            thisnode->Exponent = prea->Exponent;
            prea=prea->Next;
            pre->Next = thisnode;
            pre = thisnode;
        }
    }
    else if (preb != NULL)
    {
        while (preb != NULL)
        {
            Polynomial thisnode = (Polynomial)malloc(sizeof(struct Node));
            thisnode->Coefficient = preb->Coefficient;
            thisnode->Coefficient = preb->Exponent;
            preb=preb->Next;
            pre->Next = thisnode;
            pre = thisnode;
        }
    }
    pre->Next = NULL;
    return head;
}