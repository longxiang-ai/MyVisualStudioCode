#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int Address;
    int Data;
    int Next;
};
Node *Merge(Node *a, Node *b, int N);
void Print(Node *list);
int main()
{
    int head1, head2;
    int N;
    Node list1[N];
    Node list2[N];
    scanf("%d %d %d", &head1, &head2, &N);
    int i = 0;
    for (i = 0; i < N; i++) //读入过程
    {
        int address, num, next;
        scanf("%d %d %d", &address, &num, &next);
        list1[i].Address = address;
        list1[i].Data = num;
        list1[i].Next = next;
        if (next == -1)
        {
            break;
        }
    }
    for (int j = 0; i + j < N; j++)
    {
        int address, num, next;
        scanf("%d %d %d", &address, &num, &next);
        list2[j].Address = address;
        list2[j].Data = num;
        list2[j].Next = next;
    }
    if (i > j)
    {
        Print(Merge(list1, list2, N));
    }
    else
    {
        Print(Merge(list2, list1, N));
    }
    return 0;
}
Node *Merge(Node *a, Node *b, int N) //将B插入A中
{
    int lenb;
    for (int i = 0; i < N; i++)
    {
        if (b[i].Next == -1)
        {
            lenb = i + 1;
            break;
        }
    }
    int lena = N - lenb;
    for (int i = 0; i < lena; i++)
    {
    }
}