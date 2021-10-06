#include <stdio.h>
#include <math.h>
#include <string.h>
int isnum(char ch)
{
    if (ch >= '0' && ch <= '9')
    {
        // printf("is a num");
        return 1;
    }
    else
    {
        // printf("not a num");
        return 0;
    }
}

void num_to_alpha(char *num)
{
    int n = 0;
    sscanf(num, "%d", &n);
    char out[10];
    int i = 0;
    for (i = 0; i < 10; i++)
    {
        out[i] = '\0';
    }
    i = 0;
    while (n)
    {
        out[i++] = n % 26 + 'A' - 1;
        n /= 26;
    }
    while (i--)
    {
        printf("%c", out[i]);
    }
    return;
}

void alpha_to_num(char *alpha)
{
    // printf("%s", alpha);
    int length = strlen(alpha);
    long sum = 0;
    for (int i = length - 1; i >= 0; i--)
    {
        sum += (alpha[i] - 'A' + 1) * pow(26, length - i - 1);
    }
    printf("%d", sum);
    return;
}
int main()
{
    char num[10];
    // while (scanf("%s", &num) != EOF)
    while (gets(num))
    {
        // #作为结束标志
        // printf("num[0] = %c", num[0]);
        if (num[0] == '#')
        {
            break;
        }
        else // 没结束的情况下，如果是数字转为字母，如果是字母转为数字，实际上是一个进制转换问题
        {
            if (isnum(num[0]))
            {
                // printf("is num to ->");
                num_to_alpha(num);
            }
            else
            {
                alpha_to_num(num);
            }
            printf("\n");
        }
    }
}