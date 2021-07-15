#include <stdio.h>
#include <stdlib.h>

struct node
{
    int element; //元素
    int height;  //当前节点的高度
    struct node *left;  //左节点
    struct node *right; //右节点
};
typedef struct node Node;

int FindHeight(Node *r) //得到这个节点的高度,r代表当前节点的指针
{
    // 如果是空节点，认为高度是-1
    int Height = -1;
    if (r == NULL)
    {
        return Height;
    }
    else
    {
        int LeftHeight = FindHeight(r->left);
        int RightHeight = FindHeight(r->right);
        if (LeftHeight < RightHeight)
        {
            Height = RightHeight + 1;
        }
        else
        {
            Height = LeftHeight + 1;
        }
        return Height;
    }
}
Node *RRRotation(Node *r) //右子树插右孩子，r是出现失衡的节点，返回旋转后子树根节点的位置
{
    Node *NewRoot = r->right;
    r->right = NewRoot->left;
    NewRoot->left = r;
    //更新高度
    r->height = FindHeight(r);
    NewRoot->height = FindHeight(NewRoot);
    return NewRoot;
}
Node *LLRotation(Node *r) //左子树插左孩子，r是出现失衡的节点，返回旋转后子树根节点的位置
{
    Node *NewRoot = r->left;
    r->left = NewRoot->right;
    NewRoot->right = r;
    //更新高度
    r->height = FindHeight(r);
    NewRoot->height = FindHeight(NewRoot);
    return NewRoot;
}

Node *RLRotation(Node *r) //右子树插左孩子，要进行两次Rotate
{
    Node *NewRoot;
    r->right = LLRotation(r->right);
    NewRoot = RRRotation(r);
    return NewRoot;
}
Node *LRRotation(Node *r) //左子树插右孩子，要进行两次Rotate
{
    Node *NewRoot;
    r->left = RRRotation(r->left);
    NewRoot = LLRotation(r);
    return NewRoot;
}

Node *InsertNode(Node *PrNode, int PrElement) // 由于插入的过程中要进行旋转改变树的结构，所以这里返回从下到上最先出问题子树的根节点
{
    if (PrNode == NULL) //插入叶子结点
    {
        PrNode = (Node *)malloc(sizeof(Node));
        PrNode->element = PrElement;
        PrNode->height = 0;
        PrNode->left = NULL;
        PrNode->right = NULL;
        return PrNode;
    }
    else
    {
        if (PrElement < PrNode->element) //如果要插入的元素比当前节点的元素小,则向左子树插入
        {
            PrNode->left = InsertNode(PrNode->left, PrElement);
            // 向左子树插入之后，由于平衡因子可能会增大，可能需要Rotate
            if (FindHeight(PrNode->left) - FindHeight(PrNode->right) > 1)
            {
                if (PrNode->left->element > PrElement) //LL型插入
                {
                    PrNode = LLRotation(PrNode);
                }
                else if (PrNode->left->element < PrElement) // LR型插入
                {
                    PrNode = LRRotation(PrNode);
                }
            }
        }

        if (PrElement > PrNode->element) //如果要插入的元素比当前节点的元素大,则向右子树插入
        {
            PrNode->right = InsertNode(PrNode->right, PrElement);

            if (FindHeight(PrNode->left) - FindHeight(PrNode->right) < -1)
            {
                if (PrNode->right->element < PrElement) //RR型插入
                {
                    PrNode = RRRotation(PrNode);
                }
                else if (PrNode->right->element > PrElement) // RL型插入
                {
                    PrNode = RLRotation(PrNode);
                }
            }
        }
        PrNode->height = FindHeight(PrNode); // 更新高度
        return PrNode;
    }
}
int main()
{
    int N = 3;
    scanf("%d", &N); //读取节点数目
    int i = 0;
    Node *root = NULL; //根节点初始为NULL

    for (i = 0; i < N; i++)
    {
        int PrElement;
        scanf("%d", &PrElement);
        root = InsertNode(root, PrElement);
    }
    printf("%d\n", root->element);
}