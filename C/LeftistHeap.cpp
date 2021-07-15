#include <stdio.h>
#include <malloc.h>

typedef int ElementType;

typedef struct TreeNode
{
    ElementType Element;
    struct TreeNode *Left;
    struct TreeNode *Right;
    int Npl;
} node;
node *Merge(node *root1, node *root2);
node *Insert(node *root, ElementType element);
node *BuildHeap(int n);
void DispHeap(node *root);

int main()
{
    node *root1 = BuildHeap(3);
    node *root2 = BuildHeap(3);
    node *ret = Merge(root1, root2);
    DispHeap(ret);
}

node *Merge(node *root1, node *root2)
{
    if (root1 == NULL)
    {
        return root2;
    }
    else if (root2 == NULL)
    {
        return root1;
    }
    if (root1->Element > root2->Element)
    {
        // Swap(root1, root2);
        node *temp = root1;
        root1 = root2;
        root2 = temp;
    }
    // 递归完成Merge
    root1->Right = Merge(root1->Right, root2);
    // 当root1的右孩子已经Merge好了之后，对root1进行merge
    // 如果左边比右边Npl小，或者左边已经是空的了，则对左右进行交换
    if (root1->Left == NULL || root1->Left->Npl < root1->Right->Npl)
    {
        node *temp = root1->Left;
        root1->Left = root1->Right;
        root1->Right = temp;
    }
    // 更新Npl
    if (root1->Right != NULL)
    {
        root1->Npl = root1->Right->Npl + 1;
    }
    else
    {
        root1->Npl = 0;
    }
    return root1;
}
node *Insert(node *root, ElementType element)
{
    node *newnode = (node *)malloc(sizeof(node));
    newnode->Element = element;
    newnode->Left = NULL;
    newnode->Right = NULL;
    newnode->Npl = 0;
    return Merge(root, newnode);
}
node *BuildHeap(int n)
{
    node *root = NULL;
    // node *pre = root;
    for (int i = 0; i < n; i++)
    {
        ElementType num;
        scanf("%d", &num);
        root = Insert(root, num);
    }
    return root;
}
void DispHeap(node *root)
{
    int numofchild = 0;
    if (root != NULL)
    {
        if (root->Left != NULL)
        {
            numofchild++;
        }
        if (root->Right != NULL)
        {
            numofchild++;
        }
    }

    if (root != NULL)
    {
        if (numofchild == 0)
            printf("%d(%d) is root\n", root->Element, root->Npl);
        else
        {
            printf("%d(%d) is root,", root->Element, root->Npl);
            printf("numofchild is %d\n", numofchild);
        }

        // cout << tree->key << "(" << tree->npl << ")"
        //      << " is " << key << "'s " << (child == 1 ? "left child" : "right child") << endl;
        DispHeap(root->Left);
        DispHeap(root->Right);
    }
}