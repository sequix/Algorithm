// POJ No.3694 Network (10144K 422MS)
// 给一无向图，问每添一条边后的桥的数量。
// Tarjan求边双连通分量，用并查集将这些分量缩成一点，形成树
// 对每次的询问(u,v)判断u和v是否再一个连通分量中，
// 若在，对图的桥数没有影响
// 若不在，则u、v和lca(u,v)形成环，去环中的所有桥，并在并查集中合并u、v
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 1e5 + 10;
const int maxm = 5e5 + 10;

int n, m, nb;       // nb = number of bridges
int fat[maxn];      // 深度搜索树
int par[maxn];
int low[maxn];
int dfn[maxn];
int egc, head[maxn];
struct edge { int v, next; } eg[maxm];

void init()
{
    nb = egc = 0;
    //memset(fat, 0, sizeof(fat));
    //memset(low, 0, sizeof(low));
    memset(dfn, 0, sizeof(dfn));
    memset(head, -1, sizeof(head));
    for(int i = 0; i < maxn; ++i) par[i] = i;
}

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

void tarjan(int u, int f, int dep)
{
    fat[u] = f;
    low[u] = dfn[u] = dep;
    for(int p = head[u]; ~p; p = eg[p].next) {
        int v = eg[p].v;
        if(!dfn[v]) {   // 这里dfn从1开始
            tarjan(v, u, dep+1);
            low[u] = min(low[u], low[v]);
            if(low[v] <= dfn[u]) merge(u, v);
            if(low[v] > dfn[u]) ++nb;
        } else if(v != f) {
            low[u] = min(low[u], dfn[v]);
        }
    }
}

void merge_father(int u)
{
    int pu = getpar(u);
    int pfu = getpar(fat[u]);
    // 不在一个连通分量中，则u到fat[u]的边必为桥，所以--nb
    if(pu != pfu) {
        --nb;
        par[pu] = par[pfu];
    }
}

void lca(int u, int v)
{
    while(dfn[u] > dfn[v]) {
        merge_father(u);
        u = fat[u];
    }
    while(dfn[v] > dfn[u]) {
        merge_father(v);
        v = fat[v];
    }
    while(u != v) {
        merge_father(u);
        merge_father(v);
        u = fat[u], v = fat[v];
    }
}

int main()
{
    int u, v, q, kase = 1;
    while(scanf("%d%d", &n, &m) == 2 && n + m) {
        init();
        for(int i = 0; i < m; ++i) {
            scanf("%d%d", &u, &v);
            addedge(u, v);
        }
        tarjan(1, 0, 1);
        printf("Case %d:\n", kase++);
        for(scanf("%d", &q); q > 0; --q) {
            scanf("%d%d", &u, &v);
            if(getpar(u) != getpar(v))
                lca(u, v);
            printf("%d\n", nb);
        }
        putchar('\n');
    }
}
