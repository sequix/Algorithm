// Tarjan算法求无向图的桥 O(V+E)
int dfn[maxn];  // 每个结点的深度搜索数，从1开始
int low[maxn];  // 每个结点可通过回边或子女的回边能达到的最高层（dfn最小）
int nb, bridge[maxm];   // 桥数; 每一个桥

void tarjan(int u, int from, int dep)
{
    low[u] = dfn[u] = dep;
    for(int p = head[u]; ~p; p = eg[p].next) {
        int v = eg[p].v;
        if(!dfn[v]) {
            tarjan(v, u, dep+1);
            low[u] = min(low[u], low[v]);
            if(low[v] > dfn[u])
                bridge[nb][0] = u, bridge[nb++][1] = v;
        } else if(v != from) {
            low[u] = min(low[u], dfn[v]);
        }
    }
}
