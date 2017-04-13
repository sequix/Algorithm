// Tarjan算法求无向图的割点 O(V+E)
int root;       // 深度搜索树的根
int dfn[maxn];  // 每个结点的深度搜索数
int low[maxn];  // 每个结点可通过回边或子女的回边能达到的最高层（dfn最小）
bool vis[maxn];
bool is_cut_vertex[maxn];

void tarjan(int u, int from, int dep)
{
    int subtree = 0;        // 子树个数
    vis[u] = 1;
    low[u] = dfn[u] = dep;

    for(int p = head[u]; ~p; p = eg[p].next) {
        int v = eg[p].v;

        if(!vis[v]) {
            ++subtree;
            tarjan(v, u, dep+1);
            low[u] = min(low[u], low[v]);
            if((u==root && subtree>1) || (u!=root && low[v]>=dfn[u]))
                is_cut_vertex[u] = 1;
        } else if(v != from) {
            low[u] = min(low[u], dfn[v]);
        }
    }
}
