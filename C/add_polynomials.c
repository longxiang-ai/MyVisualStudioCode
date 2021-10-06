#include <stdio.h>
#include <stdlib.h>
typedef struct Node *PtrToNode;
struct Node
{
    int Coefficient;
    int Exponent;
    PtrToNode Next;
};
typedef PtrToNode Polynomial;

Polynomial Read();        /* details omitted */
void Print(Polynomial p); /* details omitted */
Polynomial Add(Polynomial a, Polynomial b);

int main()
{
    Polynomial a, b, s;
    a = Read();
    b = Read();
    s = Add(a, b);
    Print(s);
    // Print(a);
    return 0;
}

/* Your function will be put here */
Polynomial Read()
{
    int N;
    scanf("%d", &N);
    Polynomial head = (Polynomial)malloc(sizeof(struct Node));
    head->Coefficient = 0;
    head->Exponent = 0;
    head->Next = NULL;
    Polynomial pre = head;
    for (int i = 0; i < N; i++)
    {
        // printf("\n %d times \n", i);
        Polynomial temp = (Polynomial)malloc(sizeof(struct Node));
        scanf("%d %d", &temp->Coefficient, &temp->Exponent);
        // printf("%d %d", temp->Coefficient, temp->Exponent);
        temp->Next = NULL;
        pre->Next = temp;
        pre = temp;
    }
    pre->Next = NULL;
    return head;
}

void Print(Polynomial p)
{
    Polynomial pre = p;
    while (p = p->Next)
    {
        // printf("%dx^%d ", p->Coefficient, p->Exponent);
        printf("%d %d", p->Coefficient, p->Exponent);
        if (p->Next)
        {
            printf(" ");
        }
    }
    return;
}
// 将a,b的值加起来存在s（一个新的链表头上）
Polynomial Add(Polynomial a, Polynomial b)
{
    Polynomial prea = a->Next, preb = b->Next;
    Polynomial head = (Polynomial)malloc(sizeof(struct Node));
    head->Exponent = 0;
    head->Coefficient = 0;
    head->Next = NULL;

    Polynomial pre = head;

    while (prea && preb)
    {
        if (prea->Exponent == preb->Exponent)
        {
            int sum = prea->Coefficient + preb->Coefficient;
            if (sum!=0)
            {
                Polynomial temp = (Polynomial)malloc(sizeof(struct Node));
                temp->Coefficient = sum;
                temp->Exponent = prea->Exponent;
                temp->Next = NULL;
                pre->Next = temp;
                pre = temp;
            }
            prea = prea->Next;
            preb = preb->Next;
        }
        else if (prea->Exponent > preb->Exponent)
        {
            Polynomial temp = (Polynomial)malloc(sizeof(struct Node));
            temp->Coefficient = prea->Coefficient;
            temp->Exponent = prea->Exponent;
            temp->Next = NULL;
            pre->Next = temp;
            pre = temp;
            prea = prea->Next;
        }
        else if (prea->Exponent < preb->Exponent)
        {
            Polynomial temp = (Polynomial)malloc(sizeof(struct Node));
            temp->Coefficient = preb->Coefficient;
            temp->Exponent = preb->Exponent;
            temp->Next = NULL;
            pre->Next = temp;
            pre = temp;
            preb = preb->Next;
        }
    }
    while (prea)
    {
        Polynomial temp = (Polynomial)malloc(sizeof(struct Node));
        temp->Coefficient = prea->Coefficient;
        temp->Exponent = prea->Exponent;
        temp->Next = NULL;
        pre->Next = temp;
        pre = temp;
        prea = prea->Next;
    }
    while (preb)
    {
        Polynomial temp = (Polynomial)malloc(sizeof(struct Node));
        temp->Coefficient = preb->Coefficient;
        temp->Exponent = preb->Exponent;
        temp->Next = NULL;
        pre->Next = temp;
        pre = temp;
        preb = preb->Next;
    }
    pre->Next = NULL;
    return head;
}