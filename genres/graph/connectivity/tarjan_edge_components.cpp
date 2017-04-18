// Tarjan算法求无向图的边双连通分量 O(V+E)
// 将无向图的所有桥删掉后剩下的自然就是边双连通分量
// 这里用并查集记录每个边双连通分量
int par[maxn];  // 并查集
int dfn[maxn];  // 每个结点的深度搜索数，从1开始
int low[maxn];  // 每个结点可通过回边或子女的回边能达到的最高层（dfn最小）

void init()
{
    for(int i = 0; i < maxn; ++i)
        par[i] = i;
}

int getpar(int x)
{
    if(par[x] != x)
        par[x] = getpar(par[x]);
    return par[x];
}

void merge(int x, int y)
{
    x = getpar(x), y = getpar(y);
    if(x != y) par[x] = y;
}

void tarjan(int u, int from, int dep)
{
    low[u] = dfn[u] = dep;
    for(int p = head[u]; ~p; p = eg[p].next) {
        int v = eg[p].v;
        if(!dfn[v]) {
            tarjan(v, u, dep+1);
            low[u] = min(low[u], low[v]);
            if(low[v] <= dfn[u]) merge(u, v);
        } else if(v != from) {
            low[u] = min(low[u], dfn[v]);
        }
    }
}
