// POJ No.2528 (离散化+区间覆盖) (63ms 1240kB)
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 1e4 + 10;
const int maxnode = maxn << 3;
#define lc(o) (((o)<<1)+1)
#define rc(o) (((o)<<1)+2)

struct {
    bool coverd[maxnode];   // 区间是否被完全覆盖
    int L[maxnode], R[maxnode], M[maxnode];

    void build(int o, int l, int r) {
        if(l == r) { coverd[o] = 0; L[o] = R[o] = l; return; }
        coverd[o] = 0;
        L[o] = l, R[o] = r;
        M[o] = (l + r) >> 1;
        build(lc(o), l, M[o]);
        build(rc(o), M[o]+1, r);
    }
    bool post(int o, int l, int r) {
        if(coverd[o]) return 0;
        if(l == L[o] && r == R[o]) return coverd[o] = 1;

        bool ret = 0;
        if(r <= M[o]) {
            ret = post(lc(o), l, r);
        } else if(l > M[o]) {
            ret = post(rc(o), l, r);
        } else {
            bool r1 = post(lc(o), l, M[o]);
            bool r2 = post(rc(o), M[o]+1, r);
            ret = r1 || r2;
        }
        coverd[o] = coverd[lc(o)] && coverd[rc(o)];
        return ret;
    }
} tree;

int n, ne;
int ends[maxn << 1];
int endL[maxn], endR[maxn];

int main()
{
    int T;
    for(scanf("%d", &T); T > 0; --T) {
        ne = 0;
        scanf("%d", &n);
        for(int i = 0; i < n; ++i) {
            scanf("%d%d", &endL[i], &endR[i]);
            ends[ne++] = endL[i], ends[ne++] = endR[i];
        }

        sort(ends, ends+ne);
        ne = unique(ends, ends+ne) - ends;
        tree.build(0, 0, ne);

        int ans = 0;
        for(int i = n-1; i >= 0; --i) {
            int e1 = lower_bound(ends, ends+ne, endL[i]) - ends;
            int e2 = lower_bound(ends, ends+ne, endR[i]) - ends;
            if(tree.post(0, e1, e2)) ++ans;
        }
        printf("%d\n", ans);
    }
}
