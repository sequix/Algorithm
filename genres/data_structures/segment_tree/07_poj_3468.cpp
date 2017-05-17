// POJ No.3468 (segment addition) (7064K 2954MS)
#include <cstdio>
using namespace std;
const int maxn = 1e5 + 10;
const int maxnode = maxn << 2;
#define lc(o) (((o)<<1)+1)
#define rc(o) (((o)<<1)+2)
typedef long long LL;

struct SegmentTree {
    LL sumv[maxnode], addv[maxnode];
    int L[maxnode], R[maxnode], M[maxnode];

    void init(int o, int l, int r) {
        if(l == r) {
            L[o] = R[o] = l;
            scanf("%lld", &sumv[o]);
            addv[o] = sumv[o];  // 注意这里
// 在maintain中每次为计算新的sumv，要先将原sumv[o]置0
// 再由子树计算新的附加信息，最后将本结点的addv累加上
// 但对叶子来说没有子树，为保证其值正确更新，所以将其原值放在addv中
            return;
        }
        M[o] = (l + r) >> 1;
        init(lc(o), l, M[o]);
        init(rc(o), M[o]+1, r);
        addv[o] = 0;
        L[o] = l, R[o] = r;
        sumv[o] = sumv[lc(o)] + sumv[rc(o)];
    }
    void maintain(int o) {
        sumv[o] = 0;
        if(L[o] < R[o]) sumv[o] = sumv[lc(o)] + sumv[rc(o)];
        if(addv[o]) sumv[o] += (R[o] - L[o] + 1) * addv[o];
    }
    void update(int o, int l, int r, LL v) {
        if(l <= L[o] && R[o] <= r) {
            addv[o] += v;
        } else {
            if(l <= M[o]) update(lc(o), l, r, v);
            if(r > M[o]) update(rc(o), l, r, v);
        }
        maintain(o);
    }
    LL query(int o, int l, int r, LL add) {
        if(l <= L[o] && R[o] <= r) {
            return sumv[o] + (R[o]-L[o]+1) * add;
        } else {
            LL sum = 0;
            if(l <= M[o]) sum += query(lc(o), l, r, add + addv[o]);
            if(r > M[o]) sum += query(rc(o), l, r, add + addv[o]);
            return sum;
        }
    }
} tree;

int main()
{
    LL c;
    char cmd[2];
    int a, b, n, q;

    scanf("%d%d", &n, &q);
    tree.init(0, 1, n);
    for(int i = 1; i <= q; ++i) {
        scanf("%s", cmd);
        if(cmd[0] == 'C') {
            scanf("%d%d%lld", &a, &b, &c);
            tree.update(0, a, b, c);
        } else {
            scanf("%d%d", &a, &b);
            printf("%lld\n", tree.query(0, a, b, 0));
        }
    }
}
