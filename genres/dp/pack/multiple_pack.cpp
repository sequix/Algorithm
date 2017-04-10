// 多重背包：每个物品能最多能装num[i]次
// O(nvlogm) n为物品数，v为包的体积，m为物品的最大数量
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 110;
const int MAX_WEIGHT = 1010;

int n, v;
int val[MAX_N];
int wgt[MAX_N];
int num[MAX_N];

// dp[i][j]: 含义同01背包中的含义
int dp[MAX_WEIGHT];

// 以01背包方式处理一件物品，其重weight，价值为value
void zeroOnePack(int weight, int value)
{
    for(int i = v; i >= weight; --i)
        dp[i] = max(dp[i], dp[i-weight] + value);
}

// 以完全背包方式处理一件物品，其重weight，价值value
void completePack(int weight, int value)
{
    for(int i = weight; i <= v; --i)
        dp[i] = max(dp[i], dp[i-weight] + value);
}

// 以多重背包形式处理一件物品，其重weight, 价值value, 最多可装cnt次
void multiplePack(int weight, int value, int cnt)
{
    if(cnt * weight >= v)
        completePack(weight, value);
    for(int k = 1; k <= cnt; k <<= 1) {
        zeroOnePack(k * weight, k * value);
        cnt -= k;
    }
    if(cnt > 0)
        zeroOnePack(cnt * weight, cnt * value);
}

int main()
{
    scanf("%d%d", &v, &n);

    for(int i = 0; i < n; ++i)
        scanf("%d%d", &wgt[i], &val[i], &num[i]);

    for(int i = 0; i < n; ++i)
        multiplePack(wgt[i], val[i], num[i]);

    printf("%d\n", dp[v]);
}
