#include "my_index_manager.h"

// 构建函数
IndexManager::IndexManager(std::string table_name)
{
    CatalogManager catalog;
    ATTRIBUTE attr = catalog.getAttribute(table_name);

    int i = 0;
    while (i < attr.num)
    {
        if (attr.index[i])
        {
            CreateIndex("INDEX_FILE_" + attr.name[i] + "_" + table_name, attr.type[i]);
        }
        i++;
    }
}

// 析构函数
IndexManager::~IndexManager()
{
    for (intMap::iterator itInt = indexIntMap.begin(); itInt != indexIntMap.end(); itInt++)
    {
        if (itInt->second)
        {
            itInt->second->WriteDisk();
            delete itInt->second;
        }
    }
    for (stringMap::iterator itString = indexStringMap.begin(); itString != indexStringMap.end(); itString++)
    {
        if (itString->second)
        {
            itString->second->WriteDisk();
            delete itString->second;
        }
    }
    for (floatMap::iterator itFloat = indexFloatMap.begin(); itFloat != indexFloatMap.end(); itFloat++)
    {
        if (itFloat->second)
        {
            itFloat->second->WriteDisk();
            delete itFloat->second;
        }
    }
}

int IndexManager::GetDegree(int type)
{
    int degree = (PAGESIZE - sizeof(int)) / (GetKeySize(type) + sizeof(int));
    if (degree % 2 == 0)
        degree -= 1;
    return degree;
}

int IndexManager::GetKeySize(int type)
{
    if (type == TYPE_FLOAT)
        return sizeof(float);
    else if (type == TYPE_INT)
        return sizeof(int);
    else if (type > 0)
        return type;
    else
    {
        // cout << "ERROR: in getKeySize: invalid type" << endl;
        return -100;
    }
}

void IndexManager::CreateIndex(std::string file_path, int type)
{
    int key_size = GetKeySize(type); //获取key的size
    int degree = GetDegree(type);    //获取需要的degree

    //根据数据类型不同，用对应的方法建立映射关系
    //并且先初始化一颗B+树
    if (type == TYPE_INT)
    {
        mybplustree<int> *tree = new mybplustree<int>(file_path, key_size, degree);
        indexIntMap.insert(intMap::value_type(file_path, tree));
    }
    else if (type == TYPE_FLOAT)
    {
        mybplustree<float> *tree = new mybplustree<float>(file_path, key_size, degree);
        indexFloatMap.insert(floatMap::value_type(file_path, tree));
    }
    else
    {
        mybplustree<std::string> *tree = new mybplustree<std::string>(file_path, key_size, degree);
        indexStringMap.insert(stringMap::value_type(file_path, tree));
    }

    return;
}

void IndexManager::DropIndex(std::string file_path, int type)
{
    //根据不同数据类型采用对应的处理方式
    if (type == TYPE_INT)
    {
        //查找路径对应的键值对
        intMap::iterator itInt = indexIntMap.find(file_path);
        if (itInt == indexIntMap.end())
        { //未找到
            // cout << "Error:in drop index, no index " << file_path <<" exits" << endl;
            return;
        }
        else
        {
            //删除对应的B+树
            delete itInt->second;
            //清空该键值对
            indexIntMap.erase(itInt);
        }
    }
    else if (type == TYPE_FLOAT)
    { //同上
        floatMap::iterator itFloat = indexFloatMap.find(file_path);
        if (itFloat == indexFloatMap.end())
        {
            // cout << "Error:in drop index, no index " << file_path <<" exits" << endl;
            return;
        }
        else
        {
            delete itFloat->second;
            indexFloatMap.erase(itFloat);
        }
    }
    else
    {
        stringMap::iterator itString = indexStringMap.find(file_path);
        if (itString == indexStringMap.end())
        { //同上
            // cout << "Error:in drop index, no index " << file_path <<" exits" << endl;
            return;
        }
        else
        {
            delete itString->second;
            indexStringMap.erase(itString);
        }
    }

    return;
}

