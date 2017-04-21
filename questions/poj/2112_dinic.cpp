// POJ No.2112 二分+Dinic (860K 157MS)
#include <cstdio>
#include <cstring>
using namespace std;
const int maxn = 250;
const int inf = 0x3f3f3f3f;
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) < (b) ? (b) : (a))

int K, C, M, s, t;
int level[maxn];
int r[maxn][maxn];
int dis[maxn][maxn];
int qf, qb, que[maxn];

void build(int m)
{
    // 新建源点为s，新建汇点为t
    s = 0, t = K+C+1;
    memset(r, 0, sizeof(r));
    // 源到每头牛有一条容量为1的弧
    // 所有源的出弧，刚好满足所有牛的数量C
    for(int i = K+1; i <= K+C; ++i)
        r[s][i] = 1;
    // 若牛和机器间的距离<=m，则牛在机器间有容量为1的弧
    for(int i = K+1; i <= K+C; ++i)
        for(int j = 1; j <= K; ++j)
            if(dis[i][j] <= m) r[i][j] = 1;
    // 机器到汇点有容量为M的弧
    for(int i = 1; i <= K; ++i)
        r[i][t] = M;
}

int bfs()
{
    qf = qb = 0;
    memset(level, -1, sizeof(level));
    level[s] = 0;
    que[qb++] = s;
    while(qf < qb && level[t] == -1) {
        int u = que[qf++];
        for(int i = 0; i <= K+C+1; ++i)
            if(level[i] == -1 && r[u][i] > 0)
                level[i] = level[u] + 1, que[qb++] = i;
    }
    return level[t] != -1;
}

int augment(int u, int low)
{
    int a;
    if(u == t) return low;
    for(int i = 0; i <= K+C+1; ++i)
        if(r[u][i] > 0 &&
            level[i] == level[u] + 1 &&
            (a = augment(i, min(low, r[u][i]))))
        {
            r[u][i] -= a, r[i][u] += a;
            return a;
        }
    return 0;
}

int isok(int m)
{
    build(m);
    int tmp, maxflow = 0;
    while(bfs())
        while(tmp = augment(s, inf))
            maxflow += tmp;
    return maxflow >= C;
}

int main()
{
    scanf("%d%d%d", &K, &C, &M);

    for(int i = 1; i <= K+C; ++i)
        for(int j = 1; j <= K+C; ++j) {
            scanf("%d", &dis[i][j]);
            dis[i][j] = (dis[i][j] == 0) ? inf : dis[i][j];
        }

    for(int k = 1; k <= K+C; ++k)
        for(int i = 1; i <= K+C; ++i)
            for(int j = 1; j <= K+C; ++j)
                dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);

    int l = inf, r = -inf;
    for(int i = 1; i <= K+C; ++i)
        for(int j = 1; j <= K+C; ++j)
            if(dis[i][j] != inf)
                l = min(l, dis[i][j]), r = max(r, dis[i][j]);

    while(l < r) {
        int m = l + r >> 1;
        if(isok(m)) r = m;
        else l = m + 1;
    }
    printf("%d\n", l);
}
