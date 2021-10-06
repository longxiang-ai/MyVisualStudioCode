#include <stdio.h>
void check(int array[], int M, int N)
{
    // 对一个长度为N的数列array，其是不是一个栈的pop序列可以由以下的几个步骤进行判断
    // 即模拟其入栈出栈的顺序
}
int main()
{
    int M, N, K;
    // M: the capacity of the stack
    // N: from 1 to N ,we have N numbers in total
    // K: there will be K sequences to be checked
    // scanf("%d %d %d",&M,&N,&K);
    N = 7;
    M = 5;
    K = 1;
    for (int i = 0; i < K; i++)
    {
        int temp[N];
        for (int j = 0; j < N; j++)
        {
            scanf("%d", &temp[j]);
        }
        check(temp, M, N);
    }
    return 0;
}