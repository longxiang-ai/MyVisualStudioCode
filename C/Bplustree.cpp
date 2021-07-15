#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <memory.h>
#define NUM(p) (p == NULL ? 0 : p->num)
#define GETP(p) (p == NULL ? NULL : p->parent)
#define GETR(p) (p == NULL ? NULL : p->rightNode)
#define GETL(p) (p == NULL ? NULL : p->leftNode)
#define GETM(p) (p == NULL ? NULL : p->midNode)
#define nil NULL;
#define null NULL;

typedef struct TreeNode
{
    int value[3]; //存储值的数组  含有三个元素
    int num;
    struct TreeNode *rightNode; //指向右结点
    struct TreeNode *leftNode;  //指向左结点     //3树结构会有三个结点
    struct TreeNode *midNode;   //指向中间结点
    struct TreeNode *tmpNode;   //作为四结点的缓存结点
    struct TreeNode *parent;    //指向双亲结点

} tn, *ptn;
//修复
void fixup(ptn p, ptn *root);
ptn createTreeNode(int value); //创建一个树结点
//交换
void change(int *a, int *b);
//插入一个结点
ptn insertTreeNode(ptn p, ptn *rootp)
{
    ptn pn;
    ptn move = p;

    ptn movep = p;

    int value = 0;
    for (fflush(stdin); scanf("%d", &value) != 1; fflush(stdin), value = 0)
        ; //输入1表示终止
    if (value == -1)
        return null; // 如果value值等于-1  那么这个函数返回null

    ptn tr = GETR(move); //如果p=move不为空 那么tr指向rightNode结点
    ptn tl = GETL(move); //下面是同样的道理  tl指向leftNode
    ptn tm = GETM(move); //tm=midNode
    while (!(!tr && !tl && !tm))
    { //如果这三个指针不全为空
        if (NUM(move) == 1)
        { //根据7行代码可知   如果move不是空  那么NUM(move)=move->num  此时move是一个二树
            if (value < move->value[0])
            { //如果输入的value值小于value[0]
                movep = move;
                move = move->leftNode; //将move的左指针指赋值给move
            }
            else
            {
                movep = move;
                move = move->rightNode; //否则就是将右指针赋值给move
            }
        }
        else if (NUM(move) == 2)
        { //如果move的num值等于2  此时move是一个3树
            if (value < move->value[0])
            {
                movep = move;
                move = move->leftNode;
            }
            else if (value > move->value[1])
            {
                movep = move;
                move = move->rightNode;
            }
            else
            {
                movep = move;
                move = move->midNode;
            }
        }

        tm = GETM(move);
        tr = GETR(move);
        tl = GETL(move);
    }

    if (NUM(move) == 1)
    { //如果原先是一个2树 那么增加一个结点后  num++  然后将加入的值放value[num]数组中去
        move->value[move->num] = value;
        move->num++;
        //交换一个左右的顺序
        if (move->value[0] > move->value[1])
            change(&(move->value[0]), &(move->value[1]));
        //这一步是调整一下位置关系
        fixup(move, rootp);
        return move;
    }
    else if (NUM(move) == 2)
    { //这种情况本来是3树
        move->value[move->num] = value;
        move->num++;
        //将value[]数组中元素按照从小到大的顺序排列
        if (move->value[1] > move->value[2])
            change(&(move->value[1]), &(move->value[2]));
        if (move->value[0] > move->value[1])
            change(&(move->value[0]), &(move->value[1]));
        fixup(move, rootp);
        return move;
    }
    else
    {
        //如果move指针为空 那么就新创建一个指针
        pn = createTreeNode(value);
        pn->parent = p; //p就是pn的双亲结点
        fixup(pn, rootp);
        return pn;
    }
}
//创建一个树结点
ptn createTreeNode(int value)
{
    //分配空间
    ptn pn = (ptn)malloc(sizeof(tn));
    pn->num = 0;
    pn->value[pn->num] = value; //将传入参数value赋值给数组对应num位置的值
    pn->num++;                  //num++数递增
    //将结构体中定义的结点全部指向空
    pn->leftNode = null;
    pn->rightNode = null;
    pn->midNode = null;
    pn->tmpNode = null;
    pn->parent = null;
    return pn;
}
//输出这个树的信息
void printTree(ptn root, int deep)
{
    if (NUM(root) == 0)
        return;                       //如果输入的root是一个空树  直接退出
    deep++;                           //将这个树的深度递增
    printTree(root->rightNode, deep); //遍历右指针

    if (NUM(root) == 2)
    {
        for (int j = 0; j < deep; j++)
        {
            printf(" ");
        }
        printf("%d\n", root->value[1]); //如果root中num的值为2,则输出数组中value[1]的值
    }
    printTree(root->midNode, deep); //输入这个树的中间结点的信息
    for (int j = 0; j < deep; j++)
    {
        printf(" ");
    }
    printf("%d\n", root->value[0]);  //输出数组value(0)的值
    printTree(root->leftNode, deep); //再遍历左结点
                                     //这是一个23 树 只有两个值 分别存储在value[0]和value[1]中
}
//交换a,b  在给value数组排序的时候将会用到
void change(int *a, int *b)
{
    int t = (*a);
    (*a) = (*b);
    (*b) = t;
}
void fixup(ptn p, ptn *root)
{
    ptn move = p;
    ptn movep = GETP(p); //movep指向p的双亲结点
    if (!p)
        return; //如果是一棵空树  直接返回
    if (NUM(move) == 3 && !movep)
    {                                           //如果move=p不为空 且没有双亲结点  其实就是根结点
        ptn b = createTreeNode(move->value[1]); //用value[1]中存储的值 创建一个新的结点
        ptn c = createTreeNode(move->value[2]); //value[2]中保存的值创建一个新的结点
        move->num = 1;                          //将move的num值降到1
        b->leftNode = move;                     //将move变成b结点左孩子
        b->rightNode = c;                       //c变成b结点的右孩子
        //这个两个结点的双亲结点都是p
        move->parent = b;
        c->parent = b;

        c->rightNode = move->rightNode;
        c->leftNode = move->tmpNode;
        move->rightNode = move->midNode;
        move->midNode = null;
        move->tmpNode = null;

        (*root) = b;
    }
    else if (NUM(move) == 3 && NUM(movep) == 1 && GETL(movep) == move)
    {
        movep->value[movep->num] = move->value[1];
        (movep->num)++;
        change(&(movep->value[0]), &(movep->value[1]));
        ptn c = createTreeNode(move->value[2]);
        c->parent = movep;
        movep->midNode = c;
        move->num = 1;

        c->rightNode = move->rightNode;
        move->rightNode = move->midNode;

        c->leftNode = move->tmpNode;
        move->tmpNode = null;
        move->midNode = null;
    }
    else if (NUM(move) == 3 && NUM(movep) == 1 && GETR(movep) == move)
    {

        movep->value[movep->num] = move->value[1];
        movep->num++;

        ptn d = createTreeNode(move->value[2]);
        d->parent = movep;
        movep->rightNode = d;
        move->num = 1;
        movep->midNode = move;

        d->rightNode = move->rightNode;
        move->rightNode = move->midNode;
        d->leftNode = move->tmpNode;
        move->tmpNode = null;
        move->midNode = null;
    }
    else if (NUM(move) == 3 && NUM(movep) == 2 && GETL(movep) == move)
    {

        movep->value[movep->num] = move->value[1];
        movep->num++;
        change(&(movep->value[0]), &(movep->value[2]));
        change(&(movep->value[1]), &(movep->value[2]));
        ptn c = createTreeNode(move->value[2]);
        c->parent = movep;
        movep->midNode = c;
        move->num = 1;

        c->rightNode = move->rightNode;
        move->rightNode = move->midNode;
        c->leftNode = move->tmpNode;
        move->midNode = null;
        move->tmpNode = null;

        fixup(movep, root);
    }
    else if (NUM(move) == 3 && NUM(movep) == 2 && GETM(movep) == move)
    {

        movep->value[movep->num] = move->value[1];
        movep->num++;
        change(&(movep->value[1]), &(movep->value[2]));
        ptn d = createTreeNode(move->value[2]);
        d->parent = movep;
        movep->tmpNode = d;
        move->num = 1;

        d->rightNode = move->rightNode;
        move->rightNode = move->midNode;
        d->leftNode = move->tmpNode;
        move->midNode = null;
        move->tmpNode = null;

        fixup(movep, root);
    }
    else if (NUM(move) == 3 && NUM(movep) == 2 && GETR(movep) == move)
    {
        movep->value[movep->num] = move->value[1];
        movep->num++;
        change(&(movep->value[1]), &(movep->value[2]));
        ptn c = createTreeNode(move->value[2]);
        c->parent = movep;
        movep->tmpNode = c;
        move->num = 1;

        c->leftNode = move->leftNode;
        move->leftNode = move->tmpNode;
        c->rightNode = move->midNode;
        move->midNode = null;
        move->tmpNode = null;

        fixup(movep, root);
    }
    else
    {
        return;
    }
}
//销毁树  释放每个结点指向的空间  也用到了递归的思想
void dropTree(ptn root)
{
    if (!root)
        return;
    if (root->leftNode)
    {
        free(root->leftNode);
    }
    if (root->rightNode)
    {
        free(root->rightNode);
    }
    if (root->midNode)
    {

        free(root->midNode);
    }
    if (root->tmpNode)
    {
        free(root->tmpNode);
    }
    free(root);
    root = null;
}
main()
{

    ptn root = null;
    ptn *rootp = null; //双亲结点
    ptn node = null;

    node = insertTreeNode(root, rootp);
    root = node;
    rootp = &root;
    do
    {
        node = insertTreeNode(root, rootp);
    } while (node != NULL);

    printTree(root, 0);
    dropTree(root);
}