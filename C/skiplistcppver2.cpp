#include <iostream>
#include <ctime>
#include <random>

using namespace std;
// 无穷大
#define INF (0x7fffffff)
// 一个事先定义好的 maxlevel
#define MAXLEVEL (20)

// 元素类型
typedef int ElementType;
// 节点定义
typedef struct node
{
    ElementType key;      // 当前节点的值
    struct node *next[1]; // 指向后续节点的指针数组
} Node;

// 跳表定义
typedef struct skiplist
{
    int level;  // 层数
    Node *head; // 头指针
} List;

// 类的定义

class SkipList
{
public:
    SkipList()
    {
        CreateList();
        // cout << "Construction complete" << endl;
    }
    ~SkipList()
    {
        FreeList();
        // cout << "Destruction complete" << endl;
    }
    // 申请一个具有level层的节点空间
    void CreateNode(int level, Node *&thisnode);
    // 插入
    bool Insert(ElementType &key);
    // 删除
    bool Delete(ElementType &key);
    // 查找
    bool Search(ElementType &key);
    // 打印level0的值
    void PrintList();

private:
    void CreateList();
    void FreeList();
    // 包含元素数目
    int size;
    // 跳表指针
    List *list;
    // 尾节点，存值为无穷大
    Node *NILL;
};

// 创建一个n层的节点
// 注意这里用Node* & 是为了能够更改外部的thisnode的值
void SkipList::CreateNode(int level, Node *&thisnode)
{
    // 每个节点分配空间大小：1个Node所占的空间，以及level个Node * 指针所占的空间
    thisnode = (Node *)malloc(sizeof(Node) + level * sizeof(Node *));
    return;
}

