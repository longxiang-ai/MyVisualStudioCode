#ifndef _BASIC_H_
#define _BASIC_H_ 1
#include <iostream>
#include <vector>

//关系基本元素（大小关系）
typedef enum
{
	EQUAL,
	NOT_EQUAL,
	LESS,
	LESS_OR_EQUAL,
	GREATER,
	GREATER_OR_EQUAL,
} WHERE;

//定义数据(数据类型(-1为整数；0为浮点数；1为字符串)，具体数据)
struct DATA
{
	int type;
	int INTEGER;
	float POINT;
	std::string WORD;
};

//定义关系(数据、关系)
struct RELATION
{
	DATA data;
	WHERE relation;
};

//属性（最多32个）
struct ATTRIBUTE
{
	int num;			  //属性数目
	short primarykey;	  //主键设置（-1代表无主键）
	std::string name[32]; //属性名称
	short type[32];		  //属性类型
	bool unique[32];	  //是否unique
	bool index[32];		  //是否有索引
};

//索引（至多十个）
struct INDEX
{
	int num;					//索引数量
	short position[10];			//哪些属性是索引
	std::string index_name[10]; //每个索引的名字
};

//元组
class TUPLE
{
private:
	std::vector<DATA> data; //每个元组中的信息
	bool is_deleted;		//是否被删
public:
	TUPLE();						   //构建元组
	TUPLE(const TUPLE &tuple_in);	   //复制元组
	void addData(DATA data_in);		   //新增数据
	std::vector<DATA> getData() const; //返回元组中数据
	int getSize();					   //返回元组大小
	bool isDeleted();				   //返回删除位
	void setDeleted();				   //设置删除位
	void showTuple();				   //显示元组中所有数据
};

//关系表
class TABLE
{
private:
	std::string title;		  //表名
	std::vector<TUPLE> tuple; //所有的元组
	INDEX index;			  //表的索引
public:
	ATTRIBUTE attr;							  //表的属性
	TABLE();								  //构造函数
	TABLE(std::string title, ATTRIBUTE attr); //建立表
	TABLE(const TABLE &table_in);			  //复制表
	bool addTuple(TUPLE tuple_in);			  //添加元组

	bool setIndex(short position, std::string index_name); //添加索引
	int dropIndex(std::string index_name);				   //删除索引

	std::string getTitle();			//返回标题
	ATTRIBUTE getAttr();			//返回属性
	std::vector<TUPLE> &getTuple(); //返回元组
	INDEX getIndex();				//返回索引
	//short gethasKey();

	void showTable();				  //显示表中所有数据
	void showTable(int up, int down); //显示表中部分数据
};

//TUPLE函数

//复制元组
TUPLE::TUPLE(const TUPLE &tuple_in)
{
	for (int index = 0; index < tuple_in.data.size(); index++)
	{
		this->data.push_back(tuple_in.data[index]);
	}
}

//返回元组大小
inline int TUPLE::getSize()
{
	return (int)data.size();
}

//写数据
void TUPLE::addData(DATA data_in)
{
	this->data.push_back(data_in);
}

//返回元组删除位
bool TUPLE::isDeleted()
{
	return is_deleted;
}

//设置元组删除位
void TUPLE::setDeleted()
{
	is_deleted = true;
}

//返回元组数据
std::vector<DATA> TUPLE::getData() const
{
	return this->data;
}

//打印元组中数据
void TUPLE::showTuple()
{
	for (int index = 0; index < getSize(); index++)
	{
		if (data[index].type == -1) //type=1时输出整形
			std::cout << data[index].INTEGER << '\t';
		else if (data[index].type == 0) //type=0时输出浮点型
			std::cout << data[index].POINT << '\t';
		else
		{
			// TODO: ?????????
			std::cout << data[index].WORD << '\t'; //type为其他输出字符串
		}
	}
	std::cout << std::endl;
}

//TABLE函数

//构造函数(表名，属性，索引数设为0)
TABLE::TABLE(std::string title_i, ATTRIBUTE attr_i)
{
	this->title = title_i;
	this->attr = attr_i;
	this->index.num = 0;
}

//复制关系表
TABLE::TABLE(const TABLE &table_in)
{
	this->attr = table_in.attr;
	this->index = table_in.index;
	this->title = table_in.title;
	for (int index = 0; index < tuple.size(); index++)
		this->tuple.push_back(table_in.tuple[index]);
}

//添加元组
bool TABLE::addTuple(TUPLE tuple_in)
{
	//检查元组大小相等
	if (tuple_in.getSize() != attr.num)
	{
		std::cout << "illegal Tuple insert:The size of tuple is NOT_EQUAL" << std::endl;
		return false;
	}
	//检查各属性相同
	for (int index = 0; index < attr.num; index++)
	{
		if (tuple_in.getData()[index].type > attr.type[index] || (tuple_in.getData()[index].type <= 0 && tuple_in.getData()[index].type != attr.type[index])) //int，float必须相等
		{
			std::cout << "illegal Tuple insert:The type of attribute is NOT_EQUAL" << std::endl;
			return 0;
		}
	}
	tuple.push_back(tuple_in);
	return true;
}

//添加索引
bool TABLE::setIndex(short index_in, std::string index_name)
{
	short tmpIndex;
	for (tmpIndex = 0; tmpIndex < index.num; tmpIndex++)
	{
		if (index_in == index.position[tmpIndex]) //当该元素已经有索引时，报错
		{
			std::cout << "Illegal Set Index: The index has been in the table." << std::endl;
			return false;
		}
	}
	for (tmpIndex = 0; tmpIndex < index.num; tmpIndex++)
	{
		if (index_name == index.index_name[tmpIndex]) //当该元素已经有索引时，报错
		{
			std::cout << "Illegal Set Index: The name has been used." << std::endl;
			return false;
		}
	}
	index.position[index.num] = index_in; //插入索引位置和索引名字，最后把索引个数加一
	index.index_name[index.num] = index_name;
	index.num++;
	return true;
}

int TABLE::dropIndex(std::string index_name)
{
	short tmpIndex;
	//遍历索引
	for (tmpIndex = 0; tmpIndex < index.num; tmpIndex++)
	{
		if (index_name == index.index_name[tmpIndex])
			break;
	}
	//无此索引
	if (tmpIndex == index.num)
	{
		std::cout << "illegal Drop Index: No such a index in the table." << std::endl;
		return 0;
	}
	//有该索引
	index.index_name[tmpIndex] = index.index_name[index.num - 1];
	index.position[tmpIndex] = index.position[index.num - 1];
	index.num--;
	return 1;
}
//返回标题
std::string TABLE::getTitle()
{
	return title;
}
//返回属性
ATTRIBUTE TABLE::getAttr()
{
	return attr;
}
//返回元组
std::vector<TUPLE> &TABLE::getTuple()
{
	return tuple;
}
//返回索引
INDEX TABLE::getIndex()
{
	return index;
}
//打印关系表
void TABLE::showTable()
{
	for (int index = 0; index < attr.num; index++)
		// TODO: ?????????
		std::cout << attr.name[index] << '\t';
	std::cout << std::endl;
	for (int index = 0; index < tuple.size(); index++)
		tuple[index].showTuple();
}
//打印第down行到第up行元组
void TABLE::showTable(int up, int down)
{
	for (int index = 0; index < attr.num; index++)
		// TODO: ?????????
		std::cout << attr.name[index] << '\t';
	std::cout << std::endl;
	for (int index = down; index < up && index < tuple.size(); index++)
		tuple[index].showTuple();
}
#endif
