#include <iostream>
using namespace std;
//��ģ��
template <class T>
class vector
{
public:
    void sort(T a[], int n);       //����
    void reverse(T a[], int n);    //����
    T sum(T a[], int n);           //���
    int search(T e, T a[], int n); //����
};
//����
template <class T>
void vector<T>::sort(T a[], int n)
{
    T temp;
    bool exchange;
    for (int i = 1; i < n; i++)
    {
        exchange = false;
        for (int j = n - 1; j >= i; j--)
            if (a[j] < a[j - 1])
            {
                // ð������
                temp = a[j];
                a[j] = a[j - 1];
                a[j - 1] = temp;
                exchange = true;
            }
        if (!exchange)
            return;
    }
}
template <class T>
void vector<T>::reverse(T a[], int n)
{
    T temp;
    for (int i = 0; i <= n / 2; i++)
    {
        temp = a[i];
        a[i] = a[n - 1 - i];
        a[n - 1 - i] = temp;
    }
}
//���
template <class T>
T vector<T>::sum(T a[], int n)
{
    T sum = a[0];
    for (int i = 1; i < n; i++)
        sum += a[i];
    return sum;
}
//����
template <class T>
int vector<T>::search(T e, T a[], int n)
{
    for (int i = 0; i < n; i++)
        if (a[i] == e)
            return i;
    // ��û�в��ҵ�Ԫ�أ��򷵻�-1
    return -1;
}
int main()
{
    int data[5] = {3, 1, 4, 2, 5};
    vector<int> obj;
    cout << "�����Ϊ��" << obj.sum(data, 5) << endl;
    cout << "����4�������е�λ���ǣ�" << obj.search(4, data, 5) << endl;
    cout << "����ǰ�����Ԫ��Ϊ��" << endl;
    for (int i = 0; i < 5; i++)
        cout << data[i] << " " << endl;
    obj.sort(data, 5);
    cout << "����������Ԫ��Ϊ��" << endl;
    for (int i = 0; i < 5; i++)
        cout << data[i] << " " << endl;
    obj.reverse(data, 5);
    cout << "���ú������Ԫ��Ϊ��" << endl;
    for (int i = 0; i < 5; i++)
        cout << data[i] << " " << endl;

    cout << "data2:" << endl;
    double data2[5] = {0.4, 0.5, 0.2, 0.3, 0.1};
    vector<double> obj2;
    cout << "�����Ϊ��" << obj2.sum(data2, 5) << endl;
    cout << "����0.4�������е�λ���ǣ�" << obj2.search(0.4, data2, 5) << endl;
    cout << "����ǰ�����Ԫ��Ϊ��" << endl;
    for (int i = 0; i < 5; i++)
        cout << data2[i] << " " << endl;
    obj2.sort(data2, 5);
    cout << "����������Ԫ��Ϊ��" << endl;
    for (int i = 0; i < 5; i++)
        cout << data2[i] << " " << endl;
    obj2.reverse(data2, 5);
    cout << "���ú������Ԫ��Ϊ��" << endl;
    for (int i = 0; i < 5; i++)
        cout << data2[i] << " " << endl;
    return 0;
}
// output:
// �����Ϊ��15
// ����4�������е�λ���ǣ�2
// ����ǰ�����Ԫ��Ϊ��    
// 3 
// 1 
// 4 
// 2 
// 5 
// ����������Ԫ��Ϊ��
// 1
// 2
// 3
// 4
// 5
// ���ú������Ԫ��Ϊ��
// 5
// 4
// 3
// 2
// 1
// data2:
// �����Ϊ��1.5
// ����0.4�������е�λ���ǣ�0
// ����ǰ�����Ԫ��Ϊ��
// 0.4
// 0.5
// 0.2
// 0.3
// 0.1
// ����������Ԫ��Ϊ��
// 0.1
// 0.2
// 0.3
// 0.4
// 0.5
// ���ú������Ԫ��Ϊ��
// 0.5
// 0.4
// 0.3
// 0.2
// 0.1