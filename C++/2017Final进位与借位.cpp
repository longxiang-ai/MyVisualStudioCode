#include <iostream>
using namespace std;
class Group
{
public:
    virtual int add(int x, int y) = 0; //输出加法的运算结果
    virtual int sub(int x, int y) = 0; //输出减法的运算结果
};

// 均能正确计算
class GroupA : public Group
{
public:
    int add(int x, int y)
    {
        return x + y;
    }
    int sub(int x, int y)
    {
        return x - y;
    }
};

class GroupB : public Group
{
public:
    int add(int x, int y)
    {
        return x + y;
    }
    int sub(int x, int y)
    {
        // 提取各位
        int x1[4] = {0};
        int x2[4] = {0};
        int i = 0, j = 0;
        do
        {
            x1[i++] = x % 10;
            x2[j++] = y % 10;
            x /= 10;
            y /= 10;
        } while (x || y);

        int n = i, carry = 1, sum = 0;
        for (int k = 0; k < n; k++)
        {
            // 忘记借位
            if (x1[k] < x2[k])
            {
                sum = sum + carry * (10 + x1[k] - x2[k]);
            }
            else
            {
                sum = sum + carry * (x1[k] - x2[k]);
            }
            carry *= 10;
        }

        return sum;
    }
};

class GroupC : public Group
{
public:
    int add(int x, int y)
    {
        // 提取各位
        int x1[4] = {0};
        int x2[4] = {0};
        int i = 0, j = 0;
        do
        {
            x1[i++] = x % 10;
            x2[j++] = y % 10;
            x /= 10;
            y /= 10;
        } while (x || y);

        int n = i, carry = 1, sum = 0;
        for (int k = 0; k < n; k++)
        {
            // 忘记进位
            if (x1[k] + x2[k] > 9)
            {
                sum += carry * (x1[k] + x2[k] - 10);
            }
            else
            {
                sum += carry * (x1[k] + x2[k]);
            }
            carry *= 10;
        }

        return sum;
    }
    int sub(int x, int y)
    {
        // 提取各位
        int x1[4] = {0};
        int x2[4] = {0};
        int i = 0, j = 0;
        do
        {
            x1[i++] = x % 10;
            x2[j++] = y % 10;
            x /= 10;
            y /= 10;
        } while (x || y);

        int n = i, carry = 1, sum = 0;
        for (int k = 0; k < n; k++)
        {
            // 忘记借位
            if (x1[k] < x2[k])
            {
                sum = sum + carry * (10 + x1[k] - x2[k]);
            }
            else
            {
                sum = sum + carry * (x1[k] - x2[k]);
            }
            carry *= 10;
        }

        return sum;
    }
};

int main()
{
    int n;
    cin >> n;
    int stutype[n];
    for (int i = 0; i < n; i++)
    {
        cin >> stutype[i];
    }
    while (true)
    {
        int index;
        cin >> index;
        if (index == 0)
        {
            break;
        }
        index--;
        int x, y;
        char op;
        cin >> x >> op >> y;

        if (stutype[index] == 1)
        {
            GroupA stu;
            if (op == '+')
            {
                cout << stu.add(x, y) << endl;
            }
            else if (op == '-')
            {
                cout << stu.sub(x, y) << endl;
            }
        }
        else if (stutype[index] == 2)
        {
            GroupB stu;
            if (op == '+')
            {
                cout << stu.add(x, y) << endl;
            }
            else if (op == '-')
            {
                cout << stu.sub(x, y) << endl;
            }
        }
        else if (stutype[index] == 3)
        {
            GroupC stu;
            if (op == '+')
            {
                cout << stu.add(x, y) << endl;
            }
            else if (op == '-')
            {
                cout << stu.sub(x, y) << endl;
            }
        }
    }
}