
#include <bits/stdc++.h>
using namespace std;
const int SIZE = 1005;
int mat[SIZE][SIZE] = {0}, dp[SIZE], Stack[SIZE][SIZE];
vector<int> idToIndex(SIZE, 105), indexToId(SIZE), tips_id[SIZE];
vector<int> temppath, path;
int price[SIZE], n, m, a, b, tempans = 0, ans;
int mx;
void dfs(int N, int num, int step)
{
    if (num == 0)
    {
        if (step > mx || (step == mx && tempans < ans))
        {
            ans = tempans;
            mx = step;
            path = temppath;
        }
        return;
    }
    for (int i = 0; i < num; ++i)
    {
        int k = Stack[step][i];
        if (step + N - k < mx)
            return;
        if (step + dp[k] < mx)
            return;
        int cnt = 0;
        for (int j = i + 1; j < num; ++j)
            if (!mat[k][Stack[step][j]])
                Stack[step + 1][cnt++] = Stack[step][j];
        temppath.push_back(k);
        tempans += price[k];
        dfs(N, cnt, step + 1);
        tempans -= price[k];
        temppath.pop_back();
    }
}
void run(int N)
{
    mx = 0;
    for (int i = N - 1; i >= 0; --i)
    {
        int sz = 0;
        for (int j = i + 1; j < N; ++j)
            if (!mat[i][j])
                Stack[1][sz++] = j;
        temppath.push_back(i);
        tempans += price[i];
        dfs(N, sz, 1);
        tempans -= price[i];
        temppath.pop_back();
        dp[i] = mx;
    }
}
int main()
{
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; ++i)
    {
        scanf("%d %d", &a, &b);
        tips_id[a].push_back(b);
    }
    for (int i = 0; i < m; ++i)
    {
        scanf("%d %d", &a, &price[i]);
        indexToId[i] = a;
        idToIndex[a] = i;
    }
    for (int i = 0; i < m; ++i)
    {
        mat[i][i] = 1;
        for (int j : tips_id[indexToId[i]])
            if (idToIndex[j] < m)
                mat[i][idToIndex[j]] = mat[idToIndex[j]][i] = 1;
    }
    run(m);
    for (int i = 0; i < path.size(); ++i)
        path[i] = indexToId[path[i]];
    sort(path.begin(), path.end());
    printf("%d\n%03d", mx, path[0]);
    for (int i = 1; i < path.size(); ++i)
        printf(" %03d", path[i]);
    printf("\n%d", ans);
}