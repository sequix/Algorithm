// POJ No.2391 floyd+二分+拆点+Dinic (2148K 375MS)
#include <map>
#include <string>
#include <cstdio>
#include <cstring>
using namespace std;
typedef long long LL;
const int maxn = 500;
const LL INF = 1e16;
const int inf = 0x3f3f3f3f;
#define min(a, b) ((a) < (b) ? (a) : (b))

int n, m, s, t, cow;
int farm[maxn][2];
LL dis[maxn][maxn];
int lv[maxn];
int cur[maxn];
int egc, head[maxn];
int qf, qb, que[maxn];
struct edge { int v, c, next; } eg[maxn*maxn];

void add(int u, int v, int c)
{
    eg[egc] = (edge){v, c, head[u]}; head[u] = egc++;
    eg[egc] = (edge){u, 0, head[v]}; head[v] = egc++;
}

int bfs()
{
    qf = qb = 0;
    memset(lv, -1, sizeof(lv));
    lv[s] = 0;
    que[qb++] = s;
    while(qf < qb && lv[t] == -1) {
        int u = que[qf++];
        for(int p = head[u]; p != -1; p = eg[p].next)
            if(lv[eg[p].v] == -1 && eg[p].c > 0)
                lv[eg[p].v] = lv[u]+1, que[qb++] = eg[p].v;
    }
    return lv[t] != -1;
}

int dfs(int u, int low)
{
    int a;
    if(u == t) return low;
    for(int &p = cur[u]; p != -1; p = eg[p].next) {
        int v = eg[p].v, c = eg[p].c;
        if(lv[v]==lv[u]+1 && c > 0 && (a=dfs(v, min(low,c)))) {
            eg[p].c -= a, eg[p^1].c += a;
            return a;
        }
    }
    return 0;
}

void build(LL m)
{
    egc = s = 0, t = (n << 1) + 1;
    memset(head, -1, sizeof(head));
    for(int i = 1; i <= n; ++i) {
        // 拆点i为i和t+i
        add(s, i, farm[i][0]);
        add(i, n+i, inf);
        add(n+i, t, farm[i][1]);
    }
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= n; ++j)
            if(dis[i][j] <= m) add(i, n+j, inf);
}

int dinic()
{
    int tmp, ans = 0;
    while(bfs()) {
        memcpy(cur, head, sizeof(head));
        while(tmp = dfs(s, inf)) ans += tmp;
    }
    return ans;
}

int isok(LL m)
{
    build(m);
    return dinic() >= cow;
}

int main()
{
    int u, v, w;

    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; ++i) {
        scanf("%d%d", &farm[i][0], &farm[i][1]);
        cow += farm[i][0];
    }
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= n; ++j)
            dis[i][j] = INF;    // 注意不是inf
    for(int i = 1; i <= m; ++i) {
        scanf("%d%d%d", &u, &v, &w);
        if(w < dis[u][v]) dis[u][v] = dis[v][u] = w;
    }

    for(int k = 1; k <= n; ++k)
        for(int i = 1; i <= n; ++i)
            for(int j = 1; j <= n; ++j)
                dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
    
    LL l = 0, r = INF, ans = -1;
    while(l < r) {
        LL m = l + r >> 1;
        if(isok(m)) ans = r = m;
        else l = m + 1;
    }
    printf("%lld\n", ans);
}
