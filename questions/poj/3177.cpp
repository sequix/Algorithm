// POJ No.3177 Redundant Paths (484K 0MS)
// 给一个无向图，问最少填多少边可以将其转化为一个边双连通图。
// 将所有的边双连通分量缩成一个点，仅保留从各缩点连出的桥
// 统计新图(其实是个树)的叶子数C（度为1的点数），答案即为(C+1)/2
// 因为可以遵循这样的连法：首先把两个最近公共祖先最远的两个叶节点
// 之间连接一条边，这样可以把这两个点到祖先的路径上所有点收缩到一
// 起，因为一个形成的环一定是双连通的。然后再找两个最近公共祖先最
// 远的两个叶节点，这样一对一对找完，恰好是(C+1)/2次，把所有点
// 收缩到了一起。
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 5e3 + 10;
const int maxm = 2e4 + 10;

int n, m;
int low[maxn];
int dfn[maxn];
bool vis[maxn];
int egc, head[maxn];
struct edge { int v, next; } eg[maxm];

int d[maxn];
int par[maxn];
int belong[maxn];
int nb, bridge[maxm][2];

int getpar(int x)
{
    if(x != par[x])
        par[x] = getpar(par[x]);
    return par[x];
}

void merge(int x, int y)
{
    x = getpar(x), y = getpar(y);
    if(x != y) par[x] = y;
}

void addedge(int u, int v)
{
    eg[egc] = (edge){v, head[u]}, head[u] = egc++;
    eg[egc] = (edge){u, head[v]}, head[v] = egc++;
}

void init()
{
    memset(head, -1, sizeof(head));
    memset(belong, -1, sizeof(belong));
    for(int i = 0; i < maxn; ++i) par[i] = i;
}

void tarjan(int u, int f, int dep)
{
    vis[u] = 1;
    low[u] = dfn[u] = dep;

    for(int p = head[u]; ~p; p = eg[p].next) {
        int v = eg[p].v;
        if(!vis[v]) {
            tarjan(v, u, dep+1);
            low[u] = min(low[u], low[v]);
            // u，v在同一连通分量中
            if(low[v] <= dfn[u])
                merge(u, v);
            // (u,v)是桥
            if(low[v] > dfn[u])
                bridge[nb][0] = u, bridge[nb++][1] = v;
        } else if(v != f) {
            low[u] = min(low[u], dfn[v]);
        }
    }
}

// 将边双连通分量缩成一个点，返回点数
int compress()
{
    int ncon = 0;   // 连通变量数
    for(int i = 1; i <= n; ++i) {
        int p = getpar(i);
        if(belong[p] == -1)
            belong[p] = ncon++;
        belong[i] = belong[p];
    }
    return ncon;
}

int main()
{
    init();
    int u, v, nn;   // nn为缩点后图的点数

    scanf("%d%d", &n, &m);
    for(int i = 0; i < m; ++i) {
        scanf("%d%d", &u, &v);
        addedge(u, v);
    }
    tarjan(1, -1, 0);
    nn = compress();
    for(int i = 0; i < nb; ++i) {
        u = bridge[i][0], v = bridge[i][1];
        ++d[belong[u]], ++d[belong[v]];
    }
    int leafCount = 0;
    for(int i = 0; i < nn; ++i)
        if(d[i] == 1) ++leafCount;
    printf("%d\n", (leafCount+1) / 2);
}
