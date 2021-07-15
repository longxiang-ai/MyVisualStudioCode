#include <stdio.h>

int n;
int possible = 0;

int NumOfOne(char *str)
{
    int num_of_one = 0;
    for (int i = 0; i < n; i++)
    {
        if (str[i] == '1')
        {
            num_of_one++;
        }
    }
    return num_of_one;
}

void dfs(int x, char *str, int num_of_one)
{
    // 如果已经找到一个possible的解，则直接return
    if (possible)
    {
        return;
    }
    if (x == n) //递归结束条件
    {
        // 遍历的数目不合适，直接return
        if (NumOfOne(str) != num_of_one)
        {
            return;
        }

        // 从A[2] ? A[1] + A[0]开始穷举
        int flag = 1;
        for (int i = 2; i < n; i++)
        {
            if (str[i] - '0' == str[i - 1] - '0' + str[i - 2] - '0')
            {
                flag = 0;
            }
        }
        if (flag)
        {
            printf("A possible solution:%s \n", str);
        }
        possible = flag;
        return;
    }
    else // 简单枚举
    {
        str[x] = '0';
        dfs(x + 1, str, num_of_one);
        str[x] = '1';
        dfs(x + 1, str, num_of_one);
    }
}

int main()
{
    scanf("%d", &n);
    char str[n];
    scanf("%s", str);
    // 统计1和0的个数
    int num_of_one = NumOfOne(str);
    int num_of_zero = n - num_of_one;
    printf("num of zero:%d, num of one:%d\n", num_of_zero, num_of_one);
    // 思路：列举n位的每一种情况，判断是否满足性质A[i+2] = A[i+1] + A[i],只要有某一位满足则这种情况不符合条件
    // 只需要构建一个字符串满足0,1的个数和上面的个数相同即可,即选择n位里面有a = num_of_zero位是0，其余位是1
    // C_n^a 种可能性,只需要用dfs即可
    if (n <= 2)
    {
        possible = 1;
    }
    else
    {
        char temp[n + 1];
        dfs(0, temp, num_of_one);
    }

    if (possible)
    {
        printf("possible");
    }
    else
    {
        printf("impossible");
    }
}