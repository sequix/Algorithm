// POJ No.3041 Subsequence O(nlogn) (784K 79MS)
// 给N个正数(10<N<1e5)，每个<=1e4，求满足和>=S(S<1e8)的最小子串长度
// 对每一子串开始位置s找可以满足的结束位置t
// 统计前i个元素的和sum[i]
// 因为 a[s] + a[s+1] + ... + a[t] = sum[t] - sum[s-1] >= S
// 所以sum[t] >= S + sum[s-1]
// 又因为sum[]递增，所以二分找t
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 1e5 + 10;

int sum[maxn];  // sum数组从1开始，方便计算sum[t]-sum[s-1]这样的形式

int main()
{
    int T, N, S, tmp;

    for(scanf("%d", &T); T > 0; --T) {
        scanf("%d%d", &N, &S);

        sum[0] = 0;
        for(int i = 1; i <= N; ++i) {
            scanf("%d", &tmp);
            sum[i] = sum[i-1] + tmp;
        }

        if(sum[N] < S) {
            puts("0");
            continue;
        }

        int ans = N;
        for(int s = 0; S + sum[s] <= sum[N]; ++s) {
            int t = lower_bound(sum+s, sum+N, S + sum[s]) - sum;
            ans = min(ans, t - s);
        }
        printf("%d\n", ans);
    }
}
