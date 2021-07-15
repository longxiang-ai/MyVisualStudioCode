// 一个跳表，应该具有以下特征：
// 1、一个跳表应该有几个层（level）组成;通常是10-20层，leveldb中默认为12层。
// 2、跳表的第0层包含所有的元素，且节点值是有序的。
// 3、每一层都是一个有序的链表，层数越高应越稀疏，这样在高层次中能 '跳过'许多的不符合条件的数据。
// 4、如果元素x出现在第i层，则所有比i小的层都包含x;
// 5、每个节点包含key及其对应的value和一个指向该节点第n层的下个节点的指针数组 x->next[level] 表示第level层的x的下一个节点

#include <stdio.h>
#include <malloc.h>

typedef int ElementType;
typedef struct node
{
    ElementType key;   // 用于查找的值
    ElementType value; // 当前节点的值
    Node *next[1];     // 指向后续节点的指针数组
} Node;

typedef struct skiplist
{
    int level;  // 层数
    Node *head; // 头指针
} list;

void CreateList()
{
    // 创建一个空节点
    Node *NillNode;
    NillNode = (Node *)malloc(level * sizeof(Node *) + sizeof(Node));
    NillNode->next = NULL;
}

Node *CreateNode(int level)
{
    Node *thisnode;
    thisnode = (Node *)malloc(level * sizeof(Node *) + sizeof(Node)); // 存放level 个额外的Node*指针 以及 一个Node的正常空间
    return thisnode;
}