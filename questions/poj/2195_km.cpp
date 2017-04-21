// POJ No.2195 二分图最优匹配 (428K 0MS)
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 101;
const int inf = 0x3f3f3f3f;
typedef pair<int, int> P;

int r, c, ny, nx;
P hs[maxn], ms[maxn];

int lx[maxn];
int ly[maxn];
int cy[maxn];
int slack[maxn];
bool visx[maxn];
bool visy[maxn];
int g[maxn][maxn];

int dis_of(const P &p1, const P &p2)
{
    return abs(p1.first - p2.first) + abs(p1.second - p2.second);
}

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

int km()
{
    memset(cy, -1, sizeof(cy));
    memset(ly, 0, sizeof(ly));
    memset(lx, 0, sizeof(lx));
    for(int i = 0; i < nx; ++i)
        for(int j = 0; j < ny; ++j)
            lx[i] = max(lx[i], g[i][j]);
    for(int i = 0; i < nx; ++i) {
        memset(slack, inf, sizeof(slack));
        while(1) {
            memset(visx, 0, sizeof(visx));
            memset(visy, 0, sizeof(visy));
            if(dfs(i)) break;
            int d = inf;
            for(int j = 0; j < ny; ++j)
                if(!visy[j]) d = min(d, slack[j]);
            for(int j = 0; j < nx; ++j)
                if(visx[j]) lx[j] -= d;
            for(int j = 0; j < ny; ++j)
                if(visy[j]) ly[j] += d;
                else slack[j] -= d;
        }
    }
    int ans = 0;
    for(int i = 0; i < ny; ++i)
        ans += g[cy[i]][i];
    return ans;
}

int main()
{
    int ch, ans;

    while(scanf("%d%d", &r, &c) == 2 && r + c) {
        nx = ny = 0;
        memset(g, 0, sizeof(g));

        for(int i = 0; i < r; ++i) {
            for(int j = 0; j < c; ++j) {
                // 不要用scanf(" %c", &ch)
                while(isspace(ch = getchar()));
                if(ch == 'm')
                    ms[nx++] = P(i, j);
                else if(ch == 'H')
                    hs[ny++] = P(i, j);
            }
        }

        for(int i = 0; i < nx; ++i)
            for(int j = 0; j < ny; ++j)
                g[i][j] = -dis_of(ms[i], hs[j]);

        printf("%d\n", -km());
    }
}
