// POJ No.2125 求有向图的最小点权覆盖集 (708K 32MS)
// 转换成求最小割，进而由最大流解决
// 我们找到一个满足条件的割边集(注意不是所有割边， 
// 因为有一条流已经经过了一条割边，那么下面一条割边就不用选了，
// 这样费用才是最小的)，那么就能输出解了。怎么找出割边呢?
// 我们可以在残余网络里走流，如果有一条边是割边，
// 那么之后就流不过去了，不是割边还能继续流，
// 具体实现我们可以从源点S用dfs搜出能走到的点标记vis[] =1，
// 那么对于边<u,v> 只要 vis[u] = 1 && vis[v] = 0 那就是割边了。
#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 110;
const int inf = 0x3f3f3f3f;

int n, m;
vector<int> ans;

int s, t;
int cur[maxn*2];
int lv[maxn*2];
bool vis[maxn*2];
int qf, qb, que[maxn*2];
int egc, head[maxn*2];
struct edge { int v, c, next; } eg[maxn * maxn];

void addedge(int u, int v, int c)
{
    eg[egc] = (edge){v, c, head[u]}; head[u] = egc++;
    eg[egc] = (edge){u, 0, head[v]}; head[v] = egc++;
}

int bfs()
{
    memset(lv, -1, sizeof(lv));
    lv[s] = 0;
    qf = qb = 0;
    que[qb++] = s;
    while(qf < qb && lv[t] == -1) {
        int u = que[qf++];
        for(int p = head[u]; ~p; p = eg[p].next)
            if(lv[eg[p].v] == -1 && eg[p].c > 0)
                lv[eg[p].v] = lv[u] + 1, que[qb++] = eg[p].v;
    }
    return lv[t] != -1;
}

int dfs(int u, int low)
{
    int a;
    if(u == t) return low;
    for(int &p = cur[u]; ~p; p = eg[p].next) {
        int v = eg[p].v, c = eg[p].c;
        if(lv[v]==lv[u]+1 && c > 0 && (a=dfs(v, min(low,c)))) {
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

void dfs2(int u)
{
    vis[u] = 1;
    for(int p = head[u]; ~p; p = eg[p].next) {
        if(!vis[eg[p].v] && eg[p].c > 0)
            dfs2(eg[p].v);
    }
}

int main()
{
    int u, v, x;
    memset(head, -1, sizeof(head));

    scanf("%d%d", &n, &m);
    s = 0, t = 2 * n + 1;
    for(int i = 1; i <= n; ++i) {
        scanf("%d", &x);
        addedge(n+i, t, x); 
    }
    for(int i = 1; i <= n; ++i) {
        scanf("%d", &x);
        addedge(s, i, x);
    }
    for(int i = 0; i < m; ++i) {
        scanf("%d%d", &u, &v);
        addedge(u, n + v, inf);
    }

    printf("%d\n", dinic());
    dfs2(s);
    for(int i = 1; i <= n; ++i) {
        if(vis[s] && !vis[i]) ans.push_back(i);
        if(vis[n+i] && !vis[t]) ans.push_back(n+i);
    }
    printf("%d\n", ans.size());
    for(int i = 0; i < ans.size(); ++i) {
        if(ans[i] <= n)
            printf("%d -\n", ans[i]);
        else
            printf("%d +\n", ans[i]-n);
    }
}
