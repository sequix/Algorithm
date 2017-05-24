// POJ No.3368 (rmq & rle) (4404K 1125MS)
// 询问有序数列在[L,R]内中，出现次数最多数字的出现次数。
#include <cstdio>
using namespace std;
const int inf = 0x3f3f3f3f;
const int maxn = 1e5 + 10;
inline int max(int a, int b) { return a < b ? b : a; }

int n, q;
int seg[maxn];   // seg[i] A[i]处于第几段
int cnt[maxn];   // cnt[i] 第i段的数量
int left[maxn];  // left[i] 第i段的左端点
int right[maxn]; // right[i] 第i段的右端点
int f[maxn][18];

int main()
{
    int L, R, x, last, ns, a, b, k;

    while(scanf("%d%d", &n, &q) == 2) {
        if(n == 1) {
            while(q--) { scanf("%*d%*d"); puts("1"); }
            continue;
        }

        seg[1] = ns = 0;
        cnt[ns] = left[ns] = 1;

        scanf("%d", &last);
        for(int i = 2; i <= n; ++i) {
            scanf("%d", &x);
            if(x == last) {
                ++cnt[ns];
                seg[i] = ns;
            } else {
                right[ns] = i-1;
                seg[i] = ++ns;
                cnt[ns] = 1;
                left[ns] = i;
            }
            last = x;
        }
        right[ns] = n;

        for(int i = 0; i <= ns; ++i)
            f[i][0] = cnt[i];
        for(int j = 1; (1 << j) <= ns; ++j)
            for(int i = 0; i + (1<<j) - 1 <= ns; ++i)
                f[i][j] = max(f[i][j-1], f[i+(1<<j-1)][j-1]);

        while(q--) {
            scanf("%d%d", &L, &R);
            a = seg[L], b = seg[R];

            if(a == b) {
                printf("%d\n", R - L + 1);
            } else {
                int t1 = right[a] - L + 1;
                int t2 = R - left[b] + 1;
                int t3 = -inf;
                if(b - a > 1) {
                    ++a, --b;
                    for(k = 0; 1<<(k+1) <= b-a+1; ++k);
                    t3 = max(f[a][k], f[b-(1<<k)+1][k]);
                }
                printf("%d\n", max(t1, max(t2, t3)));
            }
        }
    }
}
