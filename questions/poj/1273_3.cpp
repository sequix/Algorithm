// POJ No.1273 Edmonds-Karp 邻接阵 (552K 0MS)
// EK:
//  while BFS 找到了增广路
//      增广
//      累计增广量到maxflow
//  maxflow为最大流
#include <cstdio>
#include <cstring>
using namespace std;
const int maxn = 205;
const int inf = 0x3f3f3f3f;
#define min(a, b) ((a) < (b) ? (a) : (b))

int n, m;
int pre[maxn];
int r[maxn][maxn];
int qf, qb, que[maxn];

int bfs(int s, int t)
{
    qf = qb = 0;
    memset(pre, -1, sizeof(pre));
    que[qb++] = s;
    pre[s] = s;
    while(qf < qb) {
        int u = que[qf++];
        if(u == t) return 1;
        for(int i = 0; i < n; ++i)
            if(r[u][i] > 0 && pre[i] == -1)
                pre[i] = u, que[qb++] = i;
    }
    return 0;
}

int ek(int s, int t)
{
    int maxflow = 0;
    while(bfs(s, t)) {
        int d = inf;
        for(int i = t; i != s; i = pre[i])
            d = min(d, r[pre[i]][i]);
        for(int i = t; i != s; i = pre[i])
            r[pre[i]][i] -= d, r[i][pre[i]] += d;
        maxflow += d;
    }
    return maxflow;
}

int main()
{
    int u, v, w;

    while(~scanf("%d%d", &m, &n)) {
        memset(r, 0, sizeof(r));
        for(int i = 0; i < m; ++i) {
            scanf("%d%d%d", &u, &v, &w);
            r[--u][--v] += w;
        }
        printf("%d\n", ek(0, n-1));
    }
}
