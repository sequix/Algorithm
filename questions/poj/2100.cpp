// POJ No.2100 Graveyard Design (尺取法) (584K 3797MS)
// 给一个正整数n<=1e14，求所有满足s^2 + (s+1)^2 + ... + (s+k-1)^2 = n
// 的方案。
#include <cmath>
#include <vector>
#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long LL;
typedef pair<LL, LL> P;

vector<P> ans;

int main()
{
    LL n;
    while(scanf("%lld", &n) != EOF) {
        ans.clear();

        LL sum = 0;
        LL s = 1, t = 1;
        LL lim = ceil(sqrt(n));
        while(1) {
            while(t <= lim && sum < n) {
                sum += t * t;
                ++t;
            }
            if(sum < n)
                break;
            if(sum == n)
                ans.push_back(make_pair(s, t));
            sum -= s * s;
            ++s;
        }
        printf("%d\n", ans.size());
        for(int i = 0; i < ans.size(); ++i) {
            printf("%lld", ans[i].second - ans[i].first);
            for(LL j = ans[i].first; j < ans[i].second; ++j)
                printf(" %lld", j);
            putchar(10);
        }
    }
}
