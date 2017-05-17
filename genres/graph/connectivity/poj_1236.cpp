// POJ No.1236 Network of schools (412K 47MS)
// 给定N所学校和网络，目标是分发软件其他学校都可收到，
// 求①所需最少分发学校数；②若任选学校都能收到，最低新增边数。
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 105;

int n, dfscnt, nscc;
int ind[maxn], otd[maxn];
bool instk[maxn];
int belong[maxn];
int top, stk[maxn];
int dfn[maxn], low[maxn];
int egc, head[maxn];
struct edge { int v, next; } eg[maxn * maxn];

void addedge(int u, int v)
{
    eg[egc] = (edge){v, head[u]}, head[u] = egc++;
}

void dfs(int u)
{
    low[u] = dfn[u] = ++dfscnt;
    stk[top++] = u, instk[u] = 1;

    for(int p = head[u]; ~p; p = eg[p].next) {
        int v = eg[p].v;
        if(!dfn[v]) {
            dfs(v);
            low[u] = min(low[u], low[v]);
        } else if(instk[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if(dfn[u] == low[u]) {
        int v; ++nscc;
        do {
            v = stk[--top], instk[v] = 0;
            belong[v] = nscc;
        } while(v != u);
    }
}

int main()
{
    int u, v;
    memset(head, -1, sizeof(head));

    scanf("%d", &n);
    for(u = 1; u <= n; ++u)
        while(scanf("%d", &v)==1 && v != 0)
            addedge(u, v);

    for(u = 1; u <= n; ++u)
        if(!dfn[u]) dfs(u);

    if(nscc == 1) {
        puts("1\n0");
        return 0;
    }

    for(u = 1; u <= n; ++u) {
        int bu = belong[u];
        for(int p = head[u]; ~p; p = eg[p].next) {
            int bv = belong[eg[p].v];
            if(bu != bv) ++otd[bu], ++ind[bv];
        }
    }

    int otd0 = 0, ind0 = 0;
    for(u = 1; u <= nscc; ++u)
        otd0 += (otd[u]==0), ind0 += (ind[u]==0);
    printf("%d\n%d\n", ind0, max(ind0, otd0));
}
