// #pragma once
#ifndef _MY_BPLUSTREE_H
#define _MY_BPLUSTREE_H 1

#include "BufferManager.h"
#include "template_function.h"
#include <algorithm>
#include <sstream>
#include <string.h>
#include <iostream>
#include <vector>
//using namespace std;
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
    std::string file_name;
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
    mybplustree(std::string name, int key_size, int degree);
    ~mybplustree();
    int SearchVal(ElementType &key);

    bool InsertKey(ElementType &key, int val);

    bool DeleteKey(ElementType &key);

    void DropTree(Node<ElementType> *node);
    // 打印头节点和所有叶子结点
    void PrintAllLeaf();

    // TODO: --------------------------------------------
    // 文件操作,该部分与buffer 有关
    void CheckFilePath(std::string path);
    int GetBlockNum(std::string table_name);
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

// 构造函数
template <typename ElementType>
Node<ElementType>::Node(int degree, bool is_leaf)
{
    this->num_of_key = 0;
    this->parent = NULL;
    this->is_leaf = is_leaf;
    this->degree = degree;
    this->next_leaf_node = NULL;

    for (int i = 0; i <= degree; i++)
    {
        childs.push_back(NULL);
        keys.push_back(ElementType());
        vals.push_back(int());
    }
    childs.push_back(NULL);
}
// 析构函数
template <typename ElementType>
Node<ElementType>::~Node()
{
}

