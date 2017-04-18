// Tarjan算法求有向图的强连通分量 O(V+E) POJ2762
int nscc;           // scc的数量
int dfscnt;         // 记录进入dfs的次数
int dfn[maxn];      // 每个结点的深度搜索数，从1开始
int low[maxn];      // 每个结点可通过回边或子女的回边能达到的最高层（dfn最小）
bool instk[maxn];   // 记录一个点是否在栈中
int stop, stk[maxn];

void dfs(int u)
{
    stk[stop++] = u;
    instk[u] = 1;
    low[u] = dfn[u] = ++dfscnt;
    for(int p = head[u]; ~p; p = eg[p].next) {
        int v = eg[p].v;
        if(!dfn[v]) {
            tarjan(v, u, dep+1);
            low[u] = min(low[u], low[v]);
        } else if(instk[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if(low[u] == dfn[u]) {
        int v; ++nscc;
        do {
            v = stk[--top];
            instk[v] = 0;
            belong[v] = nscc;   // scc从1开始编号
        } while(u != v);
    }
}

void tarjan()
{
    for(int i = 0; i < n; ++i)  // 图的结点从0开始
        if(!dfn[i]) dfs(i);
}
