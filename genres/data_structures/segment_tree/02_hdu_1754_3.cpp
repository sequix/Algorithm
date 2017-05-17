// NDU No.1754 I Hate It (range query & point update) (967ms 8464kB)
#include <cstdio>
using namespace std;
const int maxn = 2e5 + 10;
const int inf = 0x3f3f3f3f;
#define lc(o) (((o)<<1)+1)
#define rc(o) (((o)<<1)+2)
inline int min(int a, int b) { return a < b ? a : b; }
inline int max(int a, int b) { return a < b ? b : a; }

int n, q, A[maxn];
struct node { int L, R, maxv; } nd[maxn << 2];

void build(int o, int L, int R)
{
    if(L == R) { nd[o].L = nd[o].R = L, nd[o].maxv = A[L]; return; }
    int M = (L + R) >> 1;
    build(lc(o), L, M);
    build(rc(o), M+1, R);
    nd[o].L = L, nd[o].R = R;
    nd[o].maxv = max(nd[lc(o)].maxv, nd[rc(o)].maxv);
}

void update(int o, int p, int v)
{
    if(nd[o].L == nd[o].R) {
        nd[o].maxv = v;
    } else {
        int M = (nd[o].L + nd[o].R) >> 1;
        if(p <= M) update(lc(o), p, v); else update(rc(o), p, v);
        nd[o].maxv = max(nd[lc(o)].maxv, nd[rc(o)].maxv);
    }
}

int query(int o, int L, int R)
{
    if(L <= nd[o].L && nd[o].R <= R) {
        return nd[o].maxv;
    } else {
        int ans = -0x3f3f3f3f;
        int M = (nd[o].L + nd[o].R) >> 1;
        // 注意这里查询区间[L, R]始终未变
        // 直到某次节点区间[nd[o].L, nd[o].R]为[L, R]的子区间
        // 就将答案返回
        if(L <= M) ans = max(ans, query(lc(o), L, R));
        if(R > M) ans = max(ans, query(rc(o), L, R));
        return ans;
    }
}

int main()
{
    while(scanf("%d%d", &n, &q) != EOF) {
        for(int i = 1; i <= n; ++i)
            scanf("%d", &A[i]);
        build(0, 1, n);
        for(int i = 1; i <= q; ++i) {
            char c[2]; int A, B;
            scanf("%s%d%d", c, &A, &B);
            if(c[0] == 'U')
                update(0, A, B);
            else
                printf("%d\n", query(0, A, B));
        }
    }
}
