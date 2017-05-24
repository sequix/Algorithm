// UVA No.11992 (二维线段树) (1160ms)
#include <cstdio>
using namespace std;
const int inf = 2e9;
const int maxnode = 1 << 17;
#define lc(o) ((o)<<1)
#define rc(o) ((o)<<1|1)
inline int min(int a, int b) { return a < b ? a : b; }
inline int max(int a, int b) { return a < b ? b : a; }

struct SegmentTree {
    int qL, qR, qT, qV, rMin, rMax, rSum;
    int set[maxnode], add[maxnode];
    int sum[maxnode], minv[maxnode], maxv[maxnode];
    int L[maxnode], R[maxnode], M[maxnode], sz[maxnode];

    void build(int o, int l, int r) {
        L[o] = l, R[o] = r, M[o] = (l+r) >> 1, sz[o] = r-l+1;
        sum[o] = add[o] = set[o] = minv[o] = maxv[o] = 0;
        if(l < r) {
            build(lc(o), l, M[o]);
            build(rc(o), M[o]+1, r);
        }
    }
    void passSet(int o, int s) {
        set[o] = s, add[o] = 0;
        minv[o] = maxv[o] = s, sum[o] = sz[o] * s;
    }
    void passAdd(int o, int a) {
        add[o] += a;
        minv[o] += a, maxv[o] += a, sum[o] += sz[o] * a;
    }
    void pushdown(int o) {
        if(set[o] > 0) {
            passSet(lc(o), set[o]);
            passSet(rc(o), set[o]);
            set[o] = 0;
        }
        if(add[o] > 0) {
            passAdd(lc(o), add[o]);
            passAdd(rc(o), add[o]);
            add[o] = 0;
        }
    }
    void pushup(int o) {
        sum[o] = sum[lc(o)] + sum[rc(o)];
        minv[o] = min(minv[lc(o)], minv[rc(o)]);
        maxv[o] = max(maxv[lc(o)], maxv[rc(o)]);
    }
    void update(int o) {
        if(qL <= L[o] && R[o] <= qR) {
            if(qT == 'S') passSet(o, qV);
            else passAdd(o, qV);
        } else {
            pushdown(o);
            if(qL <= M[o]) update(lc(o));
            if(qR > M[o]) update(rc(o));
            pushup(o);
        }
    }
    int query(int o) {
        if(qL <= L[o] && R[o] <= qR) {
            rSum += sum[o];
            rMin = min(rMin, minv[o]);
            rMax = max(rMax, maxv[o]);
        } else {
            pushdown(o);
            if(qL <= M[o]) query(lc(o));
            if(qR > M[o]) query(rc(o));
            pushup(o);
        }
    }
    void F(char t, int a, int b, int c=0) {
        qL = a, qR = b, qV = c, qT = t;
        if(t == 'Q') {
            rSum = 0, rMin = inf, rMax = -inf;
            query(1);
        } else {
            update(1);
        }
    }
};

int r, c, m;
SegmentTree row[21];

int main()
{
    int T, x1, x2, y1, y2, v;

    while(scanf("%d%d%d", &r, &c, &m) != EOF) {
        for(int i = 1; i <= r; ++i)
            row[i].build(1, 1, c);
        while(m--) {
            scanf("%d", &T);
            switch(T) {
                case 1:
                    scanf("%d%d%d%d%d", &x1, &y1, &x2, &y2, &v);
                    for(int i = x1; i <= x2; ++i)
                        row[i].F('A', y1, y2, v);
                    break;
                case 2:
                    scanf("%d%d%d%d%d", &x1, &y1, &x2, &y2, &v);
                    for(int i = x1; i <= x2; ++i)
                        row[i].F('S', y1, y2, v);
                    break;
                case 3:
                    scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
                    int rSum = 0, rMin = inf, rMax = -inf;
                    for(int i = x1; i <= x2; ++i) {
                        row[i].F('Q', y1, y2);
                        rSum += row[i].rSum;
                        rMin = min(rMin, row[i].rMin);
                        rMax = max(rMax, row[i].rMax);
                    }
                    printf("%d %d %d\n", rSum, rMin, rMax);
                    break;
            }
        }
    }
}