int IndexManager::SearchIndex(std::string file_path, DATA data)
{
    //setKey(type, key);

    if (data.type == TYPE_INT)
    {
        intMap::iterator itInt = indexIntMap.find(file_path);
        if (itInt == indexIntMap.end())
        { //未找到
            // cout << "Error:in search index, no index " << file_path <<" exits" << endl;
            return -1;
        }
        else
            //找到则返回对应的键值
            return itInt->second->SearchVal(data.INTEGER);
    }
    else if (data.type == TYPE_FLOAT)
    {
        floatMap::iterator itFloat = indexFloatMap.find(file_path);
        if (itFloat == indexFloatMap.end())
        { //同上
            // cout << "Error:in search index, no index " << file_path <<" exits" << endl;
            return -1;
        }
        else
            return itFloat->second->SearchVal(data.POINT);
    }
    else
    {
        stringMap::iterator itString = indexStringMap.find(file_path);
        if (itString == indexStringMap.end())
        { //同上
            // cout << "Error:in search index, no index " << file_path <<" exits" << endl;
            return -1;
        }
        else
            return itString->second->SearchVal(data.WORD);
    }
}

void IndexManager::InsertIndex(std::string file_path, DATA data, int block_id)
{
    //setKey(type, key);

    if (data.type == TYPE_INT)
    {
        intMap::iterator itInt = indexIntMap.find(file_path);
        if (itInt == indexIntMap.end())
        {
            // cout << "Error:in search index, no index " << file_path <<" exits" << endl;
            return;
        }
        else
            itInt->second->InsertKey(data.INTEGER, block_id);
    }
    else if (data.type == TYPE_FLOAT)
    {
        floatMap::iterator itFloat = indexFloatMap.find(file_path);
        if (itFloat == indexFloatMap.end())
        {
            // cout << "Error:in search index, no index " << file_path <<" exits" << endl;
            return;
        }
        else
            itFloat->second->InsertKey(data.POINT, block_id);
    }
    else
    {
        stringMap::iterator itString = indexStringMap.find(file_path);
        if (itString == indexStringMap.end())
        {
            // cout << "Error:in search index, no index " << file_path <<" exits" << endl;
            return;
        }
        else
            itString->second->InsertKey(data.WORD, block_id);
    }
    return;
}

void IndexManager::DeleteIndexByKey(std::string file_path, DATA data)
{
    //setKey(type, key);

    if (data.type == TYPE_INT)
    {
        intMap::iterator itInt = indexIntMap.find(file_path);
        if (itInt == indexIntMap.end())
        {
            // cout << "Error:in search index, no index " << file_path <<" exits" << endl;
            return;
        }
        else
            itInt->second->DeleteKey(data.INTEGER);
    }
    else if (data.type == TYPE_FLOAT)
    {
        floatMap::iterator itFloat = indexFloatMap.find(file_path);
        if (itFloat == indexFloatMap.end())
        {
            // cout << "Error:in search index, no index " << file_path <<" exits" << endl;
            return;
        }
        else
            itFloat->second->DeleteKey(data.POINT);
    }
    else
    {
        stringMap::iterator itString = indexStringMap.find(file_path);
        if (itString == indexStringMap.end())
        {
            // cout << "Error:in search index, no index " << file_path <<" exits" << endl;
            return;
        }
        else
            itString->second->DeleteKey(data.WORD);
    }
    return;
}

// TODO: 支持search range功能 6.22

void IndexManager::SearchRange(std::string file_path, DATA data1, DATA data2, std::vector<int> &vals)
{
    int flag = 0;
    //检测数据类型是否匹配
    if (data1.type == -2)
    {
        flag = 1;
    }
    else if (data2.type == -2)
    {
        flag = 2;
    }
    /*
    else if (data1.type != data2.type) {
        // cout << "ERROR: in searchRange: Wrong data type!" << endl;
        return;
    }
     */

    if (data1.type == TYPE_INT)
    {
        intMap::iterator itInt = indexIntMap.find(file_path);
        if (itInt == indexIntMap.end())
        {
            // cout << "Error:in search index, no index " << file_path <<" exits" << endl;
            return;
        }
        else
            itInt->second->SearchRange(data1.INTEGER, data2.INTEGER, vals, flag);
    }
    else if (data1.type == TYPE_FLOAT)
    {
        floatMap::iterator itFloat = indexFloatMap.find(file_path);
        if (itFloat == indexFloatMap.end())
        {
            // cout << "Error:in search index, no index " << file_path <<" exits" << endl;
            return;
        }
        else
            itFloat->second->SearchRange(data1.POINT, data2.POINT, vals, flag);
    }
    else
    {
        stringMap::iterator itString = indexStringMap.find(file_path);
        if (itString == indexStringMap.end())
        {
            // cout << "Error:in search index, no index " << file_path <<" exits" << endl;
            return;
        }
        else
            itString->second->SearchRange(data1.WORD, data2.WORD, vals, flag);
    }
}