// 考虑红黑树有N个内部节点的时候，最多有多少种实现可能性
// 因为红黑树的根节点可能是红色或黑色
// 如根节点为红色，则左右子树必为黑根节点红黑树
// 如根节点为黑色，则左右子树可为随意的种类
// 不妨从N小的时候进行累加计算

// 约束条件：红节点数+黑节点数 = N
#include <stdio.h>

int main()
{
    // N个内部节点
    int N;
    scanf("%d", &N);
}

// #include <bits/stdc++.h>
// using namespace std;
// const int maxn = 505;
// const int mod = 1000000007;
// int n, low, high;
// long long dpB[maxn][maxn]={}, dpR[maxn][maxn]={}, ans = 0;
// int main(){
//     scanf("%d", &n);
//     dpB[1][1] = 1, dpB[2][1] = 2;
//     dpR[1][1] = 1;
//     for(int i = 3; i <= n; ++ i){
//         low = log2(i+1)/2, high = log2(i+1)*2;
//         for(int j = low; j <= high; ++ j){
//             for(int k = 1; k < i-1; ++ k){
//                 dpB[i][j] = (dpB[i][j] + (((dpB[k][j-1]+dpR[k][j])*(dpB[i-1-k][j-1]+dpR[i-1-k][j]))%mod))% mod;
//                 dpR[i][j] = (dpR[i][j] + (dpB[k][j-1] * dpB[i-1-k][j-1]) % mod) % mod;
//             }
//         }
//     }
//     for(int i = 0; i < 30; ++ i)
//         ans = (ans + dpB[n][i]) % mod;
//     printf("%lld", ans);
// }
// ————————————————
// 版权声明：本文为CSDN博主「Brielleqqqqqqjie」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
// 原文链接：https://blog.csdn.net/qq_41562704/article/details/104183583