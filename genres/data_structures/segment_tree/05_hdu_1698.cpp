// HDU No.1698 Just a Hook (segment setting) (1185ms 5628kB)
#include <cstdio>
using namespace std;
const int maxn = 1e5 + 10;
#define lc(o) (((o)<<1)+1)
#define rc(o) (((o)<<1)+2)

int n, q;
struct node { int L, R, sum, set; } nd[maxn << 2];

void build(int o, int L, int R)
{
    if(L == R) {
        nd[o].L = nd[o].R = L;
        nd[o].set = 0, nd[o].sum = 1;
        return;
    }
    int M = (L + R) >> 1;
    build(lc(o), L, M);
    build(rc(o), M+1, R);
    nd[o].set = 0;
    nd[o].L = L, nd[o].R = R;
    nd[o].sum = nd[lc(o)].sum + nd[rc(o)].sum;
}

void pushdown(int o)
{
    if(nd[o].set > 0) {
        nd[lc(o)].set = nd[rc(o)].set = nd[o].set;
        nd[o].set = 0;
    }
}

void maintain(int o)
{
    if(nd[o].L != nd[o].R)
        nd[o].sum = nd[lc(o)].sum + nd[rc(o)].sum;
    if(nd[o].set > 0)
        nd[o].sum = (nd[o].R - nd[o].L + 1) * nd[o].set;
}

void update(int o, int L, int R, int Z)
{
    if(L <= nd[o].L && nd[o].R <= R) {
        nd[o].set = Z;
    } else {
        pushdown(o);
        int M = (nd[o].L + nd[o].R) >> 1;
        if(L <= M) update(lc(o), L, R, Z); else maintain(lc(o));
        if(R > M) update(rc(o), L, R, Z); else maintain(rc(o));
    }
    maintain(o); 
}

int main()
{
    int T, A, B, Z;
    scanf("%d", &T);

    for(int kase = 1; kase <= T; ++kase) {
        scanf("%d%d", &n, &q);    
        build(0, 1, n);
        for(int i = 0; i < q; ++i) {
            scanf("%d%d%d", &A, &B, &Z);
            update(0, A, B, Z);
        }
        printf("Case %d: The total value of the hook is %d.\n",
            kase, nd[0].sum);
    }
}
