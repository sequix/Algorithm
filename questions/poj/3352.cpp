// POJ No.3352 Road Construction (456K 32MS) (同POJ3177)
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
