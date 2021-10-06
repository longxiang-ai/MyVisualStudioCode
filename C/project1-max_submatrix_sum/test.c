// O(N^3)
int b[1000];
int MSStest()
{
    int max = 0;
    for (int i = 0; i < N; i++)
    {
        memset(b, 0, sizeof(b));
        for (int j = i; j < N; j++)
        {
            int sum = 0;
            for (int k = 0; k < N; k++)
            {
                b[k] += array[j][k];
                sum += b[k];
                if (sum > max)
                {
                    max = sum;
                }
                if (sum < 0)
                {
                    sum = 0;
                }
            }
        }
    }
    return max;
}