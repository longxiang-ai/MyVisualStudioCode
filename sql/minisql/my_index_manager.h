#include <sstream>
#include <string>
#include <vector>
#include <map>

// using namespace std;
#include "myBASIC.h"
#include "catalog_manager.h"
#include "mybplustree.h"

class IndexManager
{
public:
    IndexManager(std::string table_name);
    ~IndexManager();

    void CreateIndex(std::string file_path, int type);

    void DropIndex(std::string file_path, int type);

    int SearchIndex(std::string file_path, DATA data);

    void InsertIndex(std::string file_path, DATA data, int block_id);

    void DeleteIndexByKey(std::string file_path, DATA data);

    void SearchRange(std::string file_path, DATA data1, DATA data2, std::vector<int> &vals);

private:
    // TODO: 这三个map 用来干嘛的 ？
    typedef std::map<std::string, mybplustree<int> *> intMap;
    typedef std::map<std::string, mybplustree<std::string> *> stringMap;
    typedef std::map<std::string, mybplustree<float> *> floatMap;

    intMap indexIntMap;
    stringMap indexStringMap;
    floatMap indexFloatMap;

    int static const TYPE_FLOAT = 0;
    int static const TYPE_INT = -1;
    //计算B+树适合的degree
    int GetDegree(int type);

    //计算不同类型Key的size
    int GetKeySize(int type);
};
