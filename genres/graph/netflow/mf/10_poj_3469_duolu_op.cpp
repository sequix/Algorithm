// POJ No.3469 Dinic+多路增广 求最小割容量 (6260K 5516MS)
// 网络流流量 <= 任何s-t割的容量
// 当且仅当，为最小割时，取等号
#include <cstdio>
#include <cstring>
using namespace std;
const int maxn = 20010;
const int inf = 0x3f3f3f3f;
#define min(a, b) ((a) < (b) ? (a) : (b))

int n, m, s, t;
int lv[maxn];
int egc, head[maxn];
int qf, qb, que[maxn];
struct edge { int v, c, next; } eg[500000];

int add(int u, int v, int c)
{
    eg[egc] = (edge){v, c, head[u]};
    head[u] = egc++;
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
    int a, tot = 0;
    if(u == t) return low;
    for(int p = head[u]; p != -1; p = eg[p].next) {
        int v = eg[p].v, c = eg[p].c;
        if(lv[v]==lv[u]+1 && c>0 && (a=dfs(v, min(c,low)))) {
            eg[p].c -= a, eg[p^1].c += a;
            tot += a;
            if((low -= a) == 0) break;
        }
    }
    return tot;
}

int dinic()
{
    int tmp, ans = 0;
    while(bfs())
        while(tmp = dfs(s, inf))
            ans += tmp;
    return ans;
}

int main()
{
    int a, b, w;
    while(~scanf("%d%d", &n, &m)) {
        egc = 0;
        s = 0, t = n + 1;
        memset(head, -1, sizeof(head));

        for(int i = 1; i <= n; ++i) {
            scanf("%d%d", &a, &b);
            add(s, i, a), add(i, s, 0);
            add(i, t, b), add(t, i, 0);
        }
        for(int i = 1; i <= m; ++i) {
            scanf("%d%d%d", &a, &b, &w);
            add(a, b, w), add(b, a, w);
        }
        printf("%d\n", dinic());
    }
}
