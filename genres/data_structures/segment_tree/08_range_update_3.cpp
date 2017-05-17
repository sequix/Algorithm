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
    int qL, qR, qV, qT; // 调用update, query的参数
    int rMin, rMax, rSum; // query的返回值

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
    void update(int o) {
        if(qL <= L[o] && R[o] <= qR) {
            if(qT == 1) addv[o] += qV;
            else setv[o] = qV, addv[o] = 0, setted[o] = 1;
        } else {
            pushdown(o);
            if(qL <= M[o]) update(lc(o)); else maintain(lc(o));
            if(qR > M[o]) update(rc(o)); else maintain(rc(o));
        }
        maintain(o);
    }
    void query(int o, int add) {
        if(setted[o]) {
            int v = setv[o] + add + addv[o];
            rMin = min(rMin, v);
            rMax = max(rMax, v);
            rSum += (min(qR, R[o])-max(qL, L[o])+1) * v;
        } else if(qL <= L[o] && R[o] <= qR) {
            rMin = min(rMin, minv[o] + add);
            rMax = max(rMax, maxv[o] + add);
            rSum += sumv[o] + (R[o]-L[o]+1) * add;
        } else {
            if(qL <= M[o]) query(lc(o), add + addv[0]);
            if(qR > M[o]) query(rc(o), add + addv[0]);
        }
    }
    void F(const char *f, int a, int b, int c=0) {
        qL = a, qR = b, qV = c;
        if(*f == 'A') {
            qT = 1, update(0);
        } else if(*f == 'S') {
            qT = 2, update(0);
        } else if(*f == 'Q') {
            rSum = 0, rMin = inf, rMax = -inf;
            query(0, 0);
        }
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
                tree.F("Q", l, r);
                printf("%d %d %d\n", tree.rMin, tree.rMax, tree.rSum);
            } else if(T == 1) {
                scanf("%d%d%d", &l, &r, &v);
                tree.F("A", l, r, v);
            } else if(T == 2) {
                scanf("%d%d%d", &l, &r, &v);
                tree.F("S", l, r, v);
            }
        }
    }
}
