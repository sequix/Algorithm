// POJ No.3041 求二分图的点覆盖数 (632K 16MS)
// 给一个N*N的矩阵，有些格子有障碍，要求消除这些障碍，
// 问每次消除一行或一列的障碍， 最少要几次。
// 这里将每行x看成一个X结点，每列Y看成一个Y结点，障碍的坐标x,y看成X到Y的
// 一条边，构建出图后，就变成了找最少的点，使得这些点与所有的边相邻，
// 即最小点覆盖问题。 
#include <cstdio>
#include <cstring>
using namespace std;
const int maxn = 505;

int n, k;
char L[maxn][maxn];

int cx[maxn];
int cy[maxn];
bool vis[maxn];
int egc, head[maxn];
struct edge { int v, next; } eg[maxn*maxn];

void add(int u, int v)
{
    eg[egc] = (edge){v, head[u]};
    head[u] = egc++;
}

int dfs(int x)
{
    for(int p = head[x]; ~p; p = eg[p].next) {
        int y = eg[p].v;
        if(!vis[y]) {
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
    for(int x = 0; x < n; ++x) {
        if(cx[x] == -1) {
            memset(vis, 0, sizeof(vis));
            if(dfs(x)) ++ans;
        }
    }
    return ans;
}

int main()
{
    int r, c;
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &k);
    for(int i = 0; i < k; ++i) {
        scanf("%d%d", &r, &c);
        L[--r][--c] = 1;
    }
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < n; ++j)
            if(L[i][j]) add(i, j);
    printf("%d\n", maxmatch());
}
