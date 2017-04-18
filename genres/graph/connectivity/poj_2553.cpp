// POJ No.2553 The Bottom of a Graph (704K 79MS)
// 给一有向图，求由自身出发能到达的点都能到达自身的点。
// Tarjan对所有的强连通分量缩点，求缩点后图中出度为0的点
#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 5e3 + 10;

int n, m;
int nscc;
int dfscnt;
int otd[maxn];
int low[maxn];
int dfn[maxn];
int belong[maxn];
int top, stk[maxn];
bool instk[maxn];

int egc, head[maxn];
struct edge { int v, next; } eg[maxn * maxn];

void addedge(int u, int v)
{
    eg[egc] = (edge){v, head[u]}, head[u] = egc++;
}

void init()
{
    top = dfscnt = nscc = egc = 0;
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
    low[u] = dfn[u] = ++dfscnt;
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
    // 统计缩点后图的出度
    for(int u = 1; u <= n; ++u) {
        int bu = belong[u];
        for(int p = head[u]; ~p; p = eg[p].next) {
            int v = eg[p].v, bv = belong[v];
            if(bu != bv) ++otd[bu];
        }
    }
    bool fir = 1;
    for(int u = 1; u <= n; ++u) {
        if(!otd[belong[u]]) {
            if(fir) fir = 0;
            else putchar(' ');
            printf("%d", u);
        }
    }
    putchar(10);
}

int main()
{
    int u, v;
    while(scanf("%d", &n) == 1 && n) {
        init();
        scanf("%d", &m);
        for(int i = 0; i < m; ++i) {
            scanf("%d%d", &u, &v);
            addedge(u, v);
        }
        solve();
    }
}
