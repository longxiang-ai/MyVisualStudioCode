#include <iostream>
#include <queue>
#include <vector>
using namespace std;
int main()
{
    // 读取输入的数字个数以及容量
    int num, capacity;
    cin >> num >> capacity;
    // 考虑到这个过程是模仿从缓冲区读取数据的过程，因此这里直接用C++的队列来维护
    // 这样可以省去维护前后两个索引
    int elements[100000];
    priority_queue<int, vector<int>, greater<int>> queue;

    // 先读入需要排序的数字
    for (int i = 0; i < num; i++)
    {
        cin >> elements[i];
    }

    // 再将容量为capacity的queue（注意这里已经帮助我们排好序了）先装满
    // 按顺序先将前capacity个元素塞进去
    for (int i = 0; i < capacity; i++)
    {
        queue.push(elements[i]);
    }
    // 接下来对剩下的元素进行处理
    // 新建一个新的队列来装被排除第一轮的元素
    priority_queue<int, vector<int>, greater<int>> out;
    // 从下一个元素开始
    int j = 0;               // j用来记录当前处理到的元素的位置
    vector<int> output[500]; // 假设不会超过500行
    for (int i = capacity; i < num; i++)
    {
        // 如果这个元素比当前队列的最小值要大，则把这个值进行替换
        if (queue.top() < elements[i])
        {
            queue.push(elements[i]);
            cout << "elements[i] pushed" << elements[i] << endl;
        }
        else // 否则就Out了
        {
            out.push(elements[i]);
        }

        output[j].push_back(queue.top());
        queue.pop();

        // 判断是不是已经空了，如果空了的话那么把out中的元素送过来
        // 即完成下一个区的接力
        if (queue.empty())
        {
            while (!out.empty())
            {
                queue.push(out.top());
                out.pop();
            }
            j++; // 完成了一个区
        }
    }
    // 退出该层循环之后，代表输入的元素已经都被处理了，接下来只需要将queue和out的元素全部清空到output中，进行输出即可
    // 先清空queue
    while (!queue.empty())
    {
        output[j].push_back(queue.top());
        queue.pop();
        // 再清空out
        if (queue.empty())
        {
            while (!out.empty())
            {
                queue.push(out.top());
                out.pop();
            }
            j++;
        }
    }

    for (int i = 0; i < j; i++)
    {
        for (int k = 0; k < output[i].size(); k++)
        {
            if (k != 0)
            {
                cout << " ";
            }
            cout << output[i][j];
        }
        cout << endl;
    }
}