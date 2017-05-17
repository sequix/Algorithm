// HDU No.3335 Divisibility (模拟) (124MS 1572K)
// 选仅可能多的整数，满足每两个之间不能整除。
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 1e3 + 10;

LL A[maxn];
int ans[maxn];  // ans[i] 选i作为起点的答案
bool vis[maxn];

int main()
{
    int T, n;

    for(scanf("%d", &T); T > 0; --T) {
        scanf("%d", &n);
        for(int i = 0; i < n; ++i)
            scanf("%lld", &A[i]);

        sort(A, A + n);
        n = unique(A, A + n) - A;

        for(int i = 0; i < n; ++i) {
            ans[i] = 1;
            memset(vis, 0, sizeof(vis));
            for(int j = i + 1; j < n; ++j) {
                if(vis[j] || A[j] % A[i] == 0)
                    continue;
                for(int k = j + 1; k < n; ++k)
                    if(A[k] % A[j] == 0) vis[k] = 1;
                ++ans[i];
            }
        }
        printf("%d\n", *max_element(ans, ans + n));
    }
}
