// POJ No.3468 A Simple Problem with Integers (segment addition)
#include <cstdio>
using namespace std;
const int maxn = 1e5 + 10;
#define lc(o) (((o)<<1)+1)
#define rc(o) (((o)<<1)+2)
typedef long long LL;

int n, q;
struct node { int L, R; LL sum, add; } nd[maxn << 2];

void build(int o, int L, int R)
{
    if(L == R) {
        nd[o].add = 0;
        nd[o].L = nd[o].R = L;
        scanf("%lld", &nd[o].sum);
        return;
    }
    int M = (L + R) >> 1;
    build(lc(o), L, M);
    build(rc(o), M+1, R);
    nd[o].add = 0;
    nd[o].L = L, nd[o].R = R;
    nd[o].sum = nd[lc(o)].sum + nd[rc(o)].sum;
}

void maintain(int o)
{
    if(nd[o].L != nd[o].R)
        nd[o].sum += nd[lc(o)].sum + nd[rc(o)].sum;
    nd[o].sum += (nd[o].R - nd[o].L + 1) * nd[o].add;
}

void add(int o, int L, int R, LL c)
{
    if(L <= nd[o].L && nd[o].R <= R) {
        nd[o].add += c;
    } else {
        int M = (nd[o].L + nd[o].R) >> 1;
        if(L <= M) add(lc(o), L, R, c);
        if(R > M) add(rc(o), L, R, c);
    }
    // 将[L,R]分解到合适结点的add，沿路的结点要更新sum值
    maintain(o);
}

LL query(int o, int L, int R)
{
    if(L <= nd[o].L && nd[o].R <= R) {
        return nd[o].sum + (nd[o].R - nd[o].L + 1) * nd[o].add;
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
    LL c;
    int a, b;
    char cmd[2];

    scanf("%d%d", &n, &q);
    build(0, 1, n);
    for(int i = 1; i <= q; ++i) {
        scanf("%s", cmd);
        if(cmd[0] == 'C') {
            scanf("%d%d%lld", &a, &b, &c);
            add(0, a, b, c);
        } else {
            scanf("%d%d", &a, &b);
            printf("%lld\n", query(0, a, b));
        }
    }
}
