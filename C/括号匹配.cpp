#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MaxLen 100
#define ERROR '\0'
typedef char ElementType;
typedef struct StackRecord *Stack;
struct StackRecord
{
    int Capacity;
    int Top;
    ElementType *Array;
};
Stack CreateStack(int StackCapacity);
bool IsLeftBracket(char ch);
bool IsRightBracket(char ch);
bool Push(Stack S, char ch);
ElementType Pop(Stack S);
bool IsFull(Stack S);
bool IsEmpty(Stack S);
int main()
{
    int StackCapacity = 10;
    // scanf("%d", &StackCapacity);
    // getchar();
    char line[MaxLen] = {'\0'};
    gets(line);
    // printf("line = %s\n",line);
    int i = 0;
    Stack S = CreateStack(StackCapacity);

    bool match = true;
    while (line[i] != '\0' && match)
    {
        if (IsLeftBracket(line[i]))
        {
            Push(S, line[i]);
            // printf("Push=%c\n",line[i]);
        }
        else if (IsRightBracket(line[i]))
        {
            ElementType ch = Pop(S);
            // printf("Pop=%c\n",ch);
            switch (ch)
            {
            case '\0':
                match = false;
                break;
            case '(':
                if (line[i] != ')')
                {
                    match = false;
                }
                break;
            case '[':
                if (line[i] != ']')
                {
                    match = false;
                }
                break;
            case '{':
                if (line[i] != '}')
                {
                    match = false;
                }
                break;
            }
        }
        i++;
    }
    if (match && IsEmpty(S))
    {
        printf("Match!");
    }
    else
    {
        printf("Not Match");
    }
    return 0;
}
Stack CreateStack(int StackCapacity)
{
    Stack S = (Stack)malloc(sizeof(struct StackRecord));
    S->Capacity = StackCapacity;
    S->Top = -1;
    ElementType *array = (ElementType *)malloc(sizeof(ElementType) * StackCapacity); //申请空间
    S->Array = array;
    return S;
}
bool IsLeftBracket(char ch)
{
    if (ch == '(' || ch == '[' || ch == '{')
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool IsRightBracket(char ch)
{
    if (ch == ')' || ch == ']' || ch == '}')
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool IsFull(Stack S)
{
    if (S->Top == S->Capacity-1)
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool IsEmpty(Stack S)
{
    if (S->Top == -1)
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool Push(Stack S, char ch)
{
    // printf("In Push \n");
    if (IsFull(S))
    {
        // printf("S->top=%d",S->Top);
        // printf("S->capacity=%d",S->Capacity);
        // printf("Is Full");
        return false;
    }
    else
    {
        S->Array[++S->Top] = ch;
        // printf("Push1 = %c",S->Array[S->Top-1]);
        return true;
    }
}
ElementType Pop(Stack S)
{
    if (IsEmpty(S))
    {
        return ERROR;
    }
    else
    {
        ElementType ch = S->Array[S->Top--];
        return ch;
    }
}