// POJ No.3041 Subsequence O(n) (776K 79MS)
// 给N个正数(10<N<1e5)，每个<=1e4，求满足和>=S(S<1e8)的最小子串长度
// 尺取法：维护求和的起点s，终点t和当前和sum
// 在保证sum < S的情况下，t向后移动，并更新sum
// 直到sum >= S，更新ans = min(ans, t-s+1) 并且 sum -= A[s++]
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 1e5 + 10;

int A[maxn];

int main()
{
    int T, N, S, tmp, sum, ans;

    for(scanf("%d", &T); T > 0; --T) {
        scanf("%d%d", &N, &S);

        for(int i = 0; i < N; ++i)
            scanf("%d", &A[i]);

        int s = 0, t = 0;
        sum = 0, ans = N + 1;
        while(1) {
            while(sum < S && t < N)
                sum += A[t++];
            if(sum < S) break;
            ans = min(ans, t - s);
            sum -= A[s++];
        }
        printf("%d\n", ans > N ? 0 : ans);
    }
}
