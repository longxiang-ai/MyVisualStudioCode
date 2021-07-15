
#ifndef _MY_BPLUSTREE_H
#define _MY_BPLUSTREE_H 1

#include "BufferManager.h"
#include <string.h>
#include <iostream>
#include <vector>
using namespace std;
extern BufferManager buffer_manager;

template <typename ElementType = int>
class Node
{
private:
    /* data */
public:
    Node(int degree, bool is_leaf);
    ~Node();
    // 判断是不是根节点
    bool IsRoot();
    // 查找某个值
    bool SearchKey(ElementType key, int &index);
    // 分裂
    Node *Split(ElementType &key_ret);
    // 添加值，返回Index
    // 叶子结点
    int AddKey(ElementType &key, int val);
    // 非叶子结点
    int AddKey(ElementType &key);
    // 删除值
    bool DeleteKey(ElementType key);
    bool DeleteKeyByIndex(int index);
    // 打印当前节点的值
    void PrintNode();
    // 返回一定范围内容器的两个函数重载
    // 返回index到key 范围内的vector
    bool GetValsInRange(int index, ElementType &key, vector<int> &vals_ret);
    // 返回从index 到 num_of_key的vector
    bool GetValsInRange(int index, vector<int> &vals_ret);

public:
    // 该结点内key的数量
    size_t num_of_key;
    // 指向父节点的指针
    Node *parent;
    // key的容器
    vector<ElementType> keys;
    // value的容器
    vector<int> vals;
    // 子节点
    vector<Node *> childs;

    Node *next_leaf_node;
    bool is_leaf;
    size_t degree;
};

template <typename ElementType>
class mybplustree
{
private:
    string file_name;
    Node<ElementType> *root;
    Node<ElementType> *leaf_head;

    int key_num;
    int level;
    int node_num;
    int key_size;
    int degree;

    // for search
    struct SearchNode
    {
        Node<ElementType> *cur_node;
        int index;
        bool find;
    };

public:
    mybplustree(string name, int key_size, int degree);
    ~mybplustree();
    int SearchVal(ElementType &key);

    bool InsertKey(ElementType &key, int val);

    bool DeleteKey(ElementType &key);

    void DropTree(Node<ElementType> *node);
    // 打印头节点和所有叶子结点
    void PrintAllLeaf();

    // TODO: --------------------------------------------
    // 文件操作,该部分与buffer 有关
    void CheckFilePath(string path);
    int GetBlockNum(string table_name);
    void ReadDisk(char *p, char *end);
    void ReadDiskAll();
    void WriteDisk();
    // TODO: --------------------------------------------
    void SearchRange(ElementType &key1, ElementType &key2, vector<int> &vals, int flag);

private:
    void Initial();

    bool InsertAdjust(Node<ElementType> *node);

    bool DeleteAdjust(Node<ElementType> *node);

    void FindLeafNode(Node<ElementType> *cur_node, ElementType key, SearchNode &search_node);
};

#endif