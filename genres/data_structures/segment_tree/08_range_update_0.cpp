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

// 区间时间序无关update
struct SegmentTree {
    int L[maxnode]; // L[o] o点覆盖区间的左端点
    int R[maxnode]; // R[o] o点覆盖区间的右端点
    int M[maxnode]; // M[o] o点覆盖区间的中间中间位置
    int minv[maxnode]; // minv[o] o点覆盖区间中的最小值
    int maxv[maxnode]; // maxv[o] o点覆盖区间中的最大值
    int sumv[maxnode]; // sumv[o] o点覆盖区间中的和
    int addv[maxnode]; // addv[o] o点覆盖区间的增量
    int _min, _max, _sum; // query的返回值

    void build(int o, int l, int r) {
        if(l == r) {
            L[o] = R[o] = M[o] = l;
            scanf("%d", &minv[o]);
            addv[o] = maxv[o] = sumv[o] = minv[o];
            return;
        }
        addv[o] = 0;
        M[o] = (l+r) >> 1;
        L[o] = l, R[o] = r;
        build(lc(o), l, M[o]);
        build(rc(o), M[o]+1, r);
        maintain(o);
    }
    void maintain(int o) {
        minv[o] = maxv[o] = sumv[o] = 0;
        if(L[o] < R[o]) {
            minv[o] = min(minv[lc(o)], minv[rc(o)]);
            maxv[o] = max(maxv[lc(o)], maxv[rc(o)]);
            sumv[o] = sumv[lc(o)] + sumv[rc(o)];
        }
        if(addv[o]) {
            minv[o] += addv[o];
            maxv[o] += addv[o];
            sumv[o] += (R[o]-L[o]+1) * addv[o];
        }
    }
    void update(int o, int l, int r, int v) {
        if(l <= L[o] && R[o] <= r) {
            addv[o] += v;
        } else {
            if(l <= M[o]) update(lc(o), l, r, v);
            if(r > M[o]) update(rc(o), l, r, v);
        }
        maintain(o);
    }
    // add用来累加祖先结点对当前结点的影响
    void query(int o, int l, int r, int add) {
        if(l <= L[o] && R[o] <= r) {
            _min = min(_min, minv[o] + add);
            _max = max(_max, maxv[o] + add);
            _sum += sumv[o] + (R[o]-L[o]+1) * add;
        } else {
            if(l <= M[o]) query(lc(o), l, r, add + addv[o]);
            if(r > M[o]) query(rc(o), l, r, add + addv[o]);
        }
    }
    void query(int l, int r) {
        _sum = 0, _min = inf, _max = -inf;
        query(0, l, r, 0);
    }
} tree;

int main()
{
    int n, q, T, l, r, v;

    while(scanf("%d%d", &n, &q) == 2) {
        tree.build(0, 0, n-1);
        for(int i = 0; i < q; ++i) {
            scanf("%d", &T);
            if(T == 0) {
                scanf("%d%d", &l, &r);
                tree.query(l, r);
                printf("%d %d %d\n", tree._min, tree._max, tree._sum);
            } else {
                scanf("%d%d%d", &l, &r, &v);
                tree.update(0, l, r, v);
            }
        }
    }
}
