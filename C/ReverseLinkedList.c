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

List Read();        /* details omitted */
void Print(List L); /* details omitted */
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

List Read()
{
    int N;
    scanf("%d", &N);
    List head = (List)malloc(sizeof(struct Node));
    head->Element = 0;
    head->Next = NULL;
    Position pre = head;
    for (int i = 0; i < N; i++)
    {
        Position temp = (Position)malloc(sizeof(struct Node));
        scanf("%d", &temp->Element);
        temp->Next = NULL;
        pre->Next = temp;
        pre = temp;
    }
    return head;
}

void Print(List L)
{
    if (L)
    {
        Position pre = L->Next;
        while (pre)
        {
            printf("%d ", pre->Element);
            pre = pre->Next;
        }
    }
    return;
}
// Write a nonrecursive procedure to reverse a singly linked list in O(N) time using constant extra space.
List Reverse(List L)
{
    // 由于链表先前实际上已经单向好了，所以这里只需要把其中连接的方向反向即可
    // 注意题目的输出可以看出，是直接在原链表的基础上进行修改即可
    // 先找到非dummy头节点的第一个结点：
    Position pre = L;
    Position next = pre->Next;
    pre = NULL; // 这里是由于最后的尾结点转化成null，所以先把pre改为NULL，最后再将头直接接在翻转后的表头即可
    // 然后用循环对链表的链接方向进行变换，注意到要保证在遍历链表的时候，向前遍历的指针不能丢失，
    // 因而这里选择用一个temp指针来进行暂存pre->next->next，然后再用next来存储pre->next的指针
    while (next != NULL)
    {
        Position temp = next->Next;
        next->Next = pre;
        pre = next;
        next = temp;
    }
    // pre->Next = NULL;
    // 最后将dummy头节点接上
    L->Next = pre;
    return L;
}
