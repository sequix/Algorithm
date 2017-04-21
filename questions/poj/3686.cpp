// POJ No.3686 二分图求带权最优匹配 (924K 16MS)
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int inf = 0x3f3f3f3f;
const int maxx = 51;
const int maxy = 2501;

int n, m, nx, ny;
// g[i][j*n+k] 第i个order于第j个shop在倒数第k个开始的
// finishing time(从0开始到该订单完成所需的时间)
int g[maxx][maxy];
int lx[maxx], ly[maxy];
bool visx[maxx], visy[maxy];
int cy[maxy], slack[maxy];

int dfs(int x)
{
    visx[x] = 1;
    for(int y = 0; y < ny; ++y) {
        if(visy[y]) continue;
        if(lx[x] + ly[y] == g[x][y]) {
            visy[y] = 1;
            if(cy[y] == -1 || dfs(cy[y])) {
                cy[y] = x;
                return 1;
            }
        } else {
            slack[y] = min(slack[y], lx[x] + ly[y] - g[x][y]);
        }
    }
    return 0;
}

void km()
{
    memset(ly, 0, sizeof(ly));
    for(int i = 0; i < nx; ++i)
        lx[i] = -inf;
    for(int i = 0; i < nx; ++i)
        for(int j = 0; j < ny; ++j)
            lx[i] = max(lx[i], g[i][j]);
    for(int i = 0; i < nx; ++i) {
        memset(slack, 0x3f, sizeof(slack));
        while(1) {
            memset(visx, 0, sizeof(visx));
            memset(visy, 0, sizeof(visy));
            if(dfs(i)) {
                break;
            } else {
                int a = inf;
                for(int j = 0; j < ny; ++j)
                    if(!visy[j]) a = min(a, slack[j]);
                for(int j = 0; j < nx; ++j)
                    if(visx[j]) lx[j] -= a;
                for(int j = 0; j < ny; ++j)
                    if(visy[j]) ly[j] += a;
                // 下面这句保证下一次执行，不会选择到这次的y点
                // 因为至少a所对应的slack[j]会变成0
                // 又由相等子图的定义值A[i] + B[i] >= w[i, j]
                // 所以保证了不会选择重复的y点
                    else slack[j] -= a;
            }
        }
    }
}

int main()
{
    int T, x, cnt;

    for(scanf("%d", &T); T > 0; --T) {
        scanf("%d%d", &n, &m);

        for(int i = 0; i < n; ++i) {
            cnt = 0;
            for(int j = 0; j < m; ++j) {
                scanf("%d", &x);
                for(int k = 1; k <= n; ++k)
                    g[i][cnt++] = -x * k;
            }
        }
        nx = n, ny = n * m;
        memset(cy, -1, sizeof(cy));
        km();

        int sum = 0;
        for(int i = 0; i < ny; ++i)
            if(cy[i] != -1)
                sum += -g[cy[i]][i];
        printf("%.6f\n", 1.0 * sum / n);
    }
}
