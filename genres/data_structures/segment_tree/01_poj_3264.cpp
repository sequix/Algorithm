// POJ No.3264 Balanced Lineup (range query) (2412K 3360MS)
// 查询区间内的最大差值。
#include <cstdio>
using namespace std;
const int maxn = 5e4 + 10;
const int inf = 0x3f3f3f3f;
#define lc(o) (((o)<<1)+1)
#define rc(o) (((o)<<1)+2)
inline int max(int a, int b) { return a < b ? b : a; }
inline int min(int a, int b) { return a < b ? a : b; }

int n, q;
struct node { int L, R, minv, maxv; } nd[maxn << 2];

void build(int o, int L, int R)
{
    if(L == R) {
        nd[o].L = nd[o].R = L;
        scanf("%d", &nd[o].minv);
        nd[o].maxv = nd[o].minv;
        return;
    }
    int M = (L + R) >> 1;
    build(lc(o), L, M);
    build(rc(o), M+1, R);
    nd[o].L = L, nd[o].R = R;
    nd[o].minv = min(nd[lc(o)].minv, nd[rc(o)].minv);
    nd[o].maxv = max(nd[lc(o)].maxv, nd[rc(o)].maxv);
}

int _minv, _maxv;
void query(int o, int L, int R)
{
    if(L <= nd[o].L && nd[o].R <= R) {
        _minv = min(_minv, nd[o].minv);
        _maxv = max(_maxv, nd[o].maxv);
    } else {
        int M = (nd[o].L + nd[o].R) >> 1;
        if(L <= M) query(lc(o), L, R);
        if(R > M) query(rc(o), L, R);
    }
}

int main()
{
    scanf("%d%d", &n, &q);
    build(0, 1, n);
    for(int i = 1; i <= q; ++i) {
        int A, B; scanf("%d%d", &A, &B);
        _minv = inf, _maxv = -inf;
        query(0, A, B);
        printf("%d\n", _maxv - _minv);
    }
}
