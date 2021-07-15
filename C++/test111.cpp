#include <iostream>
#include <vector>
#include <math.h>
using namespace std;
int a[101];
bool Judge(vector<int> &wolf, int N, int L)
{
    int i, j, w;
    w = 0;
    vector<int> result(N + 1, 1);
    vector<int> liers;
    //-1 rep werewolf 1 rep human
    for (i = 0; i < wolf.size(); i++)
    {
        result[wolf[i]] = -1;
    }
    //search the liers
    for (i = 1; i <= N; ++i)
    {
        int flag = result[i] * i;
        for (j = 1; j <= N; ++j)
        {
            if (a[j] == -1 * flag)
                liers.push_back(j);
        }
    }
    //judge is it correct by L and W
    int l = liers.size();
    if (l == L)
    {
        for (i = 0; i < l; i++)
        {
            if (result[liers[i]] < 0)
                w++;
        }
        if (w > 0 && w < wolf.size())
            return true;
    }
    return false;
}
bool BackTracking(vector<int> &wolf, int N, int M, int L, int k)
{
    //find the enough wolf
    if (wolf.size() == M)
    {
        if (Judge(wolf, N, L))
            return true;
        else
            return false;
    }
    for (; k > 0; k--)
    {
        wolf.push_back(k);
        if (BackTracking(wolf, N, M, L, k - 1))
            return true; //when k-1 is negetive just return false
        else
            wolf.pop_back(); //undo and switch the sibling
    }
    return false; // the whole child is unvailble, return false and switch the next sibling
}

int main()
{
    int N, M, L;
    int k = 1;
    cin >> N >> M >> L;
    vector<int> wolf;
    for (int i = 1; i <= N; ++i)
        cin >> a[i];
    bool find = BackTracking(wolf, N, M, L, N);
    if (!find)
        cout << "No Solution\n";
    else
    {
        cout << wolf[0];
        for (int i = 1; i < M; i++)
        {
            cout << " " << wolf[i];
        }
    }
    return 0;
}