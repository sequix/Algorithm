// CODE[VS] No.3981 (动态最大子段和) (1564ms)
#include <cstdio>
using namespace std;
typedef long long LL;
const int maxn = 2e5 + 10;
const int maxnode = maxn << 2;
#define lc(x) ((x)<<1)
#define rc(x) ((x)<<1|1)
inline LL max(LL a, LL b) { return a < b ? b : a; }

struct {
    LL ans, ansL, ansR; // 最大子段和，最大前缀和，最大后缀和
    LL sum[maxnode];  // 区间和
    LL maxv[maxnode]; // 该区间最大子段和
    LL pre[maxnode];  // 该区间最大前缀和
    LL suf[maxnode];  // 该区间最大后缀和

    void build(int o, int L, int R) {
        if(L == R) {
            scanf("%lld", &sum[o]);
            maxv[o] = pre[o] = suf[o] = sum[o];
        } else {
            int M = (L+R)>>1;
            build(lc(o), L, M);
            build(rc(o), M+1, R);

            sum[o] = sum[lc(o)] + sum[rc(o)];
            maxv[o] = max(maxv[lc(o)], maxv[rc(o)]);
            maxv[o] = max(maxv[o], suf[lc(o)] + pre[rc(o)]);
            pre[o] = max(pre[lc(o)], sum[lc(o)] + pre[rc(o)]);
            suf[o] = max(suf[rc(o)], suf[lc(o)] + sum[rc(o)]);
        }
    }
    void query(int o, int L, int R, int qL, int qR) {
        if(qL == L && qR == R) {
            ans = maxv[o], ansL = pre[o], ansR = suf[o];
        } else {
            int M = (L + R) >> 1;
            if(qR <= M) {
                query(lc(o), L, M, qL, qR);
            } else if(qL > M) {
                query(rc(o), M+1, R, qL, qR);
            } else {
                query(lc(o), L, M, qL, M);
                LL Lans = ans, Lpre = ansL, Lsuf = ansR;
                query(rc(o), M+1, R, M+1, qR);
                LL Rans = ans, Rpre = ansL, Rsuf = ansR;

                ans = max(max(Lans, Rans), Lsuf + Rpre);
                ansL = max(Lpre, sum[lc(o)] + Rpre);
                ansR = max(Rsuf, Lsuf + sum[rc(o)]);
            }
        }
    }
} seg;

int main()
{
    int n, q, l, r;
    scanf("%d", &n);
    seg.build(1, 1, n);

    for(scanf("%d", &q); q > 0; --q) {
        scanf("%d%d", &l, &r);
        seg.ans = seg.ansL = seg.ansR = 0;
        seg.query(1, 1, n, l, r);
        printf("%lld\n", seg.ans);
    }
}
