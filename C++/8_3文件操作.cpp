#include <iostream>
#include <fstream>
using namespace std;

class dog
{
public:
    int weight;
    int age;
    dog()
    {
    }
    dog(int weight1, int age1)
    {
        weight = weight1;
        age = age1;
    }
    ~dog()
    {
    }
};
int main()
{
    dog dog1(5, 10);
    dog dog2;
    ofstream fout;
    ifstream fint;
    fout.open("out.txt");
    fout << dog1.weight << "\n"
         << dog1.age << endl;
    fint.open("out.txt");
    fint >> dog2.weight >> dog2.age;
    cout << dog2.age << " " << dog2.weight << endl;
    fout.close();
    //二进制
    ofstream fdata("file.dat", ios::binary);
    fdata.write((char *)(&dog1), sizeof(dog1));
    ifstream fint1("file.dat", ios::binary);
    fint1.read((char *)(&dog2), sizeof(dog2));
    cout << dog2.age << " " << dog2.weight << endl;
    return 0;
}

// outputs are like this:
// 10 5
// 10 5
// 可以看出，程序输出的结果是相同的，但磁盘文件的ASCII码是不同的。
// 使用二进制方式时，磁盘文件的ASCII码为05 00 00 00 0A 00 00 00
// 使用文本方式时，磁盘文件的ASCII码为05 00 00 00 0D 0A 00 00 00
// 因为文本方式中，系统自动将0A 转换为了0D 0A