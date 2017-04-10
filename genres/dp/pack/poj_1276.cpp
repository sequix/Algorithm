// POJ No.1276 Cash Machine 多重背包
// 给非负整数W，和n个正数v[i]，每个整数可以用m[i]次，
// 问不超过W的最大正数和。
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int dp[100005];

int main()
{
    int m, v, W, n;

    while(scanf("%d%d", &W, &n) != EOF) {
        memset(dp, 0, sizeof(dp));
        for(int i = 0; i < n; ++i) {
            scanf("%d%d", &m, &v);
            for(int k = 1; m > 0; k <<= 1) {
                int mul = min(k, m);
                for(int j = W; j >= v*mul; --j)
                    dp[j] = max(dp[j], dp[j-v*mul] + v*mul);
                m -= k;
            }
        }
        printf("%d\n", dp[W]);
    }
}
