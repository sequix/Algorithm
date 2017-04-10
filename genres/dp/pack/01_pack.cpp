// 百练 No.2773 采药
// 01背包：每个物品仅能用一次 O(nv)
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 110;
const int MAX_WEIGHT = 1010;

int n, v;         // number of items, maximum wgt(volume)
int val[MAX_N];   // the val of item[i]
int wgt[MAX_N];   // the wgt of item[i]

// dp[i][j]: 用前i个物品填充j大小的包，能得到的最大价值
// 注意dp数组的大小是背包能放物品的权重最大值(即容量，非物品数MAX_N)
int dp[MAX_WEIGHT];

int main()
{
    scanf("%d%d", &v, &n);

    for(int i = 0; i < n; ++i)
        scanf("%d%d", &wgt[i], &val[i]);

    // 别忘初始化
    //memset(dp, 0, sizeof(dp));

    for(int i = 0; i < n; ++i)
        for(int j = v; j >= wgt[i]; --j)
            dp[j] = max(dp[j], dp[j-wgt[i]] + val[i]);

    printf("%d\n", dp[v]);
}
