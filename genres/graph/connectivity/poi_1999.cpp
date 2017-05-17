// Store-keeper (推箱子)
// https://www.byvoid.com/zhs/blog/poi-1999-mag
#include <bits/stdc++.h>
using namespace std;
const int maxn = 105;
const int maxnode = maxn * maxn;

struct {
    int nc;                 // 点双连通分量数
    int belong[maxnode];    // 某个结点所属的点双分量编号
    bool isCutNode[maxnode];
    int top, stk[maxnode];
    int dfn[maxnode], low[maxnode];
    int egc, head[maxnode];
    struct edge { int v, next; } eg[maxnode * 10];

    void init() {
        top = nc = egc = 0;
        memset(isCutNode, 0, sizeof(isCutNode));
        memset(dfn, 0, sizeof(dfn));
        memset(low, 0, sizeof(low));
        memset(head, -1, sizeof(head));
    }
    void addedge(int u, int v) {
        eg[egc] = (edge){v, head[u]}, head[u] = egc++;
        eg[egc] = (edge){u, head[v]}, head[v] = egc++;
    }
    void dfs(int u, int from, int dep) {
        stk[top++] = u;
        low[u] = dfn[u] = dep;
        for(int p = head[u]; ~p; p = eg[p].next) {
            int v = eg[p].v;
            if(!dfn[v]) {
                dfs(v, u, dep + 1);
                low[u] = min(low[u], low[v]);
                if(low[v] >= dfn[u]) {
                    isCutNode[u] = 1;
                    ++nc;
                    while(stk[top-1] != u)
                        belong[stk[--top]] = nc;
                    belong[u] = nc;
                }
            } else if(v != from) {
                low[u] = min(low[u], dfn[u]);
            }
        }
    }
    void tarjan() { dfs(0, -1, 1); }
} graph;

enum DIRECTION { R, L, D, U };
const char dir[][2] = {{0,1}, {0,-1}, {1,0}, {-1,0}};

int N, M;
int mi, mj;         // 人的起点坐标
int si, sj, ti, tj; // 箱子的起终点坐标
bool vis[maxn][maxn][4];
char storage[maxn][maxn];

struct P {
    int i, j, d;
    P(int i=0, int j=0, int d=0): i(i), j(j), d(d) {}
};
queue<P> que;

void addAdjacentEdge(int i, int j)
{
    for(int k = 0; k < 4; ++k) {
        int ni = i + dir[k][0], nj = j + dir[k][1];
        if(0<=ni&&ni<n && 0<=nj&&nj<n && storage[ni][nj]!='S')
            graph.addedge(i*n+j, ni*n+nj);
    }
}

void init()
{
    graph.init();
    que.clear();
    memset(vis, 0, sizeof(vis));
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            if(storage[i][j] == 'w') {
                addAdjacentEdge(i, j);
            } else if(storage[i][j] == 'P') {
                storage[i][j] = 'w';
                si = i, sj = j;
            } else if(storage[i][j] == 'K') {
                storage[i][j] = 'w';
                ti = i, tj = j;
            } else if(storage[i][j] == 'M') {
                storage[i][j] = 'w';
                mi = i, mj = j;
            }
        }
    }
    graph.tarjan();
}

void getAdjCrd(int i, int j, DIRECTION d, int &ni, int &nj)
{
    ni = i + dir[d][0], nj = j + dir[d][1];
    if(ni<0 || ni>=n || nj<0 || nj>=n) ni = -1, nj = -1;
}

bool belongSameComponent(int i1, int j1, int i2, int j2)
{
    int n1 = i1*n + j1, n2 = i2*n + j2; 
    return graph.belong(n1) == graph.belong(n2);
}

bool isMovable(const P &p, DIRECTION d)
{
    if(p.d == d) return 0;

    int hi, hj, ppi, ppj;
    int pi = p.i, pj = p.j;

    getAdjCrd(pi, pj, p.d, hi, hj);
    getAdjCrd(pi, pj, d, ppi, ppj);
    if(ppi == -1) return 0;
    if(storage[ppi][ppj] != 'w') return 0;

}

int solve()
{
    int ni, nj;

    getAdjCrd(si, sj, U, ni, nj);
    if(ni != -1 && belongSameComponent(mi, mj, ni, nj))
        que.push(P(mi, mj, U));

    getAdjCrd(si, sj, D, ni, nj);
    if(ni != -1 && belongSameComponent(mi, mj, ni, nj))
        que.push(P(mi, mj, D));

    getAdjCrd(si, sj, L, ni, nj);
    if(ni != -1 && belongSameComponent(mi, mj, ni, nj))
        que.push(P(mi, mj, L));

    getAdjCrd(si, sj, R, ni, nj);
    if(ni != -1 && belongSameComponent(mi, mj, ni, nj))
        que.push(P(mi, mj, R));

    while(!que.empty()) {
        P p = que.top(); que.pop();
    }
}

int main()
{
    int T, c;

    for(scanf("%d", &T); T; --T) {
        scanf("%d%d", &N, &M);
        while(isspace(c = getchar()));
        ungetc(c, stdin);
        for(int i = 0; i < N; ++i)
            scanf("%s", storage[i]);
        init();
        int ans = solve();
        if(ans == -1) puts("NO");
        else printf("%d\n", ans);
    }
}
