// POJ No.2516 最小费用流
// 建图过于复杂，以致TLE
#include <queue>
#include <cstdio>
#include <cstring>
using namespace std;
const int maxn = 1e4 + 100;
const int inf = 0x3f3f3f3f;

int n, m, k, s, t;
int dis[maxn];
int aug[maxn];
int prevv[maxn];
int preve[maxn];
int egc, head[maxn];
struct edge { int v, r, c, next; } eg[maxn * 10];

void addedge(int u, int v, int r, int c)
{
    eg[egc] = (edge){v, r, c, head[u]}; head[u] = egc++;
    eg[egc] = (edge){u, 0, -c, head[v]}; head[v] = egc++;
}

int dijkstra()
{
    typedef pair<int, int> P;
    priority_queue<P, vector<P>, greater<P> > que;
    for(int i = s; i <= t; ++i)
        dis[i] = inf;

    que.push(P(0, s));
    dis[s] = 0;
    aug[s] = inf;
    aug[t] = 0;
    prevv[s] = -1;

    while(!que.empty()) {
        P p = que.top(); que.pop();
        int u = p.second;
        if(dis[u] < p.first) continue;
        if(u == t) break;
        for(int p = head[u]; ~p; p = eg[p].next) {
            edge &e = eg[p];
            if(e.r > 0 && dis[e.v] > dis[u] + e.c) {
                dis[e.v] = dis[u] + e.c;
                prevv[e.v] = u;
                preve[e.v] = p;
                aug[e.v] = min(aug[u], e.r);
                que.push(P(dis[e.v], e.v));
            }
        }
    }
    return aug[t];
}

int mcf(int flow)
{
    int a;
    int f = 0;
    int ans = 0;

    while(a = dijkstra()) {
        f += a;
        ans += a * dis[t];
        for(int p = t; ~prevv[p]; p = prevv[p])
            eg[preve[p]].r -= a, eg[preve[p]^1].r += a;
        if(f >= flow) break;
    }
    return f >= flow ? ans : -1;
}

int main()
{
    int x;

    while(scanf("%d%d%d", &n, &m, &k)==3 && n+m+k) {
        egc = 0;
        memset(head, -1, sizeof(head));

        s = 0;
        t = (m + n) * k + 1;
        int i_stock = 1;
        int i_order = m*k + 1;
        int flow = 0;

        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < k; ++j) {
                scanf("%d", &x);
                flow += x;
                addedge(i_order + i*n+j, t, x, 0);
            }
        }
        for(int i = 0; i < m; ++i) {
            for(int j = 0; j < k; ++j) {
                scanf("%d", &x);
                addedge(s, i_stock + i*m+j, x, 0);
            }
        }
        for(int l = 0; l < k; ++l) {
            for(int i = 0; i < n; ++i) {
                for(int j = 0; j < m; ++j) {
                    scanf("%d", &x);
                    addedge(i_stock + j*m+l, i_order + i*n+l, inf, x);
                }
            }
        }

        printf("%d\n", mcf(flow));
    }
}
