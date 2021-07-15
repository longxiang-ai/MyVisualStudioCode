#include <stdio.h>
#define true 1
#define false 0
// statement用于存储每个人的发言
int statement[200] = {0};
int wolf[200] = {0};
int wolfindex = -1;
// pre 代表当前被遍历的玩家index(范围[1,N]),为了避免排序，所以直接送pre最大的玩家开始遍历
int CountLen(int array[])
{
    int i = 0;
    int count = 0;
    while (array[i++])
        count++;
    return count;
}

int IsIn(int element, int array[], int Len)
{
    for (int i = 0; i < Len; i++)
    {
        if (element == array[i])
            return true;
    }
    return false;
}
int LiersFit(int wolf[200], int N, int L)
{
    // 判断当前的情况下（此时狼的数目已经确定为M）
    //  at least one but not all the werewolves were lying, and there were exactly L liers.
    // 至少有一只狼说谎，且不是所有狼都说谎，总共有L个人说谎
    int Len = CountLen(wolf);
    int NumOfLiers = 0;
    int NumOfWolfLiers = 0;
    for (int i = 1; i < N + 1; i++)
    {
        // 好人说谎
        if (!IsIn(i, wolf, Len))
        {
            if (statement[i] > 0 && IsIn(statement[i], wolf, Len) || statement[i] < 0 && !IsIn(-statement[i], wolf, Len))
                NumOfLiers++;
        }

        // 狼人说谎
        else
        {
            if (statement[i] > 0 && IsIn(statement[i], wolf, Len) || statement[i] < 0 && !IsIn(-statement[i], wolf, Len))
            {
                NumOfLiers++;
                NumOfWolfLiers++;
            }
        }
    }
    if (NumOfWolfLiers > 0 && NumOfWolfLiers < Len && NumOfLiers == L)
    {
        return true;
    }

    return false;
}
int BackTracking(int N, int M, int L, int pre)
{
    // 如果狼的数量达到要求了，那么就判断是不是满足liers的条件
    if (CountLen(wolf) == M)
    {
        if (LiersFit(wolf, N, L))
        {
            return true;
        }
        else
            return false;
    }
    // 如果狼的数量还没达到M，则从pre开始依照顺序向index小的方向进行遍历
    while (pre > 0)
    {
        // 先假设pre是狼
        wolf[++wolfindex] = pre;
        if (BackTracking(N, M, L, pre - 1))
        {
            // 如果这样假设确实找到了符合条件的狼群，则直接返回true
            return true;
        }
        else
        {
            //如果pre是狼的情况并不符合题意，那么把pre是狼的情况去除掉，然后进入下一层循环
            wolf[wolfindex--] = 0;
        }
        pre--;
    }
    // 如果直至循环结束都没有找到合适的狼群，则证明这种情况下没有解
    return false;
}
int main()
{
    // 读入N,M,L
    int N, M, L;
    scanf("%d %d %d", &N, &M, &L);
    // 读入每个人的发言
    for (int i = 1; i < N + 1; i++)
    {
        scanf("%d", &statement[i]);
    }
    // 通过回溯算法计算出是否有合乎条件的解
    int isFind = BackTracking(N, M, L, N);
    if (isFind)
    {
        printf("%d", wolf[0]);
        for (int i = 1; i < M; i++)
        {
            printf(" %d", wolf[i]);
        }
    }
    else
    {
        printf("No Solution");
    }
}