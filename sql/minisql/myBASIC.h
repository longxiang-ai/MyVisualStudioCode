#ifndef _BASIC_H_
#define _BASIC_H_ 1
#include <iostream>
#include <vector>

//��ϵ����Ԫ�أ���С��ϵ��
typedef enum
{
	EQUAL,
	NOT_EQUAL,
	LESS,
	LESS_OR_EQUAL,
	GREATER,
	GREATER_OR_EQUAL,
} WHERE;

//��������(��������(-1Ϊ������0Ϊ��������1Ϊ�ַ���)����������)
struct DATA
{
	int type;
	int INTEGER;
	float POINT;
	std::string WORD;
};

//�����ϵ(���ݡ���ϵ)
struct RELATION
{
	DATA data;
	WHERE relation;
};

//���ԣ����32����
struct ATTRIBUTE
{
	int num;			  //������Ŀ
	short primarykey;	  //�������ã�-1������������
	std::string name[32]; //��������
	short type[32];		  //��������
	bool unique[32];	  //�Ƿ�unique
	bool index[32];		  //�Ƿ�������
};

//����������ʮ����
struct INDEX
{
	int num;					//��������
	short position[10];			//��Щ����������
	std::string index_name[10]; //ÿ������������
};

//Ԫ��
class TUPLE
{
private:
	std::vector<DATA> data; //ÿ��Ԫ���е���Ϣ
	bool is_deleted;		//�Ƿ�ɾ
public:
	TUPLE();						   //����Ԫ��
	TUPLE(const TUPLE &tuple_in);	   //����Ԫ��
	void addData(DATA data_in);		   //��������
	std::vector<DATA> getData() const; //����Ԫ��������
	int getSize();					   //����Ԫ���С
	bool isDeleted();				   //����ɾ��λ
	void setDeleted();				   //����ɾ��λ
	void showTuple();				   //��ʾԪ������������
};

//��ϵ��
class TABLE
{
private:
	std::string title;		  //����
	std::vector<TUPLE> tuple; //���е�Ԫ��
	INDEX index;			  //�������
public:
	ATTRIBUTE attr;							  //�������
	TABLE();								  //���캯��
	TABLE(std::string title, ATTRIBUTE attr); //������
	TABLE(const TABLE &table_in);			  //���Ʊ�
	bool addTuple(TUPLE tuple_in);			  //���Ԫ��

	bool setIndex(short position, std::string index_name); //�������
	int dropIndex(std::string index_name);				   //ɾ������

	std::string getTitle();			//���ر���
	ATTRIBUTE getAttr();			//��������
	std::vector<TUPLE> &getTuple(); //����Ԫ��
	INDEX getIndex();				//��������
	//short gethasKey();

	void showTable();				  //��ʾ������������
	void showTable(int up, int down); //��ʾ���в�������
};

//TUPLE����

//����Ԫ��
TUPLE::TUPLE(const TUPLE &tuple_in)
{
	for (int index = 0; index < tuple_in.data.size(); index++)
	{
		this->data.push_back(tuple_in.data[index]);
	}
}

//����Ԫ���С
inline int TUPLE::getSize()
{
	return (int)data.size();
}

//д����
void TUPLE::addData(DATA data_in)
{
	this->data.push_back(data_in);
}

//����Ԫ��ɾ��λ
bool TUPLE::isDeleted()
{
	return is_deleted;
}

//����Ԫ��ɾ��λ
void TUPLE::setDeleted()
{
	is_deleted = true;
}

//����Ԫ������
std::vector<DATA> TUPLE::getData() const
{
	return this->data;
}

//��ӡԪ��������
void TUPLE::showTuple()
{
	for (int index = 0; index < getSize(); index++)
	{
		if (data[index].type == -1) //type=1ʱ�������
			std::cout << data[index].INTEGER << '\t';
		else if (data[index].type == 0) //type=0ʱ���������
			std::cout << data[index].POINT << '\t';
		else
		{
			// TODO: ?????????
			std::cout << data[index].WORD << '\t'; //typeΪ��������ַ���
		}
	}
	std::cout << std::endl;
}

//TABLE����

//���캯��(���������ԣ���������Ϊ0)
TABLE::TABLE(std::string title_i, ATTRIBUTE attr_i)
{
	this->title = title_i;
	this->attr = attr_i;
	this->index.num = 0;
}

//���ƹ�ϵ��
TABLE::TABLE(const TABLE &table_in)
{
	this->attr = table_in.attr;
	this->index = table_in.index;
	this->title = table_in.title;
	for (int index = 0; index < tuple.size(); index++)
		this->tuple.push_back(table_in.tuple[index]);
}

//���Ԫ��
bool TABLE::addTuple(TUPLE tuple_in)
{
	//���Ԫ���С���
	if (tuple_in.getSize() != attr.num)
	{
		std::cout << "illegal Tuple insert:The size of tuple is NOT_EQUAL" << std::endl;
		return false;
	}
	//����������ͬ
	for (int index = 0; index < attr.num; index++)
	{
		if (tuple_in.getData()[index].type > attr.type[index] || (tuple_in.getData()[index].type <= 0 && tuple_in.getData()[index].type != attr.type[index])) //int��float�������
		{
			std::cout << "illegal Tuple insert:The type of attribute is NOT_EQUAL" << std::endl;
			return 0;
		}
	}
	tuple.push_back(tuple_in);
	return true;
}

//�������
bool TABLE::setIndex(short index_in, std::string index_name)
{
	short tmpIndex;
	for (tmpIndex = 0; tmpIndex < index.num; tmpIndex++)
	{
		if (index_in == index.position[tmpIndex]) //����Ԫ���Ѿ�������ʱ������
		{
			std::cout << "Illegal Set Index: The index has been in the table." << std::endl;
			return false;
		}
	}
	for (tmpIndex = 0; tmpIndex < index.num; tmpIndex++)
	{
		if (index_name == index.index_name[tmpIndex]) //����Ԫ���Ѿ�������ʱ������
		{
			std::cout << "Illegal Set Index: The name has been used." << std::endl;
			return false;
		}
	}
	index.position[index.num] = index_in; //��������λ�ú��������֣���������������һ
	index.index_name[index.num] = index_name;
	index.num++;
	return true;
}

int TABLE::dropIndex(std::string index_name)
{
	short tmpIndex;
	//��������
	for (tmpIndex = 0; tmpIndex < index.num; tmpIndex++)
	{
		if (index_name == index.index_name[tmpIndex])
			break;
	}
	//�޴�����
	if (tmpIndex == index.num)
	{
		std::cout << "illegal Drop Index: No such a index in the table." << std::endl;
		return 0;
	}
	//�и�����
	index.index_name[tmpIndex] = index.index_name[index.num - 1];
	index.position[tmpIndex] = index.position[index.num - 1];
	index.num--;
	return 1;
}
//���ر���
std::string TABLE::getTitle()
{
	return title;
}
//��������
ATTRIBUTE TABLE::getAttr()
{
	return attr;
}
//����Ԫ��
std::vector<TUPLE> &TABLE::getTuple()
{
	return tuple;
}
//��������
INDEX TABLE::getIndex()
{
	return index;
}
//��ӡ��ϵ��
void TABLE::showTable()
{
	for (int index = 0; index < attr.num; index++)
		// TODO: ?????????
		std::cout << attr.name[index] << '\t';
	std::cout << std::endl;
	for (int index = 0; index < tuple.size(); index++)
		tuple[index].showTuple();
}
//��ӡ��down�е���up��Ԫ��
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
