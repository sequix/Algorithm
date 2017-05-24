// HDU No.4614 (简单线段树+二分) (920ms 4640kB)
// hash线性探测，操作有二：
//     插入一个区间，问实际插入的初末位置
//     清除一个区间，问该区间中原来插入的值有几个
// 二分查找初末位置，线段树维护区间信息
#include <cstdio>
using namespace std;
const int maxn = 5e4 + 10;
const int maxnode = maxn << 2;
#define lc(o) ((o)<<1)
#define rc(o) ((o)<<1|1)
inline int min(int a, int b) { return a < b ? a : b; }

struct {
    int qL, qR, qV; // 维护某个区间插入值的数量
    int sum[maxnode], set[maxnode];
    int L[maxnode], R[maxnode], M[maxnode], sz[maxnode];

    void build(int o, int l, int r) {
        L[o] = l, R[o] = r;
        sz[o] = r - l + 1;
        M[o] = (l + r) >> 1;
        set[o] = -1, sum[o] = 0;
        if(l != r) {
            build(lc(o), l, M[o]);
            build(rc(o), M[o]+1, r);
        }
    }
    void pushdown(int o) {
        if(set[o] >= 0) { 
            set[lc(o)] = set[rc(o)] = set[o];
            sum[lc(o)] = sz[lc(o)] * set[o];
            sum[rc(o)] = sz[rc(o)] * set[o];
            set[o] = -1;
        }
    }
    void pushup(int o) {
        sum[o] = sum[lc(o)] + sum[rc(o)];
    }
    void update(int o) {
        if(qL <= L[o] && R[o] <= qR) {
            set[o] = qV;
            sum[o] = sz[o] * qV;
        } else {
            pushdown(o);
            if(qL <= M[o]) update(lc(o));
            if(qR > M[o]) update(rc(o));
            pushup(o);
        }
    }
    int query(int o) {
        if(qL <= L[o] && R[o] <= qR) {
            return sum[o];
        } else {
            int ans = 0;
            pushdown(o);
            if(qL <= M[o]) ans += query(lc(o));
            if(qR > M[o]) ans += query(rc(o));
            pushup(o);
            return ans;
        }
    }
} seg;

int T, n, m, k, a, b;

int main()
{
    for(scanf("%d", &T); T; --T) {
        scanf("%d%d", &n, &m);
        seg.build(1, 0, n-1);

        while(m--) {
            scanf("%d%d%d", &k, &a, &b);
            if(k == 1) {
                seg.qL = a, seg.qR = n-1;
                b = min(b, n-a - seg.query(1));
                
                if(b == 0) {
                    puts("Can not put any one.");
                    continue;
                }

                // 找a向右的第一个0
                int p1 = -1, p2 = -1;
                int l = a, r = n-1;
                while(l < r) {
                    int mid = (l + r) >> 1;
                    seg.qL = a, seg.qR = mid;
                    if(seg.query(1) < mid-a+1) p1 = r = mid;
                    else l = mid + 1;
                }

                // 找p1向右的b个0位置
                l = p1, r = n;
                // 当r==n-1时，虽然答案会覆盖[p1,n-1]
                // 但是mid==n-1那一次是不会被执行的
                // 也就是不会把n-1付给p2，所以这里r==n
                while(l < r) {
                    int mid = (l + r) >> 1;
                    seg.qL = p1, seg.qR = mid;
                    int len = mid - p1 + 1;
                    if(len - seg.query(1) >= b) p2 = r = mid;
                    else l = mid + 1;
                }

                seg.qL = p1, seg.qR = p2, seg.qV = 1, seg.update(1);
                printf("%d %d\n", p1, p2);
            } else {
                seg.qL = a, seg.qR = b, seg.qV = 0;
                printf("%d\n", seg.query(1));
                seg.update(1);
            }
        }
        putchar(10);
    }
}
