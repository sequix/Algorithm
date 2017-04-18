// Tarjan算法求无向图的点双连通分量 O(V+E)
// 用栈记录dfs过程中的点，每遇到一个割点，
// 就代表一个找齐了一个点双连通分量
int dfn[maxn];  // 每个结点的深度搜索数，从1开始
int low[maxn];  // 每个结点可通过回边或子女的回边能达到的最高层（dfn最小）
int stop, stk[maxn];

void tarjan(int u, int from, int dep)
{
    stk[stop++] = u;
    low[u] = dfn[u] = dep;
    for(int p = head[u]; ~p; p = eg[p].next) {
        int v = eg[p].v;
        if(!dfn[v]) {
            tarjan(v, u, dep+1);
            low[u] = min(low[u], low[v]);
            if(low[v] >= dfn[u]) {
                while(stk[stop-1] != u)
                    printf("%d ", stk[--stop]);
                printf("%d\n", u);
            }
        } else if(v != from) {
            low[u] = min(low[u], dfn[v]);
        }
    }
}
