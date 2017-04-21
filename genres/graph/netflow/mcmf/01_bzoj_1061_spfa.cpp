// BZOJ No.1061 最小费用最大流
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e3 + 100;
const int maxm = 1e4 + 100;
const int inf = 0x3f3f3f3f;

int s, t;
int n, m;           // n天，m类志愿者
int demand[maxn];   // demand[i] 第i天需要的志愿者数

int aug[maxn];      // aug[v] 到v点为止的最短路中的最小流量
int path[maxn];     // path[v] 指向到v点的边
int pre[maxn];
int dis[maxn];
bool inq[maxn];
int qf, qb, que[maxn];

int egc, head[maxn];
struct edge { int v, r, c, next; } eg[maxm * 4];

// from, to, remaining-capacity, cost
void add(int u, int v, int r, int c)
{
    eg[egc] = (edge){v, r, c, head[u]}; head[u] = egc++;
    eg[egc] = (edge){u, 0, -c, head[v]}; head[v] = egc++;
}

int spfa()
{
    qf = qb = 0;
    for(int i = s; i <= t; ++i) {
        dis[i] = inf;
        inq[i] = 0;
    }

    que[qb++] = s;
    aug[s] = inf;
    aug[t] = 0;
    pre[s] = -1;
    dis[s] = 0;
    inq[s] = 1;

    while(qf < qb) {
        int u = que[qf++];
        inq[u] = 0;
        for(int p = head[u]; ~p; p = eg[p].next) {
            edge &e = eg[p];
            if(e.r > 0 && dis[e.v] > dis[u] + e.c) {
                dis[e.v] = dis[u] + e.c;
                pre[e.v] = u;
                path[e.v] = p;
                aug[e.v] = min(aug[u], e.r);
                if(!inq[e.v]) que[qb++] = e.v, inq[e.v] = 1;
            }
        }
    }
    return aug[t];
}

int solve()
{
    int a, ans = 0;    // 最小费用最大流的费用
    while(a = spfa()) {
        for(int p = t; ~pre[p]; p = pre[p]) {
            int pe = path[p];
            ans += a * eg[pe].c;
            eg[pe].r -= a, eg[pe^1].r += a;
        }
    }
    return ans;
}

int main()
{
    int u, v, c;
    for(int i = 0; i < maxn; ++i)
        head[i] = -1;

    scanf("%d%d", &n, &m);
    s = 0, t = n + 2;
    for(int i = 1; i <= n; ++i)
        scanf("%d", &demand[i]);
    for(int i = 1; i <= m; ++i) {
        scanf("%d%d%d", &u, &v, &c);
        add(u, v+1, inf, c);
    }
    for(int i = 1; i <= n+1; ++i) {
        int r = demand[i] - demand[i-1];
        if(r >= 0) add(s, i, r, 0);
        else add(i, t, -r, 0);
        if(i > 1) add(i, i-1, inf, 0);
    }
    printf("%d\n", solve());
}
