#include <stdio.h>
#include <stdlib.h>
#define M 3
#define MAXN 10000
typedef int ElementType;
typedef struct node
{
    ElementType element[M + 1];
    int NumOfElements;
    struct node *left;
    struct node *mid;
    struct node *right;
    struct node *parent;
    struct node *temp;
} Node;
// 判断深度
int FindDepth(Node *pre)
{
    int depth = 0;
    while (pre != NULL)
    {
        pre = pre->parent;
        depth++;
    }
    return depth - 1;
}
// 判断是否为叶子结点
int IsLeaf(Node *T)
{
    if (T->NumOfElements == 0 || (T->left == NULL && T->mid == NULL && T->right == NULL && T->temp == NULL))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
//队列实现
Node *queue[MAXN];
int rear = 0;
int front = 0;
void EnQueue(Node *data) //从队尾进队
{
    queue[rear] = data;
    rear++;
}
Node *DeQueue() //从队首出队
{
    if (front != rear)
    {
        return queue[front++];
    }
    else
        return NULL;
}
Node *CreateNode(ElementType element) //创建一个含element的节点
{
    Node *pre = (Node *)malloc(sizeof(Node));
    pre->element[0] = element;
    pre->NumOfElements = 1;
    pre->element[1] == -1;
    pre->element[2] == -1;
    pre->element[3] == -1;
    pre->left = NULL;
    pre->mid = NULL;
    pre->right = NULL;
    pre->parent = NULL;
    pre->temp = NULL;
    return pre;
}
void PrintNode(Node *pre)
{
    printf("[");
    for (int i = 0; i < pre->NumOfElements; i++)
    {
        printf("%d", pre->element[i]);
        if (i != pre->NumOfElements - 1)
        {
            printf(",");
        }
    }
    printf("]");
}

Node *InsertLeafNode(ElementType element, Node *pre)
{
    //插入到合适的位置，先不考虑改换顺序
    int count = 0;
    for (int i = 0; i <= 3; i++)
    {
        if (pre->element[i] >= 0)
        {
            count++;
        }
    }
    pre->NumOfElements = count;

    if (pre->NumOfElements == 0)
    {
        pre->element[0] = element;
        pre->NumOfElements++;
        return pre;
    }

    if (pre->NumOfElements == 1)
    {
        if (element < pre->element[0])
        {
            pre->element[1] = pre->element[0];
            pre->element[0] = element;
        }
        else
        {
            pre->element[1] = element;
        }
    }
    else if (pre->NumOfElements == 2)
    {
        if (element < pre->element[0])
        {
            pre->element[2] = pre->element[1];
            pre->element[1] = pre->element[0];
            pre->element[0] = element;
        }
        else if (element < pre->element[1])
        {
            pre->element[2] = pre->element[1];
            pre->element[1] = element;
        }
        else
        {
            pre->element[2] = element;
        }
    }
    else if (pre->NumOfElements == 3)
    {
        if (element < pre->element[0])
        {
            pre->element[3] = pre->element[2];
            pre->element[2] = pre->element[1];
            pre->element[1] = pre->element[0];
            pre->element[0] = element;
        }
        else if (element < pre->element[1])
        {
            pre->element[3] = pre->element[2];
            pre->element[2] = pre->element[1];
            pre->element[1] = element;
        }
        else if (element < pre->element[2])
        {
            pre->element[3] = pre->element[2];
            pre->element[2] = element;
        }
        else
        {
            pre->element[3] = element;
        }
    }
    pre->NumOfElements++;
    return pre;
}
ElementType FindMin(Node *pre)
{
    while (!IsLeaf(pre))
    {
        pre = pre->left;
    }
    return pre->element[0];
}
Node *Adjust(Node *pre) //调整2树的key值
{
    //2树的left孩子必然不可能是NULL
    if (pre->mid != NULL)
    {
        pre->element[0] = FindMin(pre->mid);
    }
    if (pre->right != NULL)
    {
        pre->element[1] = FindMin(pre->right);
    }
    return pre;
}
Node *Insert(ElementType element, Node *root)
{
    // root是根节点,已经在外部初始化好了
    Node *pre = root;
    while (!IsLeaf(pre)) //不是叶子结点的时候继续选择下一层
    {

        if (element < pre->element[0])
        {
            pre = pre->left;
        }
        else if (element >= pre->element[0] && element < pre->element[1])
        {
            pre = pre->mid;
        }
        else if (element >= pre->element[1])
        {
            pre = pre->right;
        }
    }
    //是叶子结点时插入
    pre = InsertLeafNode(element, pre); //将该节点插入之后再进行调整，判断是否需要调整
    if (pre->NumOfElements == M + 1)    //该叶子结点满了，则分裂
    {
        //分裂为两个新叶子节点
        Node *parent = pre->parent;

        Node *child1, *child2;
        child1 = CreateNode(pre->element[0]);
        child1->element[1] = pre->element[1];
        child1->element[2] = -1;
        child1->element[3] = -1;
        child1->NumOfElements = 2;

        child2 = CreateNode(pre->element[2]);
        child2->element[1] = pre->element[3];
        child2->element[2] = -1;
        child2->element[3] = -1;
        child2->NumOfElements = 2;

        if (pre->parent == NULL) //如果说叶子节点同时也是根节点
        {
            /////////////////////////////
            Node *NewRoot = CreateNode(child2->element[0]);
            NewRoot->left = child1;
            NewRoot->right = child2;
            NewRoot->NumOfElements = 1;

            child1->parent = NewRoot;
            child2->parent = NewRoot;
            
            return NewRoot;
        }

        //将节点和父节点连接起来
        child1->parent = parent;
        child2->parent = parent;
        
        if (pre == parent->left) //如果是左儿子分裂，只需要右边给左边腾出位置即可，右边一定是有一个temp的位置，否则不平衡了
        {
            parent->left = child1;
            parent->temp = parent->right;
            parent->right = parent->mid;
            parent->mid = child2;
        }
        else if (pre == parent->mid)
        {
            parent->mid = child1;
            parent->temp = parent->right;
            parent->right = child2;
        }
        else if (pre == parent->right)
        {
            parent->right = child1;
            parent->temp = child2;
        }
        int count = 0;
        for (int i = 0; i < 4; i++)
        {
            if (parent->element[i] >= 0)
                count++;
        }

        parent->NumOfElements = count;
        parent = Adjust(parent); //调整parent的key值

        //调整的对象变为父亲（2树）
        // printf("out");
        pre = pre->parent;

        while (1) //如果2树结点有四个孩子，则需要分裂为两个新二树
        {
            Node *parent = pre->parent;
            if (parent == NULL)
            {
                printf("null");
            }
            if (parent == NULL)
            {
                Node *NewChild1;
                NewChild1->left = pre->left;
                NewChild1->mid = pre->mid;
                NewChild1->right = NULL;
                NewChild1->temp = NULL;
                NewChild1 = Adjust(NewChild1);
                int count = 0;
                for (int i = 0; i < 4; i++)
                {
                    if (NewChild1->element[i] >= 0)
                        count++;
                }
                NewChild1->NumOfElements = count;
                count = 0;
                Node *NewChild2;
                NewChild2->left = pre->right;
                NewChild2->mid = pre->temp;
                NewChild2->right = NULL;
                NewChild2->temp = NULL;
                for (int i = 0; i < 4; i++)
                {
                    if (NewChild2->element[i] >= 0)
                        count++;
                }
                NewChild2->NumOfElements = count;

                Node *Newparent = CreateNode(NewChild2->element[0]);
                Newparent = Adjust(Newparent);
                NewChild1->parent = Newparent;
                NewChild2->parent = Newparent;
                Newparent->left = NewChild1;
                Newparent->mid = NewChild2;
                Newparent->NumOfElements = 1;
                Newparent = Adjust(Newparent);
                return Newparent;
            }
            else if (parent->temp != NULL) //2树需要分裂
            {

                //创建两个新孩子
                Node *NewChild1;

                NewChild1->parent = parent;
                NewChild1->left = pre->left;
                NewChild1->mid = pre->mid;
                NewChild1->right = NULL;
                NewChild1->temp = NULL;
                NewChild1 = Adjust(NewChild1);
                int count = 0;
                for (int i = 0; i < 4; i++)
                {
                    if (NewChild1->element[i] >= 0)
                        count++;
                }
                NewChild1->NumOfElements = count;
                count = 0;
                Node *NewChild2;

                NewChild2->parent = parent;
                NewChild2->left = pre->right;
                NewChild2->mid = pre->temp;
                NewChild2->right = NULL;
                NewChild2->temp = NULL;
                for (int i = 0; i < 4; i++)
                {
                    if (NewChild2->element[i] >= 0)
                        count++;
                }
                NewChild2->NumOfElements = count;
                count = 0;
                // NewChild2->NumOfElements = 2;
                NewChild2 = Adjust(NewChild2);
                // 将孩子和父亲连接起来
                if (pre == parent->left)
                {
                    parent->temp = parent->right;
                    parent->right = parent->mid;
                    parent->mid = NewChild2;
                    parent->left = NewChild1;
                }
                else if (pre == parent->mid)
                {
                    parent->temp = parent->right;
                    parent->right = NewChild2;
                    parent->mid = NewChild1;
                }
                else if (pre == parent->right)
                {
                    parent->temp = NewChild2;
                    parent->right = NewChild1;
                }
            }
            pre = parent;          //更改父亲节点
            if (pre->temp == NULL) //停止条件即不需要再分裂了
            {
                break;
            }
            break;
        }
        return root; //返回最终插入后根节点的位置
    }
    return root;
}

void Print(Node *root)
{
    if (root == NULL)
    {
        return;
    }
    Node *pre = root;
    EnQueue(pre); //pre入队
    int NowDepth = 0;
    while (front != rear)
    {
        Node *pre = DeQueue(); //当前节点出队

        if (FindDepth(pre) != NowDepth)
        {
            printf("\n");
            NowDepth++;
        }
        PrintNode(pre); //打印出队的节点
        if (pre->left != NULL)
        {
            EnQueue(pre->left); //左节点入队
        }
        if (pre->mid != NULL)
        {
            EnQueue(pre->mid);
        }
        if (pre->right != NULL)
        {
            EnQueue(pre->right);
        }
    }
}
int main()
{
    //读取结点个数
    int N;
    scanf("%d", &N);
    //创建根节点
    Node *root;
    // 初始化根节点
    root = (Node *)malloc(sizeof(Node));
    root->NumOfElements = 0;
    for (int i = 0; i < 4; i++)
    {
        root->element[i] = -1;
    }

    root->left = NULL;
    root->mid = NULL;
    root->right = NULL;
    root->temp = NULL;
    root->parent = NULL;
    ElementType input[N + 1];
    for (int i = 0; i < N + 1; i++)
    {
        input[i] = -1;
    }
    int count = N;
    for (int i = 0; i < count; i++)
    {
        scanf("%d", &input[i]);
        for (int j = 0; j < i; j++)
        {
            if (input[i] == input[j])
            {
                printf("Key %d is duplicated\n", input[i]);
                i--;
                count--;
                break;
            }
        }
    }
    for (int i = 0; i < count; i++)
    {
        // printf("input i = %d \n", input[i]);
        root = Insert(input[i], root);
    }
    Print(root);
}
