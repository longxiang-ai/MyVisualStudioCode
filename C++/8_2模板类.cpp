#include <iostream>
using namespace std;
//类模板
template <class T>
class vector
{
public:
    void sort(T a[], int n);       //排序
    void reverse(T a[], int n);    //倒置
    T sum(T a[], int n);           //求和
    int search(T e, T a[], int n); //查找
};
//排序
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
                // 冒泡排序
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
//求和
template <class T>
T vector<T>::sum(T a[], int n)
{
    T sum = a[0];
    for (int i = 1; i < n; i++)
        sum += a[i];
    return sum;
}
//查找
template <class T>
int vector<T>::search(T e, T a[], int n)
{
    for (int i = 0; i < n; i++)
        if (a[i] == e)
            return i;
    // 若没有查找到元素，则返回-1
    return -1;
}
int main()
{
    int data[5] = {3, 1, 4, 2, 5};
    vector<int> obj;
    cout << "数组和为：" << obj.sum(data, 5) << endl;
    cout << "数字4在数组中的位置是：" << obj.search(4, data, 5) << endl;
    cout << "排序前数组各元素为：" << endl;
    for (int i = 0; i < 5; i++)
        cout << data[i] << " " << endl;
    obj.sort(data, 5);
    cout << "排序后数组各元素为：" << endl;
    for (int i = 0; i < 5; i++)
        cout << data[i] << " " << endl;
    obj.reverse(data, 5);
    cout << "倒置后数组各元素为：" << endl;
    for (int i = 0; i < 5; i++)
        cout << data[i] << " " << endl;

    cout << "data2:" << endl;
    double data2[5] = {0.4, 0.5, 0.2, 0.3, 0.1};
    vector<double> obj2;
    cout << "数组和为：" << obj2.sum(data2, 5) << endl;
    cout << "数字0.4在数组中的位置是：" << obj2.search(0.4, data2, 5) << endl;
    cout << "排序前数组各元素为：" << endl;
    for (int i = 0; i < 5; i++)
        cout << data2[i] << " " << endl;
    obj2.sort(data2, 5);
    cout << "排序后数组各元素为：" << endl;
    for (int i = 0; i < 5; i++)
        cout << data2[i] << " " << endl;
    obj2.reverse(data2, 5);
    cout << "倒置后数组各元素为：" << endl;
    for (int i = 0; i < 5; i++)
        cout << data2[i] << " " << endl;
    return 0;
}
// output:
// 数组和为：15
// 数字4在数组中的位置是：2
// 排序前数组各元素为：    
// 3 
// 1 
// 4 
// 2 
// 5 
// 排序后数组各元素为：
// 1
// 2
// 3
// 4
// 5
// 倒置后数组各元素为：
// 5
// 4
// 3
// 2
// 1
// data2:
// 数组和为：1.5
// 数字0.4在数组中的位置是：0
// 排序前数组各元素为：
// 0.4
// 0.5
// 0.2
// 0.3
// 0.1
// 排序后数组各元素为：
// 0.1
// 0.2
// 0.3
// 0.4
// 0.5
// 倒置后数组各元素为：
// 0.5
// 0.4
// 0.3
// 0.2
// 0.1