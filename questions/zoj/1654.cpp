// ZOJ No.1654 在方格图上放机器人，要求不同行不同列
// 除非同行同列的机器人由墙壁隔开，问最多能放多少机器人？
// 这里不能使用 点对立数 = n - 边独立数
// 因为直接连接同行列的空地所构成的图并非二分图
// 所以将原图按行列拆成连通的小块hz[][], vt[][]
// 在空地对应的行块和列块（块作为点）之间连边，构成一个二分图
// 这样仅需要在该图上找没有公共点的边的最大数量，即最大匹配数
#include <bits/stdc++.h>
using namespace std;
const int maxn = 51;

int r, c;
char M[maxn][maxn];
int hz[maxn][maxn];
int vt[maxn][maxn];

int nx, ny;
// 注意要用maxn*maxn，因为原图中的每个空地都可能会引出一条边
int G[maxn*maxn][maxn*maxn];
int cx[maxn*maxn];
int cy[maxn*maxn];
bool vis[maxn*maxn];

int dfs(int x)
{
    for(int y = 1; y <= ny; ++y) {
        if(G[x][y] && !vis[y]) {
            vis[y] = 1;
            if(cy[y] == -1 || dfs(cy[y])) {
                cy[y] = x, cx[x] = y;
                return 1;
            }
        }
    }
    return 0;
}

int maxmatch()
{
    int ans = 0;
    memset(cx, -1, sizeof(cx));
    memset(cy, -1, sizeof(cy));
    for(int x = 1; x <= nx; ++x) {
        if(cx[x] == -1) {
            memset(vis, 0, sizeof(vis));
            ans += dfs(x);
        }
    }
    return ans;
}

int main()
{
    int T, cnt;

    scanf("%d", &T);
    for(int kase = 1; kase <= T; ++kase) {
        memset(hz, 0, sizeof(hz));
        memset(vt, 0, sizeof(vt));
        memset(G, 0, sizeof(G));

        scanf("%d%d", &r, &c);
        for(int i = 0; i < r; ++i)
            scanf("%s", &M[i]);

        cnt = 0;
        for(int i = 0; i < r; ++i) {
            bool flag = 1;
            for(int j = 0; j < c; ++j) {
                if(M[i][j] == 'o') {
                    if(flag) flag = 0, ++cnt;
                    hz[i][j] = cnt;
                } else if(M[i][j] == '#') {
                    flag = 1;
                }
            }
        }
        nx = cnt;

        cnt = 0;
        for(int j = 0; j < c; ++j) {
            bool flag = 1;
            for(int i = 0; i < r; ++i) {
                if(M[i][j] == 'o') {
                    if(flag) flag = 0, ++cnt;
                    vt[i][j] = cnt;
                } else if(M[i][j] == '#') {
                    flag = 1;
                }
            }
        }
        ny = cnt;

        for(int i = 0; i < r; ++i)
            for(int j = 0; j < c; ++j)
                if(hz[i][j]) G[hz[i][j]][vt[i][j]] = 1;

        printf("Case :%d\n", kase);
        printf("%d\n", maxmatch());
    }
}
