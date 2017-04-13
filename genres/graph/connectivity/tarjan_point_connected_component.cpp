// Tarjan算法求无向图的点双连通分量 O(V+E)
typedef pair<int, int> E;   // 一条边

int egc, head[maxn];
struct edge { int v; bool used; int next; } eg[maxm];

void addedge(int u, int v)
{
    eg[egc] = (edge){v, 0, head[u]}; head[u] = egc++;
    eg[egc] = (edge){u, 0, head[v]}; head[v] = egc++;
}

int root;
int dfn[maxn];
int low[maxn];
bool vis[maxn];
stack<E> stk;   // dfs过程中记录走过的边

// 比较两条无向边是否为同一条边
bool cmp_edge(const E &e1, const E &e2)
{
    if(e1.first == e2.first && e1.second == e2.second) return 1;
    if(e1.second == e2.first && e1.first == e2.second) return 1;
    return 0;
}

void tarjan(int u, int from, int dep)
{
    vis[u] = 1;
    low[u] = dfn[u] = dep;

    for(int p = head[u]; ~p; p = eg[p].next) {
        int v = eg[p].v;
        if(eg[p].used) continue;

        stk.push(E(u, v));
        eg[p].used = eg[p^1].used = 1;

        if(!vis[v]) {
            tarjan(v, u, dep+1);
            low[u] = min(low[u], low[v]);
            if(low[v] >= dfn[u]) {  // 这样写保证连通图也被正确输出
                while(1) {
                    E e = stk.top(); stk.pop();
                    printf("%d-%d ", e.first, e.second);
                    if(cmp_edge(e, E(u, v))) break;
                }
                putchar(10);
            }
        } else if(v != from) {
            low[u] = min(low[u], dfn[v]);
        }
    }
}
