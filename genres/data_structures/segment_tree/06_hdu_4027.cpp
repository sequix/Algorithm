// HDU No.4027 Can you answer these queries? (764ms 5644kB)
// 数k（k<=2^63-1）在经最多7次的开平后，必成1，且1的平方根也是1；
// 也就是说当一个数为1的时候，我们没有必要对它进行操作和更新
// 所以每当我们要进行更新操作的时候，先判断一下这个区间
// 是否有必要进行更新（若全都是1就没有更新的必要了）；
// 判断方法：就是看该区间的长度和该区间内的总值是否相等；
#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 1e5 + 10;
typedef long long LL;
#define lc(o) (((o)<<1)+1)
#define rc(o) (((o)<<1)+2)

int n, q;
struct node { int L, R; LL sum; } nd[maxn<<2];

void build(int o, int L, int R)
{
    if(L == R) {
        nd[o].L = nd[o].R = L;
        scanf("%lld", &nd[o].sum);
        return;
    }
    int M = (L + R) >> 1;
    build(lc(o), L, M);
    build(rc(o), M+1, R);
    nd[o].L = L, nd[o].R = R;
    nd[o].sum = nd[lc(o)].sum + nd[rc(o)].sum;
}

inline int len(int o)
{
    return nd[o].R - nd[o].L + 1;
}

void update(int o, int L, int R)
{
    if(nd[o].L == nd[o].R) {
        nd[o].sum = sqrt(nd[o].sum);
    } else {
        int M = (nd[o].L + nd[o].R) >> 1;
        if(L <= M && nd[lc(o)].sum > len(lc(o))) update(lc(o), L, R);
        if(R > M && nd[rc(o)].sum > len(rc(o))) update(rc(o), L, R);
        nd[o].sum = nd[lc(o)].sum + nd[rc(o)].sum;
    }
}

LL query(int o, int L, int R)
{
    if(L <= nd[o].L && nd[o].R <= R) {
        return nd[o].sum;
    } else {
        LL sum = 0;
        int M = (nd[o].L + nd[o].R) >> 1;
        if(L <= M) sum += query(lc(o), L, R);
        if(R > M) sum += query(rc(o), L, R);
        return sum;
    }
}

int main()
{
    int T, X, Y, kase = 1;

    while(scanf("%d", &n) != EOF) {
        printf("Case #%d:\n", kase++);
        build(0, 1, n);

        scanf("%d", &q);
        for(int i = 0; i < q; ++i) {
            scanf("%d%d%d", &T, &X, &Y);
            if(X > Y) swap(X, Y);
            if(T == 0)
                update(0, X, Y);
            else
                printf("%lld\n", query(0, X, Y));
        }
        putchar(10);
    }
}
