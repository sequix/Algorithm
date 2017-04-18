// ZOJ No.2588 Burning Bridge (Tarjan求桥) (740MS 3932KB)
// 当一条深度搜索树中的边<u,v>满足low[v] > dfn[u]
// 即经过这条边从u到v就回不到u那层时，边<u,v>为桥
// 注意如果两点之间有重边，则重边中不论哪边都不是桥
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e4 + 100;
const int maxm = 1e5 + 100;

int n, m, nb;
bool vis[maxn];
int bridges[maxm];
int low[maxn], dfn[maxn];

int egc, head[maxn];    // f标记是否有与该条边一样的重边
struct edge { int v, id; bool f; int next; } eg[maxm*2];

void addedge(int u, int v, int id)
{
    bool f = 0;
    for(int p = head[u]; ~p; p = eg[p].next)
        if(eg[p].v == v) { f = 1; break; }
    eg[egc] = (edge){v, id, f, head[u]}, head[u] = egc++;
    eg[egc] = (edge){u, id, f, head[v]}, head[v] = egc++;
}

void dfs(int u, int f, int dep)
{
    vis[u] = 1;
    low[u] = dfn[u] = dep;

    for(int p = head[u]; ~p; p = eg[p].next) {
        int v = eg[p].v;
        if(!vis[v]) {
            dfs(v, u, dep+1);
            low[u] = min(low[u], low[v]);
            if(low[v] > dfn[u] && !eg[p].f)
                bridges[nb++] = eg[p].id;
        } else if(v != f) {
            low[u] = min(low[u], dfn[v]);
        }
    }
}

int main()
{
    int T, u, v;

    scanf("%d", &T);
    for(int kase = 1; kase <= T; ++kase) {
        nb = egc = 0;
        memset(head, -1, sizeof(head));
        memset(low, 0, sizeof(low));
        memset(dfn, 0, sizeof(dfn));
        memset(vis, 0, sizeof(vis));

        scanf("%d%d", &n, &m);
        for(int i = 1; i <= m; ++i) {
            scanf("%d%d", &u, &v);
            addedge(u, v, i);
        }

        dfs(1, -1, 0);
        if(kase >= 2) putchar(10);
        printf("%d\n", nb);
        sort(bridges, bridges+nb);
        for(int i = 0; i < nb-1; ++i)
            printf("%d ", bridges[i]);
        if(nb > 0)
            printf("%d\n", bridges[nb-1]);
    }
}
