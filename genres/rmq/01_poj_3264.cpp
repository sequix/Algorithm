// POJ No.3264 (7012K 3266MS)
#include <cstdio>
using namespace std;
const int maxn = 5e4 + 10;
inline int min(int a, int b) { return a < b ? a : b; }
inline int max(int a, int b) { return a < b ? b : a; }

int n, q;
int dmin[maxn][17], dmax[maxn][17];

int main()
{
    int L, R, k, a, b;

    scanf("%d%d", &n, &q);
    for(int i = 1; i <= n; ++i) {
        scanf("%d", &dmax[i][0]);
        dmin[i][0] = dmax[i][0];
    }

// 包括端点的n个数，从L开始向右为[L, L+n-1]
// 所以者n个数之后的数为L+n
// 包括端点的n个数，从R开始向左为[R-n+1, R]
// 所以者n个数之前的数为R-n

    for(int j = 1; (1<<j) <= n; ++j) {
        for(int i = 1; i + (1<<j) - 1 <= n; ++i) {
            dmin[i][j] = min(dmin[i][j-1], dmin[i+(1<<j-1)][j-1]);
            dmax[i][j] = max(dmax[i][j-1], dmax[i+(1<<j-1)][j-1]);
        }
    }

    while(q--) {
        scanf("%d%d", &L, &R);
        for(k = 0; (1<<k+1) <= R-L+1; ++k);
        b = max(dmax[L][k], dmax[R-(1<<k)+1][k]);
        a = min(dmin[L][k], dmin[R-(1<<k)+1][k]);
        printf("%d\n", b - a);
    }
}
