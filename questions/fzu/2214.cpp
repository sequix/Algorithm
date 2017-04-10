// FZU No.2214 Knapsack problem (超大背包) (2562MS 284KB)
// n个物品，填B大小的包，但无奈B非常大，普通01背包的O(nB)超时
// 发现所有物品的价值和<=5000，故定义
// dp[i][j]：前i件物品凑价值为j的方案所需的最小背包大小
// 则有dp[i][j-v[i]] = min(dp[i-1][j-v[i]], dp[i-1][j] - w[i])
// 如果不这样写递归式，你将会不知道按什么顺序计算
// 复杂度降为O(nV)，V为所有价值的和
#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn = 5010;
const LL inf = 1LL << 60;

int n, B;
LL dp[maxn];
int v[maxn], w[maxn];

int main()
{
    int T;

    for(scanf("%d", &T); T > 0; --T) {
        scanf("%d%d", &n, &B);

        LL tot_v = 0, tot_w = 0;
        for(int i = 0; i < n; ++i) {
            scanf("%d%d", &w[i], &v[i]);
            tot_v += v[i], tot_w += w[i];
        }

        fill(dp, dp + maxn, inf);
        dp[tot_v] = tot_w;

        for(int i = 0; i < n; ++i) {
            for(int j = 0; j <= tot_v; ++j) {
                if(j - v[i] >= 0) {
                    if(dp[j] - w[i] >= 0)
                        dp[j-v[i]] = min(dp[j-v[i]], dp[j] - w[i]);
                }
            }
        }

        for(int i = tot_v; i >= 0; --i)
            if(dp[i] <= B) { printf("%d\n", i); break; }
    }
}
