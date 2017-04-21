// POJ No.3422 最小费用最大流 (820K 47MS)
// 将原问题以网络流的流量限制和最小费用流的最优解特性解之
// 1->1'的容量为1限制每个点仅会获得一次分数
// 给1->1'加容量为inf，费用为0平行边保证一个点可以被走多次
// 通过x到x右和x下的容量为inf，费用为0边实现向右和下行走
// 以点数的相反数为1->1'边权保证最小费用的相反数为最大SUM
// 以(0,0)的入店和(n-1, n-1)的出点为源汇点
// 现在只需要跑一边最小费用流，取在最大流为K时的最小费用的相反数即可
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 5000;
const int inf = 0x3f3f3f3f;

int n, k, s, t;
int aug[maxn];
int pre[maxn];
int dis[maxn];
int path[maxn];
bool inq[maxn];
int qf, qb, que[maxn];

int egc, head[maxn];
struct edge { int v, r, c, next; } eg[maxn * 5];

// from, to, remaining-capacity, cost
void add(int u, int v, int r, int c)
{
    eg[egc] = (edge){v, r, c, head[u]}; head[u] = egc++;
    eg[egc] = (edge){u, 0, -c, head[v]}; head[v] = egc++;
}

int spfa()
{
    qf = qb = 0;
    memset(dis, inf, sizeof(dis));
    memset(inq, 0, sizeof(inq));

    que[qb] = s;
    qb = (qb + 1) % maxn;
    inq[s] = 1;
    dis[s] = 0;
    pre[s] = -1;
    aug[s] = inf;
    aug[t] = 0;

    while(qf != qb) {
        int u = que[qf];
        qf = (qf + 1) % maxn;
        inq[u] = 0;

        for(int p = head[u]; ~p; p = eg[p].next) {
            edge &e = eg[p];
            if(e.r > 0 && dis[e.v] > dis[u] + e.c) {
                dis[e.v] = dis[u] + e.c;
                pre[e.v] = u;
                path[e.v] = p;
                aug[e.v] = min(aug[u], e.r);
                if(!inq[e.v]) {
                    que[qb] = e.v;
                    qb = (qb + 1) % maxn;
                    inq[e.v] = 1;
                }
            }
        }
    }
    return aug[t];
}

int min_cost_flow()
{
    int a;
    int maxflow = 0;
    int ans = 0;
    while(a = spfa()) {
        for(int p = t; ~pre[p]; p = pre[p]) {
            int pe = path[p];
            eg[pe].r -= a, eg[pe^1].r += a;
            ans += eg[pe].c * a;
        }
        maxflow += a;
        if(maxflow == k) break;
    }
    return ans;
}

int id_of(int r, int c, bool out)
{
    return r * n + c + out * (n*n);
}

int main()
{
    int x;
    memset(head, -1, sizeof(head));

    scanf("%d%d", &n, &k);
    s = id_of(0, 0, 0), t = id_of(n-1, n-1, 1);
    for(int r = 0; r < n; ++r) {
        for(int c = 0; c < n; ++c) {
            scanf("%d", &x);
            add(id_of(r, c, 0), id_of(r, c, 1), 1, -x);
            add(id_of(r, c, 0), id_of(r, c, 1), k, 0);
            if(r + 1 < n)
                add(id_of(r, c, 1), id_of(r+1, c, 0), k, 0);
            if(c + 1 < n)
                add(id_of(r, c, 1), id_of(r, c+1, 0), k, 0);
        }
    }
    printf("%d\n", -min_cost_flow());
}
