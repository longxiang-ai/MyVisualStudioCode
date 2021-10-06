#include <stdio.h>
#include <math.h>
int mypower(int m, int n)
{
    int ret = m;
    while (--n)
    {
        ret *= m;
    }
    return ret;
}

int isprime(int n)
{
    for (int i = 2; i <= n / 2 + 1; i++)
    {
        if (n % i == 0)
        {
            return 0;
        }
    }
    return 1;
}
int main()
{
    int n = 0;
    int count = 0;
    scanf("%d", &n);
    for (int i = 2; i <= n; i++)
    {
        if (isprime(mypower(2, i) - 1))
        {
            printf("%10d", mypower(2, i) - 1);
            count++;
        }
    }
    printf("count = %d", count);
}