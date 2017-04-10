// POJ No.1384 Piggy-Bank
// 给出猪罐子的空质量和满质量，和n个硬币的价值和质量，
// 求猪罐子刚好塞满的的最小价值。
// 完全背包，初始化比较特殊
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 1e4 + 100;
const int inf = 0x3f3f3f3f;

int n, v;
int val[maxn];
int wgt[maxn];
int dp[maxn];

int main()
{
    int T, a, b;

    for(scanf("%d", &T); T > 0; --T) {
        scanf("%d%d%d", &a, &b, &n);
        v = b - a;
        for(int i = 0; i < n; ++i)
            scanf("%d %d", &val[i], &wgt[i]);

	// 为了刚好填满一个背包的初始化方法
        memset(dp, inf, sizeof(dp));
        dp[0] = 0;

        for(int i = 0; i < n; ++i)
            for(int j = wgt[i]; j <= v; ++j)
                dp[j] = min(dp[j], dp[j-wgt[i]] + val[i]);

        if(dp[v] == inf) {
            puts("This is impossible.");
        } else {
            printf("The minimum amount of money in "
                "the piggy-bank is %d.\n", dp[v]);
        }
    }
}
