#include <stdio.h>

#define MAXN 10
#define MAXS 1000

int need_time(const int time[], const int score[], int happy_score, int n);

int main()
{
    int n, i, happy_score;
    int time[MAXN], score[MAXN];
    scanf("%d %d", &n, &happy_score);
    for (i = 0; i < n; ++i)
        scanf("%d", &time[i]);
    for (i = 0; i < n; ++i)
        scanf("%d", &score[i]);
    printf("%d\n", need_time(time, score, happy_score, n));
    return 0;
}

#define max(x, y) (x) >= (y) ? (x) : (y)
int need_time(const int time[], const int score[], int happy_score, int n)
{
    // 由于总时间是给定的，这个问题从反面思考可以看做是一个0、1背包问题
    // 即，先选择不需要做的题，让这些题的总分数<= total_score - happy_score (volume)
    // 求这些不需要做的最大总时间 not_time
    // 最终所得的需要的时间即 total_time - not_time
    int total_time = 0;
    int total_score = 0;
    // 先分别计算总分数和总时间
    for (int i = 0; i < n; i++)
    {
        total_score += score[i];
        total_time += time[i];
    }
    // 如果全做了还不够happy_score
    if (total_score < happy_score)
        return -1;
    // 求背包的总体积volume
    int volume = total_score - happy_score;

    // 求将这些volume装满所能容纳的最大时间
    // 这里用数组int bag[i][j] 来更新背包里的最大时间
    // 其中1 <= i <= n, 1<= j <= volume
    // 初始化bag[0][x] bag[y][0]的值全部为0
    int bag[n + 1][volume + 1];
    for (int i = 0; i < volume + 1; i++)
    {
        bag[0][i] = 0;
    }
    for (int i = 0; i < n + 1; i++)
    {
        bag[i][0] = 0;
    }
    // bag[i][j]的含义是，只能使用前i个物品，装满容量为j的空间，所能容纳的最大时间
    for (int i = 1; i < n + 1; i++)
    {
        for (int j = 1; j < volume + 1; j++)
        {
            // 核心步骤
            // 当前格子的最大时间 = max(不选择装i,选装i)
            // 如果选择装第i个物品，那么此时的总时间 = 第i个物品的时间(time[i-1]) + bag[i-1][now_volume - score[i-1]]
            // 如果选择不装第i个物品，那么此时的总时间 = bag[i-1][now_volume]
            if (j >= score[i - 1]) // 如果能装下第i个物品
                bag[i][j] = max(time[i - 1] + bag[i - 1][j - score[i - 1]], bag[i - 1][j]);
            else // 如果装不下第i个物品，则直接就是继承只装前i-1个的值
                bag[i][j] = bag[i - 1][j];
            // printf("%d ", bag[i][j]);
        }
    }
    // printf("total time = %d ", total_time);
    // printf("total score = %d ", total_score);
    // printf("volume = %d ", volume);
    int final_need_time = total_time - bag[n][volume];
    if (final_need_time == 0)
        return -1;
    return final_need_time;
}

// 6 121

// 84 87 78 16 94 38
// 87 93 50 22 63 28
// 125