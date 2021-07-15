#include <stdio.h>
#include <malloc.h>
typedef int ElementType;
#define M 3
// B+树，M=3
typedef struct node
{
    Node *left;
    Node *mid;
    Node *right;
    Node *temp;
    Node *parent;
    ElementType element[M];
} Node;
//initialize, insert (with splitting) and search
Node *BuildTree(int n);
int Find(Node *root, ElementType element);
int IsLeaf(Node *pre);
void Insert(Node *root, ElementType element);
void PrintNode(Node *pre);
Node *CreateNode(void)
{
    Node *pre = (Node *)malloc(sizeof(Node));
    pre->left = pre->mid = pre->right = pre->temp = pre->parent = NULL;
    for (int i = 0; i < M; i++)
    {
        pre->element[i] = 0;
    }
}
int main()
{
    int n;
    scanf("%d", &n);
    Node *root = BuildTree(n);
}

int Find(Node *root, ElementType element)
{
    return 0;
}

Node *BuildTree(int n)
{
    Node *root = CreateNode();

    for (int i = 0; i < n; i++)
    {
        ElementType element;
        scanf("%d", &element);
        if (!Find(root, element))
        {
            Insert(root, element);
        }
        else
        {
            printf("Key %d is duplicated", element);
        }
    }
    return root;
}

int IsLeaf(Node *pre)
{
    if (pre == NULL)
    {
        return 0;
    }
    if (pre->left == NULL && pre->mid == NULL && pre->right == NULL)
    {
        return 1;
    }
    return 0;
}

void Insert(Node *root, ElementType element)
{

    Node *pre = root;
    while (!IsLeaf(pre))
    {
        if (pre->left)
        {
            if (element < pre->element[0])
                pre = pre->left;
        }
        else
        {
            pre->left = (Node *)malloc(sizeof(Node));
            pre->left->left = pre->left->mid = pre->left->right = pre->left->temp = NULL;
            pre->left->parent = pre;
        }

        else if (element < pre->element[1])
            pre = pre->mid;
        else pre = pre->right;
    }
    // 现在pre到了叶子结点，

    int index;
    while (pre->element[index])
    {
        index++;
    }
    if (index == M)
    {
        split
    }
    else
    {
        pre->element[index] = element;
    }
}

void PrintNode(Node *pre)
{
    printf("[");
    if (pre->element[0])
    {
        printf("%d", pre->element[0]);
        for (int i = 1; i < M; i++)
        {
            if (pre->element[i])
            {
                printf(",%d", pre->element[i]);
            }
        }
    }
    printf("]");
    return;
}