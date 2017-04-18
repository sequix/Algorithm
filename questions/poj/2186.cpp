// POJ No.2186 Popular Cows (1140K 47MS)
// 给一有向图，问能被其他所有点到达的的点的个数。
// Tarjan对所有的强连通分量缩点
// 若新图中仅有一个叶子结点，则该结点在原图中对应的点均符合条件
// 若新图中不止一个叶子，则没有满足条件的节点
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 1e4 + 10;
const int maxm = 5e4 + 10;

int n, m;
int nscc;       // 代表当前强连通分量数
int depth;      // 当前dfs的深度
int otd[maxn];
int low[maxn];
int dfn[maxn];
int belong[maxn];
int top, stk[maxn];
bool instk[maxn];

int egc, head[maxn];
struct edge { int v, next; } eg[maxm * 2];

void addedge(int u, int v)
{
    eg[egc] = (edge){v, head[u]}, head[u] = egc++;
}

void init()
{
    top = depth = nscc = egc = 0;
    memset(head, -1, sizeof(head));
    memset(otd, 0, sizeof(otd));
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
    for(int p = head[u]; ~p; p = eg[p].next) {
        int v = eg[p].v;
        if(!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if(instk[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if(low[u] == dfn[u]) {
        int v; ++nscc;
        do {
            v = stk[--top];
            instk[v] = 0;
            belong[v] = nscc;
        } while(u != v);
    }
}

int solve()
{
    // 缩点
    for(int i = 1; i <= n; ++i)
        if(!dfn[i]) tarjan(i);
    if(nscc == 1) return n;
    // 构图
    for(int u = 1; u <= n; ++u) {
        int bu = belong[u];
        for(int p = head[u]; ~p; p = eg[p].next) {
            int v = eg[p].v, bv = belong[v];
            if(bu != bv) ++otd[bu];
        }
    }
    int pz, nz = 0;
    for(int i = 1; i <= nscc; ++i)
        if(otd[i] == 0) ++nz, pz = i;
    if(nz != 1) return 0;
    return count(belong+1, belong+n+1, pz);
}

int main()
{
    int u, v;
    init();
    scanf("%d%d", &n, &m);
    for(int i = 0; i < m; ++i) {
        scanf("%d%d", &u, &v);
        addedge(u, v);
    }
    printf("%d\n", solve());
}
