// 多重背包：每个物品能最多能装num[i]次 O(nvlogm)
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 110;
const int MAX_WEIGHT = 1010;

int n, v;           // 共n件物品，包重量为v
int val[MAX_N];     // val[i] 第i件物品的价值
int wgt[MAX_N];     // wgt[i] 第i件物品的重量
int num[MAX_N];     // num[i] 第i件物品的数量

int dp[MAX_WEIGHT];

int main()
{
    scanf("%d%d", &v, &n);

    for(int i = 0; i < n; ++i)
        scanf("%d%d", &wgt[i], &val[i], &num[i]);

    for(int i = 0; i < n; ++i) {
        int cnt = num[i];
        for(int k = 1; cnt > 0; k <<= 1) {
            int mul = min(k, cnt);
            for(int j = v; j >= wgt[i] * mul; --j)
                dp[j] = max(dp[j], dp[j-wgt[i]*mul] + val[i]*mul);
            cnt -= mul;
        }
    }

    printf("%d\n", dp[v]);
}
