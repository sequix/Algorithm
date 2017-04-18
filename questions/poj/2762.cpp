// POJ No.2762 Going from u to v or from v to u? (456K 313MS)
// 给一有向图，问其是否是单连通。
// Tarjan对所有的强连通分量缩点，对缩点后的图进行拓扑排序
// 所得到的拓扑排序唯一则代表原图是单连通的
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 1e3 + 10;
const int maxm = 6e3 + 10;

int n, m;
int ncon;       // 代表当前强连通分量数
int depth;      // 当前dfs的深度
int ind[maxn];
int low[maxn];
int dfn[maxn];
int belong[maxn];
int top, stk[maxn];
bool instk[maxn];

// head0原图，head1缩点后的图
int egc, head0[maxn], head1[maxn];
struct edge { int v, next; } eg[maxm * 2];

void addedge(int u, int v, int *head)
{
    eg[egc] = (edge){v, head[u]}, head[u] = egc++;
}

void init()
{
    top = depth = ncon = egc = 0;
    memset(head0, -1, sizeof(head0));
    memset(head1, -1, sizeof(head1));
    memset(ind, 0, sizeof(ind));
    memset(low, 0, sizeof(low));
    memset(dfn, 0, sizeof(dfn));
    memset(belong, 0, sizeof(belong));
    memset(instk, 0, sizeof(instk));
}

void tarjan(int u)
{
    stk[top++] = u;
    instk[u] = 1;
    low[u] = dfn[u] = ++depth;
    for(int p = head0[u]; ~p; p = eg[p].next) {
        int v = eg[p].v;
        if(!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if(instk[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if(low[u] == dfn[u]) {
        int v; ++ncon;
        do {
            v = stk[--top];
            instk[v] = 0;
            belong[v] = ncon;
        } while(u != v);
    }
}

// 找入度为0的点，仅有一个时返回其序号，多个时返回0
int find_zero_degree()
{
    int ret, cnt = 0;
    for(int i = 1; i <= ncon; ++i)
        if(ind[i] == 0) ++cnt, ret = i;
    return cnt == 1 ? ret : 0;
}

bool toposort()
{
    int u, cnt = 0;
    while(u = find_zero_degree()) {
        ++cnt;
        ind[u] = -1;
        for(int p = head1[u]; ~p; p = eg[p].next)
            --ind[eg[p].v];
    }
    return cnt == ncon;
}

bool solve()
{
    // 缩点
    for(int i = 1; i <= n; ++i)
        if(!dfn[i]) tarjan(i);
    if(ncon == 1) return 1; // 强连通图必为单连通图 
    // 构图
    for(int u = 1; u <= n; ++u) {
        int bu = belong[u];
        for(int p = head0[u]; ~p; p = eg[p].next) {
            int v = eg[p].v, bv = belong[v];
            if(bu != bv) {
                addedge(bu, bv, head1);
                ++ind[bv];
            }
        }
    }
    return toposort();
}

int main()
{
    int T, u, v;
    for(scanf("%d", &T); T > 0; --T) {
        init();
        scanf("%d%d", &n, &m);
        for(int i = 0; i < m; ++i) {
            scanf("%d%d", &u, &v);
            addedge(u, v, head0);
        }
        puts(solve() ? "Yes" : "No");
    }
}
