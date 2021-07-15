#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define nums 10000

int a[nums + 1][nums + 1];

void magic_square(int n)
{

    int i = 1, j = (1 + n) / 2;
    a[i][j] = 1;
    for (int value = 2; value <= n * n; value++)
    {
        i -= 1; //当前元素，放在之前元素的上一行，右侧一列，有如下几种特殊情况
        j += 1;
        if (i < 1 && j > n)
        { //如果当前元素在右上角则，存放在前一元素下一行同一列
            i += 2;
            j -= 1;
        }
        else
        {
            if (i < 1)
            { // 如果当前元素是第一行，则将其放在最后一行，前一元素右侧一列
                i = n;
            }
            if (j > n)
            { //如果当前元素是最右的一列，则放在第一列，前一元素上一行
                j = 1;
            }
        }
        if (a[i][j] == 0)
        { //如果在原来的位置上有值则放在前一元素下一行，同一列
            a[i][j] = value;
        }
        else
        {
            i += 2;
            j -= 1;
            a[i][j] = value;
        }
    }
}
int main()
{
    int N, M;
    scanf("%d %d", &N, &M);
    magic_square(N);
    int x, y;
    for (int i = 0; i < M; i++)
    {
        scanf("%d %d", &x, &y);
        printf("%d\n", a[x][y]);
    }
}