template <typename ElementType>
bool Node<ElementType>::IsRoot()
{
    if (parent == NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}

template <typename ElementType>
bool Node<ElementType>::SearchKey(ElementType key, int &index)
{
    if (num_of_key == 0)
    {
        index = 0;
        return false;
    }

    if (keys[num_of_key - 1] < key)
    {
        index = num_of_key;
        return false;
    }
    else if (keys[0] > key)
    {
        index = 0;
        return false;
    }
    else //
    {
        for (int i = 0; i < num_of_key; i++)
        {
            if (keys[i] == key)
            {
                index = i;
                return true;
            }
            else if (keys[i] > key)
            {
                index = i;
                return false;
            }
        }
    }
    return false;
}

// 向叶子结点加入val
template <typename ElementType>
int Node<ElementType>::AddKey(ElementType &key, int val)
{
    // 不是叶子结点，插入值失败了
    if (!is_leaf)
    {
        cout << "it's not leaf node, insert failed" << endl;
        return -1;
    }
    // 节点里没有key
    if (num_of_key == 0)
    {
        keys[0] = key;
        vals[0] = val;
        num_of_key++;
        return 0;
    }
    else
    {
        int index = 0;
        // 通过引用的方式将index改变
        bool find = SearchKey(key, index);
        if (find)
        {
            cout << "Duplicated key" << endl;
            return -1;
        }
        else
        {
            // 向后挪动一个节点
            for (int i = num_of_key; i > index; i--)
            {
                keys[i] = keys[i - 1];
                vals[i] = vals[i - 1];
            }
            keys[index] = key;
            vals[index] = val;
            num_of_key++;

            return index;
        }
    }
    return -1;
}

// 向非叶子结点插入key值
template <typename ElementType>
int Node<ElementType>::AddKey(ElementType &key)
{
    if (num_of_key == 0)
    {
        keys[0] = key;
        num_of_key++;
        return 0;
    }
    else
    {
        int index = 0;
        bool find = SearchKey(key, index);
        if (find)
        {
            cout << "Duplicated key" << endl;
            return -1;
        }
        else
        {
            // 向后挪动一个节点
            for (int i = num_of_key; i > index; i--)
            {
                keys[i] = keys[i - 1];
                childs[i + 1] = childs[i];
            }
            keys[index] = key;
            childs[index + 1] = NULL;
            num_of_key++;

            return index;
        }
    }
    return 0;
}
template <typename ElementType>
bool Node<ElementType>::DeleteKey(ElementType key)
{
    int index;
    bool find = SearchKey(key, index);
    if (!find)
    {
        cout << "Delete false, Key:" << key << " not found!" << endl;
        return false;
    }
    else
    {
        // 由于叶子结点和中间节点的情况不同，所以分开进行处理
        if (is_leaf)
        {
            num_of_key--;
            for (int i = index; i < num_of_key; i++)
            {
                keys[i] = keys[i + 1];
                vals[i] = vals[i + 1];
            }
            // 弹出最后这个节点
            keys[num_of_key] = ElementType();
            vals[num_of_key] = int();
        }
        else
        {
            num_of_key--;
            for (int i = index; i < num_of_key; i--)
            {
                keys[i] = keys[i + 1];
                childs[i + 1] = childs[i + 2];
            }
            keys[num_of_key] = ElementType();
            childs[num_of_key + 1] = NULL;
        }
        // 删除成功
        return true;
    }
    return false;
}
template <typename ElementType>
bool Node<ElementType>::DeleteKeyByIndex(int index)
{
    if (index > num_of_key)
    {
        cout << "Delete false, index:" << index << "not found!" << endl;
        return false;
    }
    else
    {
        // 由于叶子结点和中间节点的情况不同，所以分开进行处理
        if (is_leaf)
        {
            for (int i = index; i < num_of_key - 1; i++)
            {
                keys[i] = keys[i + 1];
                vals[i] = vals[i + 1];
            }

            keys[num_of_key - 1] = ElementType();
            vals[num_of_key - 1] = int();
        }
        else
        {
            for (int i = index; i < num_of_key - 1; i--)
            {
                keys[i] = keys[i + 1];
                childs[i + 1] = childs[i + 2];
            }
            keys[num_of_key - 1] = ElementType();
            childs[num_of_key] = NULL;
        }
        // 删除成功
        num_of_key--;
        return true;
    }
    return false;
}
template <typename ElementType>
Node<ElementType> *Node<ElementType>::Split(ElementType &key_ret)
{
    // 节点的数目
    int new_node_num = (degree - 1) / 2;
    // 创建分裂出的节点
    Node *new_node = new Node(degree, this->is_leaf);
    // 若当前分裂的节点是叶子结点
    if (is_leaf)
    {
        // 将键的值返回给上层的节点，用于更新上面的节点
        key_ret = keys[new_node_num + 1];
        for (int i = new_node_num + 1; i < degree; i++)
        {
            new_node->keys[i - new_node_num - 1] = keys[i];
            keys[i] = ElementType();
            new_node->vals[i - new_node_num - 1] = vals[i];
            vals[i] = int();
        }
        // 将新节点和该节点连接起来
        new_node->next_leaf_node = this->next_leaf_node;
        this->next_leaf_node = new_node;
        // 连接parent
        new_node->parent = this->parent;
        // 更新该节点中的节点数目
        // 就因为少了下面这行代码让我debug了半天
        new_node->num_of_key = new_node_num;
        /////////////////////////////////////
        this->num_of_key = new_node_num + 1;
    }
    else
    {
        // 非叶子结点的情况
        // 将键的值返回给上层的节点，用于更新上面的节点
        key_ret = keys[new_node_num];
        // 更新子节点的指针
        for (int i = new_node_num + 1; i < degree + 1; i++)
        {
            new_node->childs[i - new_node_num - 1] = this->childs[i];
            new_node->childs[i - new_node_num - 1]->parent = new_node;
            this->childs[i] = NULL;
        }
        // 更新key值
        for (int i = new_node_num + 1; i < degree; i++)
        {
            new_node->keys[i - 1 - new_node_num] = keys[i];
            keys[i] = ElementType();
        }

        keys[new_node_num] = ElementType();

        new_node->parent = this->parent;
        new_node->num_of_key = new_node_num;
        this->num_of_key = new_node_num;
    }
    return new_node;
}

// 构建
template <typename ElementType>
mybplustree<ElementType>::mybplustree(string name, int key_size, int degree) : file_name(name), key_num(0), level(0), node_num(0), root(NULL), key_size(key_size), degree(degree), leaf_head(NULL)
{
    Initial();
    // readfromdisk();
}
// 析构
template <typename ElementType>
mybplustree<ElementType>::~mybplustree()
{
    DropTree(root);
    key_num = 0;
    root = NULL;
    level = 0;
}

// 初始化
template <typename ElementType>
void mybplustree<ElementType>::Initial()
{
    // 为根节点申请空间
    root = new Node<ElementType>(degree, true);
    key_num = 0;
    // 默认有一个节点的level = 1
    level = 1;
    node_num = 1;
    leaf_head = root;
}
template <typename ElementType>
void mybplustree<ElementType>::FindLeafNode(Node<ElementType> *cur_node, ElementType key, SearchNode &search_node)
{
    int index = 0;
    if (cur_node->SearchKey(key, index))
    {
        if (cur_node->is_leaf)
        {
            search_node.cur_node = cur_node;
            search_node.find = true;
            search_node.index = index;
        }
        else
        {
            cur_node = cur_node->childs[index + 1];
            while (!cur_node->is_leaf)
            {
                cur_node = cur_node->childs[0];
            }
            search_node.cur_node = cur_node;
            search_node.index = 0;
            search_node.find = true;
        }
    }
    else
    {
        // 如果当前节点已经是叶子结点证明找不到了
        if (cur_node->is_leaf)
        {
            search_node.cur_node = cur_node;
            search_node.index = index;
            search_node.find = false;
        }
        else
        {
            // 如果不是叶子结点，则继续向下寻找
            FindLeafNode(cur_node->childs[index], key, search_node);
        }
    }
}
template <typename ElementType>
bool mybplustree<ElementType>::InsertKey(ElementType &key, int val)
{
    SearchNode search_node;
    if (!root)
    {
        Initial();
    }
    // 找到应该插入的根节点的位置
    FindLeafNode(root, key, search_node);
    if (search_node.find)
    {
        cout << "duplicated node" << endl;
        return false;
    }
    else
    {
        search_node.cur_node->AddKey(key, val);
        // 结点满了需要调整
        if (search_node.cur_node->num_of_key == degree)
        {
            // cout << "----kaishi tiaozheng------- " << endl;
            // search_node.cur_node->PrintNode();
            InsertAdjust(search_node.cur_node);
            // cout << "----------tiaozhegn wanle--------" << endl;
            // search_node.cur_node->PrintNode();
            // cout << "-------------------" << endl;
            // search_node.cur_node->next_leaf_node->PrintNode();
            // cout << "-------------------" << endl;
        }
        key_num++;
        return true;
    }
    return false;
}
template <typename ElementType>
bool mybplustree<ElementType>::InsertAdjust(Node<ElementType> *cur_node)
{
    cout << "---------Insert adjust-------" << endl;
    ElementType key;
    // 分裂
    Node<ElementType> *new_node = cur_node->Split(key);
    // cout << "current key = " << key << endl;
    // new_node->PrintNode();
    // cout << "-------------------" << endl;
    // cur_node->PrintNode();
    // cout << "-------------------" << endl;
    node_num++;
    // cout << "split completed" << endl;
    // 当前节点为根节点
    if (cur_node->IsRoot())
    {
        cout << "current node is root" << endl;
        Node<ElementType> *root = new Node<ElementType>(degree, false);
        if (root == NULL)
        {
            cout << "error" << endl;
        }
        else
        {
            level++;
            node_num++;
            this->root = root;
            cur_node->parent = root;
            new_node->parent = root;
            root->AddKey(key);
            root->childs[0] = cur_node;
            root->childs[1] = new_node;
            // cout << "current key = " << key << endl;
            return true;
        }
    }
    else // 当前节点不是根节点
    {
        Node<ElementType> *parent = cur_node->parent;
        int index = parent->AddKey(key);
        // 在这里通过引用把index调节为插入的值对应的index
        parent->childs[index + 1] = new_node;
        new_node->parent = parent;
        // 递归调整
        if (parent->num_of_key == degree)
        {
            return InsertAdjust(parent);
        }
        return true;
    }
    return false;
}
template <typename ElementType>
void mybplustree<ElementType>::DropTree(Node<ElementType> *node)
{
    if (node == NULL)
    {
        return;
    }
    else if (!node->is_leaf)
    {
        // 如果不是叶子结点，则递归删除子树，并清零指针值
        for (int i = 0; i <= node->num_of_key; i++)
        {
            DropTree(node->childs[i]);
            node->childs[i] = NULL;
        }
    }
    delete node;
    node_num--;
    return;
}
template <typename ElementType>
void mybplustree<ElementType>::PrintAllLeaf()
{
    if (!root)
    {
        cout << "root is null" << endl;
        return;
    }
    Node<ElementType> *pre = root;
    for (int i = 0; i < root->num_of_key; i++)
    {
        cout << root->keys[i] << "->";
    }
    cout << "head over" << endl;
    cout << "leaf start";
    pre = leaf_head;
    while (pre != NULL)
    {
        pre->PrintNode();
        cout << "|||";
        pre = pre->next_leaf_node;
    }
    cout << "->leaf over" << endl;
    cout << "----------PrintLeafOver---------" << endl;
    return;
}

template <typename ElementType>
void Node<ElementType>::PrintNode()
{
    for (int i = 0; i < num_of_key; i++)
    {
        cout << "->" << keys[i];
    }
    // cout << "out of this node";
    // cout << endl;
}

template <typename ElementType>
bool mybplustree<ElementType>::DeleteKey(ElementType &key)
{
    // 如果根节点是个空节点则直接失败
    if (!root)
    {
        cout << "error, there's no root!" << endl;
        return false;
    }
    // 找到需要删除的位置
    SearchNode search_node;
    FindLeafNode(root, key, search_node);
    if (!search_node.find)
    {
        // 没找到节点
        cout << "deletion failed for no such a key exists" << endl;
        return false;
    }
    else
    {
        // 正常删除过程
        // 如果要删的这个值在根节点上
        if (search_node.cur_node->IsRoot())
        {
            search_node.cur_node->DeleteKey(key);
            key_num--;
            return DeleteAdjust(search_node.cur_node);
        }
        else // 要删的值不在根节点上
        {
            if (search_node.index == 0 && leaf_head != search_node.cur_node)
            {
                // 如果key不在枝干上，要回上层更新枝干

                int index = 0;

                Node<ElementType> *cur_parent = search_node.cur_node->parent;
                bool find_in_branch = cur_parent->SearchKey(key, index);
                while (!find_in_branch)
                {
                    if (cur_parent->parent)
                    {
                        cur_parent = cur_parent->parent;
                    }
                    else
                    {
                        break;
                    }
                    find_in_branch = cur_parent->SearchKey(key, index);
                }
                // TODO:
                cur_parent->keys[index] = search_node.cur_node->keys[1];

                search_node.cur_node->DeleteKeyByIndex(search_node.index);
                key_num--;
                return DeleteAdjust(search_node.cur_node);
            }
            else // 在叶子结点上
            {
                search_node.cur_node->DeleteKeyByIndex(search_node.index);
                key_num--;
                return DeleteAdjust(search_node.cur_node);
            }
        }
    }
    return false;
}
template <typename ElementType>
bool mybplustree<ElementType>::DeleteAdjust(Node<ElementType> *node)
{
    int new_node_num = (degree - 1) / 2;
    // 不需要调整的情况
    if (degree == 3)
    {
        if ((!node->is_leaf) && (node->num_of_key < 0))
            return true;
    }
    else if (degree != 3)
    {
        if (!(node->is_leaf) && (node->num_of_key >= new_node_num - 1))
            return true;
    }
    else if ((node->is_leaf) && (node->num_of_key >= new_node_num))
    {
        return true;
    }
    // 需要调整的情况：
    if (node->IsRoot())
    {
        // 是根节点的情况
        if (node->num_of_key > 0)
        {
            return true;
        }
        else
        {
            // 需要调整的节点是叶子结点
            if (root->is_leaf)
            {
                delete node;
                root = NULL;
                leaf_head = NULL;
                level--;
                node_num--;
            }
            else // 需要调整的节点是根节点但不是叶子结点
            {
                root = node->childs[0];
                root->parent = NULL;
                delete node;
                level--;
                node_num--;
            }
        }
    }
    else // 不是根节点的情况
    {
        Node<ElementType> *parent = node->parent;
        Node<ElementType> *sibling = NULL;
        if (node->is_leaf)
        {
            // 非根非叶的情况
            int index = 0;
            // 找到需要删除的位置
            parent->SearchKey(node->keys[0], index);

            // 左 sibling
            if (parent->childs[0] != node && index + 1 == parent->num_of_key)
            {
                sibling = parent->childs[index];
                // sibling的节点更多
                if (sibling->num_of_key > new_node_num)
                {
                    for (int i = node->num_of_key; i > 0; i--)
                    {
                        node->keys[i] = node->keys[i - 1];
                        node->vals[i] = node->vals[i - 1];
                    }
                    node->keys[0] = sibling->keys[sibling->num_of_key - 1];
                    node->vals[0] = sibling->vals[sibling->num_of_key - 1];

                    sibling->DeleteKeyByIndex(sibling->num_of_key - 1);

                    node->num_of_key++;
                    parent->keys[index] = node->keys[0];
                    return true;
                }
                else
                {
                    parent->DeleteKeyByIndex(index);

                    for (int i = 0; i < node->num_of_key; i++)
                    {
                        sibling->keys[i + sibling->num_of_key] = node->keys[i];
                        sibling->vals[i + sibling->num_of_key] = node->vals[i];
                    }
                    sibling->num_of_key += node->num_of_key;
                    sibling->next_leaf_node = node->next_leaf_node;

                    delete node;
                    node_num--;
                    // 递归调整上一层节点
                    return DeleteAdjust(parent);
                }
            }
            else
            {
                if (parent->childs[0] == node)
                {
                    sibling = parent->childs[1];
                }
                else
                {
                    sibling = parent->childs[index + 2];
                }
                if (sibling->num_of_key > new_node_num)
                {
                    node->keys[node->num_of_key] = sibling->keys[0];
                    node->vals[node->num_of_key] = sibling->vals[0];
                    node->num_of_key++;
                    sibling->DeleteKeyByIndex(0);
                    if (parent->childs[0] == node)
                    {
                        parent->keys[0] = sibling->keys[0];
                    }
                    else
                    {
                        parent->keys[index + 1] = sibling->keys[0];
                    }
                    return true;
                }
                else
                {
                    for (int i = 0; i < sibling->num_of_key; i++)
                    {
                        node->keys[node->num_of_key + i] = sibling->keys[i];
                        node->vals[node->num_of_key + i] = sibling->vals[i];
                    }

                    if (node == parent->childs[0])
                    {
                        parent->DeleteKeyByIndex(0);
                    }
                    else
                    {
                        parent->DeleteKeyByIndex(index + 1);
                    }
                    node->num_of_key += sibling->num_of_key;
                    node->next_leaf_node = sibling->next_leaf_node;
                    delete sibling;
                    node_num--;

                    return DeleteAdjust(parent);
                }
            }
        }
        else // 当前节点不是叶子结点，而是枝干节点
        {
            int index = 0;
            parent->SearchKey(node->childs[0]->keys[0], index);
            if ((parent->childs[0] != node) && (index + 1 == parent->num_of_key))
            {
                sibling = parent->childs[index];
                if (sibling->num_of_key > new_node_num - 1)
                {
                    node->childs[node->num_of_key + 1] = node->childs[node->num_of_key];
                    for (unsigned int i = node->num_of_key; i > 0; i--)
                    {
                        node->childs[i] = node->childs[i - 1];
                        node->keys[i] = node->keys[i - 1];
                    }
                    node->childs[0] = sibling->childs[sibling->num_of_key];
                    node->keys[0] = parent->keys[index];
                    node->num_of_key++;

                    parent->keys[index] = sibling->keys[sibling->num_of_key - 1];

                    if (sibling->childs[sibling->num_of_key])
                        sibling->childs[sibling->num_of_key]->parent = node;
                    sibling->DeleteKeyByIndex(sibling->num_of_key - 1);

                    return true;
                }
                else
                {
                    sibling->keys[sibling->num_of_key] = parent->keys[index];
                    parent->DeleteKeyByIndex(index);
                    sibling->num_of_key++;

                    for (int i = 0; i < node->num_of_key; i++)
                    {
                        sibling->childs[sibling->num_of_key + i] = node->childs[i];
                        sibling->keys[sibling->num_of_key + i] = node->keys[i];
                        sibling->childs[sibling->num_of_key + i]->parent = sibling;
                    }
                    sibling->childs[sibling->num_of_key + node->num_of_key] = node->childs[node->num_of_key];
                    sibling->childs[sibling->num_of_key + node->num_of_key]->parent = sibling;

                    sibling->num_of_key += node->num_of_key;

                    delete node;
                    node_num--;

                    return DeleteAdjust(parent);
                }
            }
            else
            {
                if (parent->childs[0] == node)
                    sibling = parent->childs[1];
                else
                    sibling = parent->childs[index + 2];
                if (sibling->num_of_key > new_node_num - 1)
                {

                    node->childs[node->num_of_key + 1] = sibling->childs[0];
                    node->keys[node->num_of_key] = sibling->keys[0];
                    node->childs[node->num_of_key + 1]->parent = node;
                    node->num_of_key++;

                    if (node == parent->childs[0])
                        parent->keys[0] = sibling->keys[0];
                    else
                        parent->keys[index + 1] = sibling->keys[0];

                    sibling->childs[0] = sibling->childs[1];
                    sibling->DeleteKeyByIndex(0);

                    return true;
                }
                else
                {

                    node->keys[node->num_of_key] = parent->keys[index];

                    if (node == parent->childs[0])
                        parent->DeleteKeyByIndex(0);
                    else
                        parent->DeleteKeyByIndex(index + 1);

                    node->num_of_key++;

                    for (int i = 0; i < sibling->num_of_key; i++)
                    {
                        node->childs[node->num_of_key + i] = sibling->childs[i];
                        node->keys[node->num_of_key + i] = sibling->keys[i];
                        node->childs[node->num_of_key + i]->parent = node;
                    }
                    node->childs[node->num_of_key + sibling->num_of_key] = sibling->childs[sibling->num_of_key];
                    node->childs[node->num_of_key + sibling->num_of_key]->parent = node;

                    node->num_of_key += sibling->num_of_key;

                    delete sibling;
                    node_num--;

                    return DeleteAdjust(parent);
                }
            }
        }
    }
    return false;
}
template <typename ElementType>
void mybplustree<ElementType>::CheckFilePath(string path)
{
    FILE *fp = fopen(path.c_str(), "r");
    if (fp == NULL)
    {
        // 如果文件不存在则创建一个文件
        FILE *fp = fopen(path.c_str(), "w+");
    }
    fclose(fp);
    return;
}
// TODO: this part is together with buffer_manager
template <typename ElementType>
int mybplustree<ElementType>::GetBlockNum(string table_name)
{
    char *p;
    int block_num = -1;
    do
    {
        p = buffer_manager.ReadPage(table_name, block_num + 1);
        block_num++;
    } while (p[0] != '\0');
    return block_num;
}
// TODO:这块没做什么改动
template <typename ElementType>
void mybplustree<ElementType>::ReadDisk(char *p, char *end)
{
    ElementType key;
    int value;

    for (int i = 0; i < PAGESIZE; i++)
        if (p[i] != '#')
            return;
        else
        {
            i += 2;
            char tmp[100];
            int j;

            for (j = 0; i < PAGESIZE && p[i] != ' '; i++)
                tmp[j++] = p[i];
            tmp[j] = '\0';
            std::string s(tmp);
            std::stringstream stream(s);
            stream >> key;

            memset(tmp, 0, sizeof(tmp));

            i++;
            for (j = 0; i < PAGESIZE && p[i] != ' '; i++)
                tmp[j++] = p[i];
            tmp[j] = '\0';
            std::string s1(tmp);
            std::stringstream stream1(s1);
            stream1 >> value;

            insertKey(key, value);
        }
}

template <typename ElementType>
void mybplustree<ElementType>::ReadDiskAll()
{
    string path = "./database/index/" + file_name;
    CheckFilePath(path);
    int block_num = GetBlockNum(path);

    if (block_num <= 0)
        block_num = 1;

    for (int i = 0; i < block_num; i++)
    {
        //获取当前块的句柄
        char *p = buffer_manager.ReadPage(path, i);
        //char* t = p;
        //遍历块中所有记录
        ReadDisk(p, p + PAGESIZE);
    }
}

template <typename ElementType>
void mybplustree<ElementType>::WriteDisk()
{
    string path = "./database/index/" + file_name;

    CheckFilePath(path);
    int block_num = GetBlockNum(path);
    // 从叶子结点开始写
    Node<ElementType> *temp = leaf_head;
    int i = 0, j = 0;
    for (i = 0, j = 0; temp != NULL; j++)
    {
        char *p = buffer_manager.ReadPage(path, j);
        int offset = 0;

        memset(p, 0, PAGESIZE);

        for (i = 0; i < temp->num_of_key; i++)
        {
            p[offset++] = '#';
            p[offset++] = ' ';

            copyString(p, offset, temp->keys[i]);
            p[offset++] = ' ';
            copyString(p, offset, temp->vals[i]);
            p[offset++] = ' ';
        }

        p[offset] = '\0';

        int page_id = buffer_manager.GetPageId(path, j);
        buffer_manager.ModifyPage(page_id);

        // 移动向下一个节点
        temp = temp->next_leaf_node;
    }
    // 可能还有剩下的block 没有解决
    while (j < block_num)
    {
        char *p = buffer_manager.ReadPage(path, j);
        memset(p, 0, PAGESIZE);

        int page_id = buffer_manager.GetPageId(path, j);
        buffer_manager.ModifyPage(page_id);

        j++;
    }
    return;
}
template <typename ElementType>
bool Node<ElementType>::GetValsInRange(int index, ElementType &key, vector<int> &vals_ret)
{
    int i;
    for (i = 0; i < num_of_key && keys[i] <= key; i++)
    {
        vals_ret.push_back(vals[i]);
    }

    if (keys[i] >= key)
    {
        return true;
    }
    else
    {
        return false;
    }
}

template <typename ElementType>
bool Node<ElementType>::GetValsInRange(int index, vector<int> &vals_ret)
{
    for (int i = index; i < num_of_key; i++)
    {
        vals_ret.push_back(vals[i]);
    }
    return false;
}

template <typename ElementType>
void mybplustree<ElementType>::SearchRange(ElementType &key1, ElementType &key2, vector<int> &vals, int flag)
{
    // 没有建树的时候
    if (!root)
    {
        return;
    }
    if (flag == 1)
    {
        SearchNode node2;
        FindLeafNode(root, key2, node2);

        bool finished = false;
        Node<ElementType> *cur_node = node2.cur_node;
        int index = node2.index;

        do
        {
            finished = cur_node->GetValsInRange(index, vals);
            index = 0;
            if (cur_node->next_leaf_node == NULL)
            {
                break;
            }
            else
            {
                cur_node = cur_node->next_leaf_node;
            }
        } while (!finished);
    }
    else if (flag == 2)
    {
        SearchNode node1;
        FindLeafNode(root, key1, node1);

        bool finished = false;
        Node<ElementType> *cur_node = node1.cur_node;
        int index = node1.index;
        do
        {
            // TODO:
            finished = cur_node->GetValsInRange(index, vals);
            index = 0;
            if (cur_node->next_leaf_node == NULL)
            {
                break;
            }
            else
            {
                cur_node = cur_node->next_leaf_node;
            }
        } while (!finished);
    }
    else
    {
        SearchNode node1, node2;
        FindLeafNode(root, key1, node1);
        FindLeafNode(root, key2, node2);
        bool finished = false;
        int index;

        if (key1 <= key2)
        {
            Node<ElementType> *cur_node = node1.cur_node;
            index = node1.index;
            do
            {
                finished = cur_node->GetValsInRange(index, key2, vals);
                index = 0;
                if (cur_node->next_leaf_node == NULL)
                {
                    break;
                }
                else
                {
                    cur_node = cur_node->next_leaf_node;
                }

            } while (!finished);
        }
        else
        {
            Node<ElementType> *cur_node = node2.cur_node;
            index = node2.index;
            do
            {
                finished = cur_node->GetValsInRange(index, key1, vals);
                index = 0;
                if (cur_node->next_leaf_node == NULL)
                {
                    break;
                }
                else
                {
                    cur_node = cur_node->next_leaf_node;
                }
            } while (!finished);
        }
    }
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());
    return;
}

template <typename ElementType>
int mybplustree<ElementType>::SearchVal(ElementType &key)
{
    if (!root)
        return -1;
    SearchNode search_node;
    FindLeafNode(root, key, search_node);

    if (!search_node.find)
        return -1;
    else
        return search_node.cur_node->vals[search_node.index];
}

#endif