// ZOJ No.1516 求棋盘的最大覆盖数
// 转换成二分匹配问题解决之
#include <bits/stdc++.h>
using namespace std;
const int maxn = 105;

int r, c;
char L[maxn][maxn];

int cx[maxn*maxn];
int cy[maxn*maxn];
bool vis[maxn*maxn];
vector<int> G[maxn*maxn];

void build()
{
    static const int dir[][2] = {{0,1}, {0,-1}, {1,0}, {-1,0}};
    for(int i = 0; i < r*c; ++i)
        G[i].clear();
    for(int i = 0; i < r; ++i) {
        for(int j = 0; j < c; ++j) {
            if(L[i][j]) continue;
            for(int k = 0; k < 4; ++k) {
                int ni = i + dir[k][0], nj = j + dir[k][1];
                if(0<=ni&&ni<r && 0<=nj&&nj<c && !L[ni][nj])
                    G[i*r+j].push_back(ni*r+nj);
            }
        }
    }
}

int dfs(int x)
{
    for(int i = 0; i < G[x].size(); ++i) {
        int y = G[x][i];
        if(!vis[y]) {
            vis[y] = 1;
            if(cy[y] == -1 || dfs(cy[y])) {
                cy[y] = x, cx[x] = x;
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
    for(int i = 0; i < r; ++i) {
        for(int j = 0; j < c; ++j) {
            if(L[i][j]) continue;
            int x = i * r + j;
            if(cx[x] == -1) {
                memset(vis, 0, sizeof(vis));
                if(dfs(x)) ++ans;
            }
        }
    }
    return ans;
}

int main()
{
    int n, x, y;
    while(scanf("%d%d", &r, &c) != EOF && r + c) {
        memset(L, 0, sizeof(L));
        for(scanf("%d", &n); n > 0; --n) {
            scanf("%d%d", &x, &y);
            L[--x][--y] = 1;
        }
        build();
        printf("%d\n", maxmatch()/2);
    }
}
