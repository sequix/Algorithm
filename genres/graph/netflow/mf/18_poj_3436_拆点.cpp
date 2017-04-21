// POJ No.3436 ACM Computer Factory Dinic+拆点+输出每条路径的具体增广量
#include <map>
#include <cstdio>
#include <cstring>
using namespace std;
const int maxn = 100;
const int maxp = 50;
const int inf = 0x3f3f3f3f;
typedef pair<int, int> P;
#define min(a, b) ((a) < (b) ? (a) : (b))

int n, p, s, t;
int lv[maxn];
int cur[maxn];
int ec, head[maxn];
int qf, qb, que[maxn];
int dev[maxn][maxp];
map<P, int> tab;        // 用于保存增广的路径
struct edge { int v, c, next; } eg[maxn*maxn];

void add(int u, int v, int c)
{
    eg[ec] = (edge){v, c, head[u]}, head[u] = ec++;
    eg[ec] = (edge){u, 0, head[v]}, head[v] = ec++;
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
            if(lv[eg[p].v]==-1 && eg[p].c>0)
                lv[eg[p].v] = lv[u]+1, que[qb++] = eg[p].v;
    }
    return lv[t] != -1;
}

int dfs(int u, int low)
{
    int a;
    if(u == t) return low;
    for(int &p = cur[u]; p != -1; p = eg[p].next) {
        int &v = eg[p].v, &c = eg[p].c;
        if(c>0 && lv[v]==lv[u]+1 && (a=dfs(v,min(low,c)))) {
            eg[p].c -= a, eg[p^1].c += a;
            if(n+1 <= u && u <= 2*n && 1 <= v && v <= n)
                tab[P(u-n, v)] += a;    // 增广和松弛一样是逐步达到的，所以+=
            return a;
        }
    }
    return 0;
}

void solve()
{
    int tmp, maxflow = 0;
    while(bfs()) {
        memcpy(cur, head, sizeof(head));
        while(tmp = dfs(s, inf)) maxflow += tmp;
    }
    printf("%d %d\n", maxflow, tab.size());
    map<P, int>::iterator it = tab.begin();
    for(; it != tab.end(); ++it)
        printf("%d %d %d\n", it->first.first, it->first.second, it->second);
}

int isbeg(int u)
{
    for(int i = 1; i <= p ; ++i)
        if(dev[u][i] == 1) return 0;
    return 1;
}

int isend(int u)
{
    for(int i = p+1; i <= 2*p ; ++i)
        if(dev[u][i] == 0) return 0;
    return 1;
}

int main()
{
    scanf("%d%d", &p, &n);
    for(int i = 1; i <= n; ++i)
        for(int j = 0; j <= 2*p; ++j)
            scanf("%d", &dev[i][j]);
    
    ec = 0, s = 0, t = 2*n + 1;
    memset(head, -1, sizeof(head));

    for(int i = 1; i <= n; ++i)   // 拆点
        add(i, i+n, dev[i][0]);

    for(int i = 1; i <= n; ++i) {
        if(isbeg(i)) add(s, i, inf);
        if(isend(i)) add(n+i, t, inf);
    }

    for(int i = 1; i <= n; ++i) {
        for(int j = 1;  j <= n; ++j) {
            int hasedge = 1;
            for(int k = 1; k <= p; ++k)
                // 有两种情况不能连边<i, j>:
                //      j所需的i没有生产出来, dev[j][k]==1 && dev[i][k+p]==0
                //      i生产出j不需要的部件，dev[j][k]==0 && dev[i][k+p]==1
                if(dev[j][k] + dev[i][p+k] == 1) { hasedge=0; break; }
            if(hasedge) add(n+i, j, inf);
        }
    }
    solve();
}