// 创建skiplist
void SkipList::CreateList()
{
    // 创建空节点（将来作为尾节点）
    CreateNode(0, NILL);
    NILL->key = INF;
    // 为list分配空间
    list = (List *)malloc(sizeof(List));
    // 默认list为0层
    list->level = 0;
    // 默认起始时元素个数为0
    size = 0;

    // 设置list的头节点，初始时指向 NILL，层数大小为事先指定的最大值 MAXLEVEL
    CreateNode(MAXLEVEL, list->head);
    for (int i = 0; i < MAXLEVEL; i++)
    {
        list->head->next[i] = NILL;
    }
    return;
}
// 查找一个值为key的元素，找到了返回true，否则返回false
bool SkipList ::Search(ElementType &key)
{
    // 根据跳表的性质，查找的时候应该从更高的level开始向下找，这样能够尽可能跳过多的点
    // 从头结点出发
    Node *pre = list->head;
    for (int i = list->level; i >= 0; i--)
    {
        // 在第i层，如果遇到下一个点的key比当前的key还要小，那么证明要找的点还在后面
        while (pre->next[i]->key < key)
        {
            pre = pre->next[i];
        }
    }
    // 向后挪动一个（此时已经是在底层了，level = 0）
    pre = pre->next[0];
    // 刚好key相等，则证明已经找到了
    if (pre->key == key)
    {
        return true;
    }
    else
    {
        return false;
    }
}
// 随机数生成函数
int RandomLevel(double p)
{
    int level = 0;
    while (level < MAXLEVEL)
    {
        srand(time(NULL));
        if (rand() / (RAND_MAX + 1.0) < p)
        {
            level++;
        }
        else
        {
            break;
        }
    }
    return level;
}
// 插入
// 首先最低层是一定要插入的
// 再考虑上面的层，以一定的概率决定在某一层进行插入
bool SkipList ::Insert(ElementType &key)
{
    // cout << "----------begin to insert " << key << "-----------" << endl;
    // 由于需要将当前位置和后面的位置连接指针，所以这里用temp[i]来存储第i层的前一个位置
    Node *temp[MAXLEVEL];
    // 插入首先找到当前应该插入的位置，这里的实现和Search类似
    Node *pre = list->head;
    for (int i = list->level; i >= 0; i--)
    {
        while (pre->next[i]->key < key)
        {
            pre = pre->next[i];
        }
        // 与search 不同的是，每次找到当层最小的大于k的节点时，需要将这个节点跟后续相连
        // 所以这里用temp先存储起来
        temp[i] = pre;
    }
    // cout << "move to the position finished" << endl;
    // 将节点移动到最底层的下一个节点
    pre = pre->next[0];
    // 如果当前已经存在了同样的值，则代表插入失败了
    if (pre->key == key)
    {
        // cout << "duplicated key here" << endl;
        return false;
    }
    else
    {
        // 如果没有当前值，则需要进行插入
        // 随机一个level的值
        // int level = rand() % MAXLEVEL;
        int level = RandomLevel(0.25);
        // if (level == 0)
        //     level = 1;
        // cout << "random level = " << level << endl;
        if (level > list->level)
        {
            level = ++list->level;
            temp[level] = list->head;
        }
        // temp[level] = list->head;
        // 为新节点申请空间
        Node *InsertNode;
        CreateNode(level, InsertNode);

        InsertNode->key = key;
        // cout << "malloc finished " << endl;
        // 将节点连接到链表中
        for (int i = level; i >= 0; i--)
        {
            pre = temp[i];
            InsertNode->next[i] = pre->next[i];
            pre->next[i] = InsertNode;
        }
        // cout << "link finished" << endl;
        // 插入成功之后总节点数+1
        size++;
        // cout << "now size = " << size << endl;
        return true;
    }
}
// 删除节点
bool SkipList ::Delete(ElementType &key)
{
    // cout << "----------begin to delete " << key << "-----------" << endl;
    // 和插入一样，首先需要找到需要删除节点的位置，且用temp存放前一个位置的节点
    Node *temp[MAXLEVEL];
    Node *pre = list->head;
    for (int i = list->level; i >= 0; i--)
    {
        while (pre->next[i]->key < key)
        {
            pre = pre->next[i];
        }
        // 与search 不同的是，每次找到当层最小的大于k的节点时，需要将这个节点跟后续相连
        // 所以这里用temp先存储起来
        temp[i] = pre;
    }
    // 将节点移动到最底层的下一个节点
    pre = pre->next[0];
    // 如果当前当前的值和寻找的值不相同，则代表并不存在这个节点
    // 删除失败
    if (pre->key != key)
    {
        return false;
    }
    else
    {
        // 如果找到了当前值的位置
        // 将这个节点从链表中剔除
        for (int i = 0; i <= list->level; i++)
        {
            if (temp[i]->next[i] == pre)
            {
                temp[i]->next[i] = pre->next[i];
            }
            else
            {
                break;
            }
        }

        // 释放当前节点的空间
        free(pre);
        size--;
        return true;
    }
}
// 将整个链表空间释放
void SkipList::FreeList()
{
    // cout << "------------begin to freelist------------" << endl;
    // 直接将最低一层的节点释放了，这样整个空间就能够被释放
    Node *pre = list->head;
    Node *temp;
    // 当pre不是NILL的时候直接释放
    // cout << "begin to free the values " << endl;
    while (pre != NILL)
    {
        temp = pre->next[0];
        free(pre);
        pre = temp;
    }
    // cout << "free the value finished" << endl;
    // 将最右边的节点释放
    free(NILL);
    // cout << "free NILL finished" << endl;
    // 最后将list释放即可
    free(list);
    // cout << "-------freelist finished-------------------" << endl;
}
// 打印最低层的链表
void SkipList::PrintList()
{
    // cout << "-----------begin to print----------" << endl;
    Node *pre = list->head->next[0];
    int count = 0;
    while (pre != NILL)
    {
        count++;
        cout << pre->key << endl;
        pre = pre->next[0];
    }
    // cout << count << " nodes in total " << endl;
    // cout << "NILL Node:";
    // cout << pre->key << endl;
    // cout << "----------print finished-----------" << endl;
}

int main()
{
    int total_time = 0;

    SkipList s;
    const int MAX = 500000;
    // 初始化跳表中的值
    for (int i = MAX; i >= 0; i--)
    {
        s.Insert(i);
    }

    const int try_times = 100;
    for (int j = 0; j < try_times; j++)
    {
        clock_t startTime, endTime;
        random_device rd;
        uniform_int_distribution<int> dist(0, MAX);
        // 生成随机数
        const int times = 1000;
        int random[times] = {0};
        for (int i = 0; i < times; i++)
        {
            random[i] = dist(rd);
        }
        startTime = clock(); //计时开始
        // 插入times个值
        for (int i = 0; i < times; i++)
        {
            s.Search(random[i]);
        }
        endTime = clock(); //计时结束
        cout << "The run time is: " << (endTime - startTime) << "ms" << endl;
        total_time += endTime - startTime;

        // for (int i = 0; i < times; i++)
        // {
        //     s.Delete(random[i]);
        // }
        // s.PrintList();
    }
    cout << "Total time = " << total_time << endl;
    cout << "average time = " << total_time * 1.0 / try_times << endl;
    // system("pause");
}