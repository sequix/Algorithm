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

// 区间时间序有关update
struct SegmentTree {
    int L[maxnode]; // L[o] o点覆盖区间的左端点
    int R[maxnode]; // R[o] o点覆盖区间的右端点
    int M[maxnode]; // M[o] o点覆盖区间的中间中间位置
    int minv[maxnode]; // minv[o] o点覆盖区间中的最小值
    int maxv[maxnode]; // maxv[o] o点覆盖区间中的最大值
    int sumv[maxnode]; // sumv[o] o点覆盖区间中的和
    int setv[maxnode]; // setv[o] o点覆盖区间的修改量
    bool setted[maxnode]; // setted[o] o点是否被设置
    int _min, _max, _sum; // query的返回值

    void build(int o, int l, int r) {
        if(l == r) {
            setted[o] = 1;
            L[o] = R[o] = M[o] = l;
            scanf("%d", &minv[o]);
            setv[o] = maxv[o] = sumv[o] = minv[o];
            return;
        }
        M[o] = (l+r) >> 1;
        L[o] = l, R[o] = r;
        setted[o] = setv[o] = 0;
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
        if(setted[o]) {
            minv[o] = maxv[o] = setv[o];
            sumv[o] += (R[o]-L[o]+1) * setv[o];
        }
    }
    void pushdown(int o) {
        if(setted[o]) {
            setted[o] = 0;
            setted[lc(o)] = setted[rc(o)] = 1;
            setv[lc(o)] = setv[rc(o)] = setv[o];
        }
    }
    void update(int o, int l, int r, int v) {
        if(l <= L[o] && R[o] <= r) {
            setv[o] = v, setted[o] = 1;
        } else {
            pushdown(o);
            if(l <= M[o]) update(lc(o), l, r, v); else maintain(lc(o));
            if(r > M[o]) update(rc(o), l, r, v); else maintain(rc(o));
        }
        maintain(o);
    }
    void query(int o, int l, int r) {
        if(setted[o]) {
            _min = min(_min, setv[o]);
            _max = max(_max, setv[o]);
            _sum = (min(r,R[o])-max(l,L[o])+1) * setv[o];
        } else if(l <= L[o] && R[o] <= r) {
            _min = min(_min, minv[o]);
            _max = max(_max, maxv[o]);
            _sum += sumv[o];
        } else {
            if(l <= M[o]) query(lc(o), l, r);
            if(r > M[o]) query(rc(o), l, r);
        }
    }
    void query(int l, int r) {
        _sum = 0, _min = inf, _max = -inf;
        query(0, l, r);
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
