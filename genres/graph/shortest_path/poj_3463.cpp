// POJ No.3463 Sightseeing (求最短路和次短路条数) (520K 79MS)
#include <queue>
#include <cstdio>
#include <cstring>
using namespace std;
const int maxn = 1e3 + 10;
const int maxm = 1e4 + 10;
const int inf = 0x3f3f3f3f;

int n, m, s, f;
int num[maxn][2];
int dis[maxn][2];
bool vis[maxn][2];
int egc, head[maxn];
struct edge { int v, w, next; } eg[maxm];

void addedge(int u, int v, int w)
{
    eg[egc] = (edge){v, w, head[u]}, head[u] = egc++;
}

int dijkstra()
{
    memset(vis, 0, sizeof(vis));
    memset(num, 0, sizeof(num));
    memset(dis, inf, sizeof(dis));

    dis[s][0] = 0;
    num[s][0] = 1;

    // 要遍历2*n-1次是因为，我们要求出以s开始的所有的节点的
    // 最短路和次短路，而s点的最短路是不需要找的，所以
    // 要遍历2*n-1次，或者直接用while(1)也行
    for(int _ = 1; _ < 2*n; ++_) {
        int u = -1, d = inf, flag;
        for(int i = 1; i <= n; ++i) {
            if(!vis[i][0] && dis[i][0] < d)
                u = i, d = dis[i][0], flag = 0;
            else if(!vis[i][1] && dis[i][1] < d)
                u = i, d = dis[i][1], flag = 1;
        }
        if(u == -1) break;
        vis[u][flag] = 1;

        for(int p = head[u]; ~p; p = eg[p].next) {
            int v = eg[p].v, w = eg[p].w;
            if(dis[v][0] > d + w) {
                dis[v][1] = dis[v][0];
                num[v][1] = num[v][0];
                dis[v][0] = d + w;
                num[v][0] = num[u][0];
            } else if(dis[v][0] == d + w) {
                num[v][0] += num[u][flag];
            } else if(dis[v][1] > d + w) {
                dis[v][1] = d + w;
                num[v][1] = num[u][flag];
            } else if(dis[v][1] == d + w) {
                num[v][1] += num[u][flag];
            }
        }
    }
    int ret = num[f][0];
    if(dis[f][1] - 1 == dis[f][0])
        ret += num[f][1];
    return ret;
}

int main()
{
    int u, v, w, T;
    for(scanf("%d", &T); T > 0; --T) {
        egc = 0;
        memset(head, -1, sizeof(head));
        scanf("%d%d", &n, &m);
        for(int i = 0; i < m; ++i) {
            scanf("%d%d%d", &u, &v, &w);
            addedge(u, v, w);
        }
        scanf("%d%d", &s, &f);
        printf("%d\n", dijkstra());
    }
}
