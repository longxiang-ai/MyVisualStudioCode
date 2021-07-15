#include <stdio.h>
int main()
{
    int n = 0;
    scanf("%d", &n); //读取
    int nums[n] = {0};
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &nums[i]);
    }
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int thissum = 0;
            for (int k = i; k <= j; k++)
            {
                thissum += nums[k];
                if (thissum > sum)
                {
                    sum = thissum;
                }
            }
        }
    }
    printf("%d", sum);
    return 0;
}
