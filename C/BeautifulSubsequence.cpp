#include <stdio.h>
#include <math.h>
#define abs(n) ((n) > 0 ? (n) : -1 * (n))
long long int DP(const int sequence[], int m, int n);
int main()
{
    int n, m;
    scanf("%d %d", &n, &m);
    int sequence[n] = {-1};
    // 读入序列
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &sequence[i]);
    }
    long long int num_of_subsequence = DP(sequence, m, n);
    printf("%d ", num_of_subsequence % 1000000007);
    printf("%d", num_of_subsequence);
}
long long int DP(const int sequence[], int m, int n)
{
    // num_{i+1} = num_{i} + \sum_{k = 0}^{k = i} a_k
    // a_k = (abs(s[k]-s[i+1])<= m) ? num_{i-1} : 2^k

    //initialize
    long long int num[n + 1] = {0};
    for (int i = 1; i < n; i++)
    {
        num[i] = num[i - 1];
        for (int k = 0; k < i; k++)
        {
            num[i] += (abs(sequence[i] - sequence[k]) <= m) ? pow(2, k) : num[k];
        }
    }
    return num[n - 1];
}