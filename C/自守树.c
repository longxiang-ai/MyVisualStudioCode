#include <stdio.h>
#include <string.h>
#include <math.h>
int digit(int n)
{
    int count = 0;
    while (n /= 10)
    {
        count++;
    }
    return ++count;
}
int num_self(int n)
{
    int count = 0;
    for (int i = 0; i <= n; i++)
    {
        int ret = pow(10, digit(i));
        if ((i * i - i) % ret == 0)
        {
            count++;
        }
    }
    return count;
}
int main()
{
    int n = 0, m = 0;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &m);
        if (i != 0)
        {
            printf(" ");
        }
        printf("%d", num_self(m));
    }
}