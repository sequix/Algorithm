// POJ No.2549 Sumsets (折半枚举) (16584K 532MS)
// 从N<=1000个数中挑出4个数满足a + b + c = d，求最大的d
// O(N^2)预处理a+b，又由a+b = d-c，枚举所有的d-c，
// 再二分的找对应的a+b，最后以O(N^2logN)解决
// 但要注意，abcd不能选相同的数字
#include <set>
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 1e3 + 10;
typedef long long LL;
const LL inf = 1LL << 60;

struct P {
    LL sum;
    int a, b;
    P(LL s=0, int a=0, int b=0): sum(s), a(a), b(b) {}
    bool operator < (const P &p) const { return sum < p.sum; }
};

int n;
LL A[maxn];
P AB[maxn*maxn];

int main()
{
    while(scanf("%d", &n) != EOF && n != 0) {
        for(int i = 0; i < n; ++i)
            scanf("%lld", &A[i]);

        // a+b满足交换律，所以j从i+1开始
        int nAB = 0;
        for(int i = 0; i < n; ++i)
            for(int j = i + 1; j < n; ++j)
                AB[nAB++] = P(A[i] + A[j], i, j);
        sort(AB, AB+nAB);

        // d-c不满足交换了，所以j从0开始
        LL ans = -inf;
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < n; ++j) {
                if(i == j) continue;
                LL DC = A[i] - A[j];
                int p = lower_bound(AB, AB+nAB, P(DC, 0, 0)) - AB;
                if(p != nAB && AB[p].sum == DC) {
                    set<int> cnt;
                    cnt.insert(i);
                    cnt.insert(j);
                    cnt.insert(AB[p].a);
                    cnt.insert(AB[p].b);
                    if(cnt.size() == 4)
                        ans = max(ans, A[i]);
                }
            }
        }
        if(ans == -inf)
            puts("no solution");
        else
            printf("%lld\n", ans);
    }
}
