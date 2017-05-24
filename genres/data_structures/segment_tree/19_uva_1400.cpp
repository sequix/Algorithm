// UVA No.1400 (动态最大子段和位置) (120ms)
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 5e5 + 10;
const int maxnode = maxn << 2;
typedef pair<int, int> Interval;
#define lc(x) ((x)<<1)
#define rc(x) ((x)<<1|1)

LL sum[maxn];
LL getsum(int L, int R) { return sum[R] - sum[L-1]; }
LL getsum(const Interval &I) { return getsum(I.first, I.second); }

Interval better(const Interval &a, const Interval &b)
{
    LL sa = getsum(a), sb = getsum(b);
    if(sa == sb) return a < b ? a : b;
    else return sa > sb ? a : b;
}

struct {
    int ansP, ansS;
    Interval ansI, sub[maxnode];
    int pre[maxnode], suf[maxnode];

    void build(int o, int L, int R) {
        if(L == R) {
            pre[o] = suf[o] = L;
            sub[o] = Interval(L, L);
            return;
        }
        int M = (L + R) >> 1;
        build(lc(o), L, M);
        build(rc(o), M+1, R);

        LL v1 = getsum(L, pre[lc(o)]);
        LL v2 = getsum(L, pre[rc(o)]);
        if(v1 == v2) pre[o] = min(pre[lc(o)], pre[rc(o)]);
        else pre[o] = v1 > v2 ? pre[lc(o)] : pre[rc(o)];

        v1 = getsum(suf[lc(o)], R);
        v2 = getsum(suf[rc(o)], R);
        if(v1 == v2) suf[o] = min(suf[lc(o)], suf[rc(o)]);
        else suf[o] = v1 > v2 ? suf[lc(o)] : suf[rc(o)];

        sub[o] = better(sub[lc(o)], sub[rc(o)]);
        sub[o] = better(sub[o], Interval(suf[lc(o)], pre[rc(o)]));
    }

    void query(int o, int L, int R, int qL, int qR) {
        if(qL <= L && R <= qR) {
            ansP = pre[o], ansS = suf[o], ansI = sub[o];
        } else {
            int M = (L + R) >> 1;
            if(qR <= M) return query(lc(o), L, M, qL, qR);
            if(qL > M) return query(rc(o), M+1, R, qL, qR);
            
            query(lc(o), L, M, qL, M);
            Interval ansIL = ansI;
            int ansPL = ansP, ansSL = ansS;

            query(rc(o), M+1, R, M+1, qR);
            Interval ansIR = ansI;
            int ansPR = ansP, ansSR = ansS;

            ansI = better(ansI, ansIL);
            ansI = better(ansI, Interval(ansSL, ansPR));

            LL v1 = getsum(L, ansPL);
            LL v2 = getsum(L, ansPR);
            if(v1 == v2) ansP = min(ansPL, ansPR);
            else ansP = v1 > v2 ? ansPL : ansPR;

            v1 = getsum(ansSL, R);
            v2 = getsum(ansSR, R);
            if(v1 == v2) ansS = min(ansSL, ansSR);
            else ansS = v1 > v2 ? ansSL : ansSR;
        }
    }
} seg;

int main()
{
    int n, m, L, R, kase = 1;

    while(scanf("%d%d", &n, &m) != EOF) {
        printf("Case %d:\n", kase++);
        if(n == 1) {
            scanf("%*d");
            while(m--) { scanf("%*d%*d"); puts("1 1"); }
            continue;
        }

        scanf("%lld", &sum[1]);
        for(int i = 2; i <= n; ++i) {
            LL tmp; scanf("%lld", &tmp);
            sum[i] = sum[i-1] + tmp;
        }
        seg.build(1, 1, n);
        while(m--) {
            scanf("%d%d", &L, &R);
            seg.query(1, 1, n, L, R);
            printf("%d %d\n", seg.ansI.first, seg.ansI.second);
        }
    }
}
