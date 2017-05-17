// NDU No.1755 I Hate It (range query & point update) (390ms 3260kB)
#include <cstdio>
using namespace std;
const int maxn = 5e4 + 10;
const int inf = 0x3f3f3f3f;
#define lc(o) (((o)<<1)+1)
#define rc(o) (((o)<<1)+2)

int n, q, A[maxn];
struct node { int L, R, sum; } nd[maxn << 2];

void build(int o, int L, int R)
{
    if(L == R) { nd[o].L = nd[o].R = L, nd[o].sum = A[L]; return; }
    int M = (L + R) >> 1;
    build(lc(o), L, M);
    build(rc(o), M+1, R);
    nd[o].L = L, nd[o].R = R;
    nd[o].sum = nd[lc(o)].sum + nd[rc(o)].sum;
}

void add(int o, int p, int v)
{
    if(nd[o].L == nd[o].R) {
        nd[o].sum += v;
    } else {
        int M = (nd[o].L + nd[o].R) >> 1;
        if(p <= M) add(lc(o), p, v); else add(rc(o), p, v);
        nd[o].sum = nd[lc(o)].sum + nd[rc(o)].sum;
    }
}

int query(int o, int L, int R)
{
    if(L <= nd[o].L && nd[o].R <= R) {
        return nd[o].sum;
    } else {
        int sum = 0;
        int M = (nd[o].L + nd[o].R) >> 1;
        if(L <= M) sum += query(lc(o), L, R);
        if(R > M) sum += query(rc(o), L, R);
        return sum;
    }
}

int main()
{
    int T, L, R;
    char cmd[10];

    scanf("%d", &T);
    for(int kase = 1; kase <= T; ++kase) {
        printf("Case %d:\n", kase);

        scanf("%d", &n);
        for(int i = 1; i <= n; ++i)
            scanf("%d", &A[i]);
        build(0, 1, n);

        while(scanf("%s", cmd) != EOF && cmd[0] != 'E') {
            if(cmd[0] == 'Q') {
                scanf("%d%d", &L, &R);
                printf("%d\n", query(0, L, R));
            } else if(cmd[0] == 'A') {
                scanf("%d%d", &L, &R);
                add(0, L, R);
            } else {
                scanf("%d%d", &L, &R);
                add(0, L, -R);
            }
        }
    }
}
