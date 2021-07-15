// �ο�������
#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;
//����ṹ��
struct student
{
    int num;
    string name;
    double score;
};
int main()
{
    // ѧ����Ϣ
    student stu[5] = {1, "����", 60, 2, "����", 70, 3, "����", 80, 4, "С��", 90, 5, "С��", 100};
    // �����������ļ�������
    fstream iofile("student.dat", ios::in | ios::out | ios::binary);
    // δ������
    if (!iofile)
    {
        cerr << "open error!" << endl;
        abort();
    }
    //���ļ���д��5��ѧ������
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

    //�޸�����
    stu[2].num = 303;
    stu[2].name = "С��";
    stu[2].score = 60;
    //��λ
    iofile.seekp(2 * sizeof(stu[0]), ios::beg);
    //д��������
    iofile.write((char *)&stu[2], sizeof(stu[2]));
    iofile.seekg(0, ios::beg);
    cout << endl;
    //������������
    for (int i = 0; i < 5; i++)
    {
        iofile.read((char *)&stu[i], sizeof(stu[i]));
        cout << stu[i].num << " " << stu[i].name << " " << stu[i].score << endl;
    }
    iofile.close();
    return 0;
}
// outputs are like this
// 1 ���� 60  
// 3 ���� 80  
// 5 С�� 100 


// 1 ���� 60  
// 2 ���� 70  
// 303 С�� 60
// 4 С�� 90
// 5 С�� 100