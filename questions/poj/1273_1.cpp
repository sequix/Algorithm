// POJ No.1273 Dinic O(EV^2) (552K 0MS)
#include <cstdio>
#include <cstring>
using namespace std;

const int maxn = 205;
const int inf = 0x3f3f3f3f;
#define min(a, b) ((a) < (b) ? (a) : (b))

int n, m, s, t;
int dis[maxn];
int r[maxn][maxn];
int qf, qb, que[maxn];

// 建立分层图，可以建立则返回1
int bfs()
{
    qf = qb = 0;
    memset(dis, -1, sizeof(dis));
    que[qb++] = s;
    dis[s] = 0;
    while(qf < qb && dis[t] == -1) {
        int u = que[qf++];
        for(int i = 0; i < n; ++i)
            if(dis[i] == -1 && r[u][i] > 0)
                dis[i] = dis[u] + 1, que[qb++] = i;
    }
    return dis[t] != -1;
}

// 找增广路并增广，返回增广的流量值
int augment(int u, int low) // low为源点但当前点u中最小的剩余流量
{
    int a;
    if(u == t) return low;
    for(int i = 0; i < n; ++i)
        if(r[u][i] > 0 &&  // 联通
        dis[i] == dis[u]+1 &&   // 为下一层点
        (a = augment(i, min(low, r[u][i]))))   // 能达汇点，即a != 0
    {
        r[u][i] -= a, r[i][u] += a;
        return a;
    }
    return 0;
}

int dinic()
{
    int tmp, maxflow = 0;
    while(bfs())
        while(tmp = augment(s, inf))
            maxflow += tmp;
    return maxflow;
}

int main()
{
    int u, v, w;

    while(~scanf("%d%d", &m, &n)) {
        s = 0, t = n-1;
        memset(r, 0, sizeof(r));
        for(int i = 0; i < m; ++i) {
            scanf("%d%d%d", &u, &v, &w);
            r[--u][--v] += w;
        }
        printf("%d\n", dinic());
    }
}
