// 完全背包：每个物品可以用无数次 O(nv)
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 110;
const int MAX_WEIGHT = 1010;

int n, v
int val[MAX_N];
int wgt[MAX_N];

// dp[i][j]: 含义同01中的含义
int dp[MAX_WEIGHT];

int main()
{
    scanf("%d%d", &v, &n);

    for(int i = 0; i < n; ++i)
        scanf("%d%d", &wgt[i], &val[i]);

    // 相对于01背包，仅是j的顺序变了
    for(int i = 0; i < n; ++i)
        for(int j = wgt[i]; j <= v; ++j)
            dp[j] = max(dp[j], dp[j-wgt[i]] + val[i]);

    printf("%d\n", dp[v]);
}
