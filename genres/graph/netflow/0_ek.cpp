// Edmonds-Karp 求最大流 (V * E^2)
int s, t;               // 源汇点
int prev[maxn];         // 增广路的点
int pree[maxn];         // 增广路的边
int aug[maxn];          // 增广量
int qf, qb, que[maxn];  // 用于BFS找增广路
int egc, head[maxn];    // 残余网络
struct edge { int v, r, next; } eg[maxm];

void addedge(int u, int v, int r)
{
    eg[egc] = (edge){v, r, head[u]}, haead[u] = egc++;
    eg[egc] = (edge){u, 0, head[v]}, haead[v] = egc++;
}

int bfs(int s, int t)
{
    qf = qb = 0;
    memset(prev, -1, sizeof(prev));

    aug[s] = inf;
    aug[t] = 0;
    que[qb++] = s;
    prev[s] = -1;

    while(qf < qb && prev[t] == -1) {
        int u = que[qf++];
        for(int p = head[u]; ~p; p = eg[p].next) {
            int v = eg[p].v, r = eg[p].r;
            if(prev[v] == -1 && r > 0) {
                prev[v] = u, 
                pree[v] = p; 
                aug[v] = min(aug[u], r);
                que[qb++] = v;
            }
        }
    }
    return aug[t];
}

int ek(int s, int t)
{
    int a, ans = 0;
    while(a = bfs(s, t)) {
        ans += a;
        for(int v = t; v != s; v = prev[v])
            eg[pree[p]].r -= a, eg[pree[p]^1].r += a;
    }
    return ans;
}
