// 刘汝佳线段树模板
#include <cstdio>
using namespace std;
const int maxn = 1e5 + 10;
const int maxnode = maxn << 2;
const int inf = 0x3f3f3f3f;
#define lc(o) (((o)<<1)+1)
#define rc(o) (((o)<<1)+2)
inline int min(int a, int b) { return a < b ? a : b; }
inline int max(int a, int b) { return a < b ? b : a; }

// 点修改
struct SegmentTree {
    int L[maxnode]; // L[o] o点覆盖区间的左端点
    int R[maxnode]; // R[o] o点覆盖区间的右端点
    int M[maxnode]; // M[o] o点覆盖区间的中间中间位置
    int minv[maxnode]; // minv[o] o点覆盖区间中的最小值

    void build(int o, int l, int r) {
        if(l == r) {
            L[o] = R[o] = M[o] = l;
            scanf("%d", &minv[o]);
            return;
        }
        M[o] = (l+r) >> 1;
        L[o] = l, R[o] = r;
        build(lc(o), l, M[o]);
        build(rc(o), M[o]+1, r);
        minv[o] = min(minv[lc(o)], minv[rc(o)]);
    }
    void update(int o, int p, int v) {
        if(L[o] == R[o]) {
            minv[o] = v;
        } else {
            if(p <= M[o]) update(lc(o), p, v);
            else update(rc(o), p, v);
            minv[o] = min(minv[lc(o)], minv[rc(o)]);
        }
    }
    int query(int o, int l, int r) {
        if(l <= L[o] && R[o] <= r) {
            return minv[o];
        } else {
            int ans = inf;
            if(l <= M[o]) ans = min(ans, query(lc(o), l, r));
            if(r > M[o]) ans = min(ans, query(rc(o), l, r));
            return ans;
        }
    }
} tree;

int main()
{
    int n, q, T, l, r;

    while(scanf("%d%d", &n, &q) == 2) {
        tree.build(0, 0, n-1);
        for(int i = 0; i < q; ++i) {
            scanf("%d%d%d", &T, &l, &r);
            if(T == 0)
                printf("%d\n", tree.query(0, l, r));
            else
                tree.update(0, l, r);
        }
    }
}
