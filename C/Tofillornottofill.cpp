#include <stdio.h>
typedef struct gasstation
{
    double price;
    int distance;
} gs;

int main()
{
    int Cmax, distance, avg, N;
    scanf("%d %d %d %d", &Cmax, &distance, &avg, &N);
    gs sta[N];
    for (int i = 0; i < N; i++)
    {
        scanf("%lf %d", &(sta[i].price), &(sta[i].distance));
    }
    // 读取完节点信息后，因为节点是乱序的，所以应该按照距离重新排序
    // 这里采用简单的冒泡排序

    int temp1 = 0;
    double temp2 = 0;
    for (int i = 0; i < N - 1; i++)
    {
        for (int j = 0; j < N - 1 - i; j++)
        {
            if (sta[j].distance > sta[j + 1].distance)
            {
                temp1 = sta[j].distance;
                temp2 = sta[j].price;
                sta[j].distance = sta[j + 1].distance;
                sta[j].price = sta[j + 1].price;
                sta[j + 1].distance = temp1;
                sta[j + 1].price = temp2;
            }
        }
    }

    // greedy method 实现条件必须满足 local minimum == globol minimum
    // 关于这个问题，首先需要分析应该把 什么 作为greedy的衡量指标
    // 在能到达终点的前提下，要求的是花费最少的价格
    // 在不能到达终点的情况下，要求的是最远能够行进的距离
    // 首先考虑加油站之间的距离(或最后一个加油站与终点间的距离)如果 > Cmax * avg，那么无论怎么加油都无法到达终点
    // 在这种情况下，只需要在第一个无法到达的位置往后加Cmax * avg 就是所能到达的最远距离了
    // 如果说任意两点间的距离都<= Cmax * avg, 则需要考虑“贪心”的加油策略了
    // 从当前位置出发，如果Cmax * avg范围里面存在比当前位置更便宜的加油站
    // 那么从P出发只需要考虑加油至刚好到最便宜的加油站即可，这样可以最大程度的省钱
    // 如果Cmax * avg范围里面 不 存在比当前位置更便宜的加油站
    // 那么就先加满油，然后找这个范围内最便宜的加油站停靠，考虑下一步如何操作

    // 特殊情况，起点处没有加油站,直接结束
    if (sta[0].distance != 0)
    {
        printf("The maximum travel distance = 0.00\n");
        return 0;
    }
    if (distance == 0)
    {
        printf("0.00\n");
        return 0;
    }

    // initialize
    double tank = 0;          // 目前油箱内油量,注意到这个量并不一定为int
    int index = 0;            // 当前加油站的下标
    double step = Cmax * avg; // 加满油能够探索的最大范围
    double total_cost = 0;    // 总花费

    while (1)
    {
        int hasStation = 0;
        int flagCheaper = 0;
        double MinPrice = 1e6;
        int MinIndex = 0;
        for (int i = index + 1; i < N; i++)
        {
            if (sta[i].distance - sta[index].distance <= step)
            {
                hasStation = 1; // 范围内存在加油站
                double next_price = sta[i].price;
                double now_price = sta[index].price;
                if (next_price <= now_price) // step内的加油站比当前的加油站便宜
                {
                    double this_step = (sta[i].distance - sta[index].distance - tank * avg) / avg; // 计算这一步走消耗的油
                    tank = 0;                                                                      // 更新油量
                    index = i;                                                                     // 更新位置
                    total_cost += this_step * now_price;                                           // 更新总花费
                    flagCheaper = 1;                                                               // 更新标签，作为在范围内找到更便宜的标志
                    break;
                }

                if (sta[i].price < MinPrice)
                {
                    MinPrice = sta[i].price;
                    MinIndex = i;
                }
            }
            else // 范围内没有找到加油站，则退出当前循环
            {
                break;
            }
        }

        if (flagCheaper == 0 && ((distance - sta[index].distance) <= step)) // 如果没有找到更便宜的，且加油一次走的距离足够走到终点了，则证明可以到终点了
        {
            double this_step = distance - sta[index].distance;
            double this_cost = this_step / avg - tank;
            tank = 0;
            total_cost += this_cost * sta[index].price;
            printf("%.2f\n", total_cost);
            return 0;
        }
        if (hasStation && flagCheaper == 0) //如果存在加油站但并不比当前的加油站便宜
        {
            double this_step = Cmax - tank;
            total_cost += this_step * sta[index].price;
            double difference = sta[MinIndex].distance - sta[index].distance; // 最便宜地方的距离和坐标
            tank = Cmax - difference / avg;                                   // 更新油量
            index = MinIndex;                                                 // 更新所在的位置
        }

        else if (hasStation == 0) // 如果在一个step里没找到结点，也没找到终点，那么最大距离就是当前的距离加一步
        {
            printf("The maximum travel distance = %.2f\n", sta[index].distance + step * 1.0);
            break;
        }
    }
}