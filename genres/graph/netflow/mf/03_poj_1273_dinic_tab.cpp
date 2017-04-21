// POJ No.1273 Dinic 邻接表实现 (388K 0MS)
#include <cstdio>
#include <cstring>
using namespace std;  
const int maxn = 205;
const int inf = 0x3f3f3f3f;
#define min(a, b) ((a) < (b) ? (a) : (b))

struct edge { int v, next, c; } eg[maxn<<1];

int n, m, s, t;
int dis[maxn];  
int egcnt, head[maxn];  
int qf, qb, que[maxn];

void add(int u, int v, int c)
{
    eg[egcnt].v = v;
    eg[egcnt].c = c;
    eg[egcnt].next = head[u];
    head[u] = egcnt++;
}  

int bfs()
{  
    qf = qb = 0;
    memset(dis, -1, sizeof(dis));  
    dis[s] = 0;
    que[qb++] = s;
    while(qf < qb && dis[t] == -1) {
        int u = que[qf++];
        for(int p = head[u]; p != -1; p = eg[p].next)
            if(dis[eg[p].v] == -1 && eg[p].c > 0)
                dis[eg[p].v] = dis[u] + 1, que[qb++] = eg[p].v;
    }  
    return dis[t] != -1;
}  

int augment(int u, int low)
{
    int a, v;
    if(u == t) return low;
    for(int p = head[u]; p != -1; p = eg[p].next) {
        v = eg[p].v;
        if(dis[v]==dis[u]+1 && eg[p].c>0 && (a=augment(v,min(low,eg[p].c)))) {
            eg[p].c -= a, eg[p^1].c += a;
            return a;
        }
    }
    return 0;
}

int dinic()
{
    int tmp, ans = 0;
    while(bfs())
        while(tmp = augment(s, inf))
            ans += tmp;
    return ans;
}  

int main()
{
    int u, v, w;

    while(~scanf("%d%d", &m, &n)) {
        egcnt = 0;
        s = 0, t = n-1;
        memset(head, -1, sizeof(head));  
        for(int i = 0; i < m; ++i) {
            scanf("%d%d%d", &u, &v, &w);
            add(--u, --v, w); add(v, u, 0);
        }
        printf("%d\n", dinic());
    }
}
