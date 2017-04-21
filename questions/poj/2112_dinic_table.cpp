// POJ No.2112 二分+Dinic (756K 188MS)
#include <cstdio>
#include <cstring>
using namespace std;
const int maxn = 250;
const int inf = 0x3f3f3f3f;
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) < (b) ? (b) : (a))

struct edge { int v, next, c; } eg[maxn*maxn];

int K, C, M, s, t;
int lv[maxn];
int dis[maxn][maxn];
int egcnt, head[maxn];
int qf, qb, que[maxn];

void add(int u, int v, int c)
{
    eg[egcnt].v = v;
    eg[egcnt].c = c;
    eg[egcnt].next = head[u];
    head[u] = egcnt++;
}

void build(int m)
{
    // 新建源点为s，新建汇点为t
    egcnt = s = 0, t = K+C+1;
    memset(head, -1, sizeof(head));
    // 源到每头牛有一条容量为1的弧
    // 所有源的出弧，刚好满足所有牛的数量C
    for(int i = K+1; i <= K+C; ++i)
        add(s, i, 1), add(i, s, 0);
    // 若牛和机器间的距离<=m，则牛在机器间有容量为1的弧
    for(int i = K+1; i <= K+C; ++i)
        for(int j = 1; j <= K; ++j)
            if(dis[i][j] <= m) add(i, j, 1), add(j, i, 0);
    // 机器到汇点有容量为M的弧
    for(int i = 1; i <= K; ++i)
        add(i, t, M), add(t, i, 0);
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

int augment(int u, int low)
{
    int a;
    if(u == t) return low;
    for(int p = head[u]; p != -1; p = eg[p].next) {
        int v = eg[p].v, c = eg[p].c;
        if(lv[v]==lv[u]+1 && c > 0 && (a=augment(v, min(low,c)))) {
            eg[p].c -= a, eg[p^1].c += a;
            return a;
        }
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
