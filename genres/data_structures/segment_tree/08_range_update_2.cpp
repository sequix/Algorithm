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

// 区间修改
struct SegmentTree {
    int L[maxnode]; // L[o] o点覆盖区间的左端点
    int R[maxnode]; // R[o] o点覆盖区间的右端点
    int M[maxnode]; // M[o] o点覆盖区间的中间中间位置
    int minv[maxnode]; // minv[o] o点覆盖区间中的最小值
    int maxv[maxnode]; // maxv[o] o点覆盖区间中的最大值
    int sumv[maxnode]; // sumv[o] o点覆盖区间中的和
    int addv[maxnode]; // addv[o] o点覆盖区间的增量
    int setv[maxnode]; // setv[o] o点覆盖区间的修改量
    bool setted[maxnode]; // setted[o] o点是否被设置
    int _min, _max, _sum; // query的返回值

    void build(int o, int l, int r) {
        if(l == r) {
            scanf("%d", &minv[o]);
            L[o] = R[o] = M[o] = l;
            setv[o] = setted[o] = 0;
            addv[o] = maxv[o] = sumv[o] = minv[o];
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
        // set的优先级比add大
        if(setted[o]) {
            minv[o] = maxv[o] = setv[o];
            sumv[o] += (R[o]-L[o]+1) * setv[o];
        }
        if(addv[o]) {
            minv[o] += addv[o];
            maxv[o] += addv[o];
            sumv[o] += (R[o]-L[o]+1) * addv[o];
        }
    }
    void pushdown(int o) {
        if(setted[o]) {
            setted[o] = 0;
            setted[lc(o)] = setted[rc(o)] = 1;
            setv[lc(o)] = setv[rc(o)] = setv[o];
            addv[lc(o)] = addv[rc(o)] = 0; // set标记传递要清除add标记
        }
        if(addv[o]) {
            addv[lc(o)] += addv[o];
            addv[rc(o)] += addv[o];
            addv[o] = 0;
        }
    }
    void update(int o, int T, int l, int r, int v) {
        if(l <= L[o] && R[o] <= r) {
            if(T == 1) addv[o] += v;
            else setv[o] = v, addv[o] = 0, setted[o] = 1;
        } else {
            pushdown(o);
            if(l <= M[o]) update(lc(o), T, l, r, v);
            else maintain(lc(o));
            if(r > M[o]) update(rc(o), T, l, r, v);
            else maintain(rc(o));
        }
        maintain(o);
    }
    void query(int o, int l, int r, int add) {
        if(setted[o]) {
            int v = setv[o] + add + addv[o];
            _min = min(_min, v);
            _max = max(_max, v);
            _sum += (min(r, R[o])-max(l, L[o])+1) * v;
        } else if(l <= L[o] && R[o] <= r) {
            _min = min(_min, minv[o] + add);
            _max = max(_max, maxv[o] + add);
            _sum += sumv[o] + (R[o]-L[o]+1) * add;
        } else {
            if(l <= M[o]) query(lc(o), l, r, add + addv[0]);
            if(r > M[o]) query(rc(o), l, r, add + addv[0]);
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
                tree.update(0, T, l, r, v);
            }
        }
    }
}
