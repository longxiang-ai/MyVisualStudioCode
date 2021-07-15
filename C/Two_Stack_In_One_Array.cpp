#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ERROR 1e8
typedef int ElementType;
typedef enum
{
    push,
    pop,
    end
} Operation;
typedef struct StackRecord *Stack;
struct StackRecord
{
    int Capacity;
    int Top1;
    int Top2;
    ElementType *Array;
};
Stack CreateStack(int MaxElements);
int IsEmpty(Stack S, int Stacknum);
int IsFull(Stack S);
int Push(ElementType X, Stack S, int Stacknum);
ElementType Top_Pop(Stack S, int Stacknum);
Operation GetOp();
void PrintStack(Stack S, int Stacknum);
int main()
{
    int N, Sn, X;
    Stack S;
    int done = 0;
    scanf("%d", &N);
    S = CreateStack(N);
    while (!done)
    {
        switch (GetOp())
        {
        case push:
            scanf("%d %d", &Sn, &X);
            if (!Push(X, S, Sn))
                printf("Stack %d is Full!\n", Sn);
            break;
        case pop:
            scanf("%d", &Sn);
            X = Top_Pop(S, Sn);
            if (X == ERROR)
            {
                printf("Stack %d is Empty!\n", Sn);
            }
            break;
        case end:
            PrintStack(S, 1);
            PrintStack(S, 2);
            done = 1;
            break;
        }
    }
    return 0;
}
Stack CreateStack(int MaxElements)
{
    Stack S = (Stack)malloc(sizeof(struct StackRecord));
    // ElementType array[MaxElements] = {0}; //默认初始值为0
    ElementType *array = (ElementType *)malloc(sizeof(int) * MaxElements);
    S->Capacity = MaxElements;
    S->Top1 = 0;               //第一个栈从下往上
    S->Top2 = MaxElements - 1; //第二个栈从上往下
    S->Array = array;
    return S;
}
Operation GetOp()
{
    char line[20] = {'\0'};
    scanf("%s", line);
    Operation ret;
    // getchar();
    if (strcmp(line, "Push") == 0)
    {
        ret = push;
    }
    else if (strcmp(line, "Pop") == 0)
    {
        ret = pop;
    }
    else if (strcmp(line, "End") == 0)
    {
        ret = end;
    }
    return ret;
}
int IsEmpty(Stack S, int Stacknum)
{
    if (Stacknum == 1)
    {
        if (S->Top1 == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        if (S->Top2 == S->Capacity - 1)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}
int IsFull(Stack S)
{
    if (S->Top1 == S->Top2)
    {
        return true;
    }
    else
    {
        return false;
    }
}
int Push(ElementType X, Stack S, int Stacknum)
{
    bool ret;
    if (IsFull(S))
    {
        ret = false;
    }
    else
    {
        if (Stacknum == 1)
        {
            S->Array[S->Top1++] = X;
            ret = true;
        }
        else if (Stacknum == 2)
        {
            S->Array[S->Top2--] = X;
            ret = true;
        }
    }
    return ret;
}
ElementType Top_Pop(Stack S, int Stacknum)
{
    if (Stacknum == 1)
    {
        if (IsEmpty(S, 1))
        {
            return ERROR;
        }
        else
        {
            return S->Array[S->Top1];
        }
    }
    else if (Stacknum == 2)
    {
        if (IsEmpty(S, 2))
        {
            return ERROR;
        }
        else
        {
            return S->Array[S->Top2];
        }
    }
    return ERROR;
}
void PrintStack(Stack S, int Stacknum)
{
    if (Stacknum == 1)
    {
        if (IsEmpty(S, 1))
        {
            printf("Stack %d is empty", Stacknum);
        }
        else
        {
            for (int i = 0; i < S->Top1; i++)
            {
                printf("%d->", S->Array[i]);
            }
            printf("Top1\n");
        }
    }
    else if (Stacknum == 2)
    {
        if (IsEmpty(S, 2))
        {
            printf("Stack %d is empty", Stacknum);
        }
        else
        {
            for (int i = S->Capacity - 1; i > S->Top2; i--)
            {
                printf("%d->", S->Array[i]);
            }
            printf("Top2\n");
        }
    }
    else
    {
        printf("Invalid Input\n");
    }
}