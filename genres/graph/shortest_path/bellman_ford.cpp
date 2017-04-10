//// Bellman-Ford: 单源最短路 + 负环判断
int V, E, d[maxn], pre[maxn];
struct edge { int u, v, w; } eg[maxm];

bool bellman_ford(int s)
{
    memset(d, inf, sizeof(d));
    d[s] = 0;
    pre[s] = s;

    for(int i = 1; i <= V; ++i) {
        bool update = false;
        for(int j = 0; j < E; ++j) {
            edge &e = eg[j];
            if(d[e.v] > d[e.u] + e.w) {
                d[e.v] = d[e.u] + e.w;
                pre[e.v] = e.u;
                if(i == V) return true;    // 存在负环
                update = true;
            }
        }
        if(!update) break;
    }
    return false;
}
