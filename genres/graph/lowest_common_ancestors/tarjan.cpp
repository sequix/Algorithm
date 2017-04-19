// Tarjan(深搜 + 并查集 + 链表)求LCA O(N + Q)
int par[MAX_N];
bool vis[MAX_N];

int getpar(int x)
{
    if(par[x] != x)
        par[x] = getpar(x);
    return par[x];
}

// 最初调用tarjan时要用root
void tarjan(int u)
{
    par[u] = u;
    for(int p = head[u]; ~p; p = eg[p].next) {
        tarjan(eg[p].v);
        par[eg[p].v] = u;
    }
    vis[u] = true;
    // qhead为所有询问的邻接表表头数组
    for(int p = qhead[u]; ~p; p = eg[p].next)
        if(vis[eg[p].v])
            printf("LCA of (%d,%d): %d\n", u, eg[p].v, getpar(eg[p].v));
}
