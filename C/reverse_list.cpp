//要求用O（N)的时间复杂度和常数的空间消耗来逆转链表
#include <stdio.h>
#include <stdlib.h>
typedef int ElementType;
typedef struct Node *PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;
struct Node
{
    ElementType Element;
    Position Next;
};
List Read();
void Print(List L);
List Reverse(List L);

int main()
{
    List L1, L2;
    L1 = Read();
    L2 = Reverse(L1);
    Print(L1);
    Print(L2);
    return 0;
}
List Reverse(List L)
{
    if (L->Next != NULL)
    {
        List thisnode = L->Next;
        List nextnode = thisnode->Next;
        List lastnode = L;
        while (nextnode != NULL)
        {
            lastnode = thisnode;
            thisnode = nextnode;
            nextnode = nextnode->Next;
            thisnode->Next = lastnode;
        }
        L->Next->Next = NULL;
        L->Next = thisnode;
    }
    return L;
}
List Read() //读入链表
{
    int n;
    scanf("%d", &n);
    List head = (List)malloc(sizeof(struct Node));
    head->Element = 0;
    head->Next = NULL;
    List pre = head;

    for (int i = 0; i < n; i++)
    {
        ElementType num = 0;
        scanf("%d", &num);
        List thisnode;
        thisnode = (List)malloc(sizeof(struct Node));
        thisnode->Element = num;
        pre->Next = thisnode;
        pre = thisnode;
    }
    pre->Next = NULL;
    return head;
}
void Print(List L)
{
    List pre = L->Next;
    while (pre != NULL)
    {
        printf("%d->", pre->Element);
        pre = pre->Next;
    }
    printf("NULL\n");
    return;
}