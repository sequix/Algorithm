// UVA No.11992 (二维线段树) (470ms)
#include <cstdio>
#include <cstring>
using namespace std;
const int inf = 2e9;
const int maxnode = 1 << 17;
#define lc(o) ((o)<<1)
#define rc(o) ((o)<<1|1)
inline int min(int a, int b) { return a < b ? a : b; }
inline int max(int a, int b) { return a < b ? b : a; }

struct SegmentTree {
    int set[maxnode], add[maxnode];
    int sum[maxnode], minv[maxnode], maxv[maxnode];
    int minI, maxI, qL, qR, qT, qV, rMin, rMax, rSum;

    void passSet(int o, int L, int R, int s) {
        set[o] = s, add[o] = 0;
        minv[o] = maxv[o] = s, sum[o] = (R-L+1) * s;
    }
    void passAdd(int o, int L, int R, int a) {
        add[o] += a;
        minv[o] += a, maxv[o] += a, sum[o] += (R-L+1) * a;
    }
    void pushdown(int o, int L, int R) {
        int M = (L + R) >> 1;
        if(set[o] > 0) {
            passSet(lc(o), L, M, set[o]);
            passSet(rc(o), M+1, R, set[o]);
            set[o] = 0;
        }
        if(add[o] > 0) {
            passAdd(lc(o), L, M, add[o]);
            passAdd(rc(o), M+1, R, add[o]);
            add[o] = 0;
        }
    }
    void pushup(int o) {
        sum[o] = sum[lc(o)] + sum[rc(o)];
        minv[o] = min(minv[lc(o)], minv[rc(o)]);
        maxv[o] = max(maxv[lc(o)], maxv[rc(o)]);
    }
    void update(int o, int L, int R) {
        if(qL <= L && R <= qR) {
            if(qT == 'S') passSet(o, L, R, qV);
            else passAdd(o, L, R, qV);
        } else {
            int M = (L + R) >> 1;
            pushdown(o, L, R);
            if(qL <= M) update(lc(o), L, M);
            if(qR > M) update(rc(o), M+1, R);
            pushup(o);
        }
    }
    int query(int o, int L, int R) {
        if(qL <= L && R <= qR) {
            rSum += sum[o];
            rMin = min(rMin, minv[o]);
            rMax = max(rMax, maxv[o]);
        } else {
            int M = (L + R) >> 1;
            pushdown(o, L, R);
            if(qL <= M) query(lc(o), L, M);
            if(qR > M) query(rc(o), M+1, R);
            pushup(o);
        }
    }
    void F(char t, int a, int b, int c=0) {
        qL = a, qR = b, qV = c, qT = t;
        if(t == 'Q') {
            rSum = 0, rMin = inf, rMax = -inf;
            query(1, minI, maxI);
        } else {
            update(1, minI, maxI);
        }
    }
};

int r, c, m;
SegmentTree row[21];

int main()
{
    int T, x1, x2, y1, y2, v;

    while(scanf("%d%d%d", &r, &c, &m) != EOF) {
        for(int i = 1; i <= r; ++i) {
            memset(&row[i], 0, sizeof(row[i]));
            row[i].minI = 1, row[i].maxI = c;
        }
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
