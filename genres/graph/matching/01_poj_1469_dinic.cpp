// POJ No.1469 二分图最大匹配 dinic O(V^2 * E) (1108K 516MS)
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 1e3;
const int maxm = 1e5;
const int inf = 0x3f3f3f3f;

int s, t;
int n, p;
int lv[maxn];
int cur[maxn];
int qf, qb, que[maxn];
int egc, head[maxn];
struct edge { int v, c, next; } eg[maxm];

void addedge(int u, int v, int c)
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
            if(lv[eg[p].v]==-1 && eg[p].c > 0)
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
        if(lv[v]==lv[u]+1 && c>0 && (a=dfs(v,min(low,c)))) {
            eg[p].c -= a, eg[p^1].c += a;
            return a;
        }
    }
    return 0;
}

int dinic()
{
    int tmp, ans = 0;
    while(bfs()) {
        memcpy(cur, head, sizeof(head));
        while(tmp = dfs(s, inf))
            ans += tmp;
    }
    return ans;
}

int main()
{
    int T, nn, v;

    for(scanf("%d", &T); T > 0; --T) {
        egc = 0;
        memset(head, -1, sizeof(head));

        scanf("%d%d", &p, &n);
        for(int i = 1; i <= p; ++i) {
            scanf("%d", &nn);
            while(nn-- > 0) {
                scanf("%d", &v);
                addedge(v, 500+i, 1);
            }
        }

        s = 901, t = 902;
        for(int i = 1; i <= n; ++i)
            addedge(s, i, 1);
        for(int i = 1; i <= p; ++i)
            addedge(500+i, t, 1);
        puts(dinic() >= p ? "YES" : "NO");
    }
}
