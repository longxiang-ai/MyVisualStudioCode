// 参考程序框架
#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;
//定义结构体
struct student
{
    int num;
    string name;
    double score;
};
int main()
{
    // 学生信息
    student stu[5] = {1, "张三", 60, 2, "李四", 70, 3, "王五", 80, 4, "小明", 90, 5, "小红", 100};
    // 创建二进制文件流对象
    fstream iofile("student.dat", ios::in | ios::out | ios::binary);
    // 未正常打开
    if (!iofile)
    {
        cerr << "open error!" << endl;
        abort();
    }
    //向文件中写入5个学生数据
    for (int i = 0; i < 5; i++)
    {
        iofile.write((char *)&stu[i], sizeof(stu[i]));
    }

    student stud1[5];
    for (int i = 0; i < 5; i = i + 2)
    {
        iofile.seekg(i * sizeof(stu[i]), ios::beg);
        iofile.read((char *)&stud1[i / 2], sizeof(stud1[0]));
        cout << stud1[i / 2].num << " " << stud1[i / 2].name << " " << stud1[i / 2].score << endl;
    }
    cout << endl;

    //修改数据
    stu[2].num = 303;
    stu[2].name = "小华";
    stu[2].score = 60;
    //定位
    iofile.seekp(2 * sizeof(stu[0]), ios::beg);
    //写入新数据
    iofile.write((char *)&stu[2], sizeof(stu[2]));
    iofile.seekg(0, ios::beg);
    cout << endl;
    //读出所有数据
    for (int i = 0; i < 5; i++)
    {
        iofile.read((char *)&stu[i], sizeof(stu[i]));
        cout << stu[i].num << " " << stu[i].name << " " << stu[i].score << endl;
    }
    iofile.close();
    return 0;
}
// outputs are like this
// 1 张三 60  
// 3 王五 80  
// 5 小红 100 


// 1 张三 60  
// 2 李四 70  
// 303 小华 60
// 4 小明 90
// 5 小红 100