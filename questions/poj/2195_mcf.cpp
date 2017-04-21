// POJ No.2195 最小费用流 (1144K 63MS)
// 建图非常直接：边容量表示人数，边费用表示距离
// 引进源汇点s，t
// s->m 容量1 费用0
// m->h 容量1 费用dis_of(m, h)
// h->t 容量1 费用0
// 求流量为人数时的最小费用流
// dijkstra找费用最小增广路，引进顶点势避免负权边
#include <queue>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 1e4 + 100;
const int inf = 0x3f3f3f3f;
typedef pair<int, int> P;

int r, c, s, t;
vector<P> ms, hs;
int dis[maxn];
int aug[maxn];
int prevv[maxn];   // 指向点的前向星
int preve[maxn];   // 指向边的前向星
int h[maxn];       // 顶点的势
int egc, head[maxn];
struct edge { int v, r, c, next; } eg[maxn * 10];

void addedge(int u, int v, int r, int c)
{
    eg[egc] = (edge){v, r, c, head[u]}; head[u] = egc++;
    eg[egc] = (edge){u, 0, -c, head[v]}; head[v] = egc++;
}

int dijkstra()
{
    priority_queue<P, vector<P>, greater<P> > que;

    for(int i = s; i <= t; ++i) {
        dis[i] = inf;
        h[i] = 0;
    }
    que.push(P(0, s));
    dis[s] = 0;
    aug[s] = inf;
    aug[t] = 0;
    prevv[s] = -1;
    
    while(!que.empty()) {
        P p = que.top(); que.pop();
        int u = p.second;
        if(dis[u] < p.first) continue;
        //if(u == t) break;   // 157ms -> 63ms, but this is wrong
        for(int p = head[u]; ~p; p = eg[p].next) {
            edge &e = eg[p];
            if(e.r > 0 && dis[e.v] > dis[u] + e.c + h[u] - h[e.v]) {
                dis[e.v] = dis[u] + e.c + h[u] - h[e.v];
                prevv[e.v] = u;
                preve[e.v] = p;
                aug[e.v] = min(aug[u], e.r);
                que.push(P(dis[e.v], e.v));
            }
        }
    }
    for(int i = s; i <= t; ++i)
        h[i] += dis[i];
    return aug[t];
}

int solve()
{
    int flow = 0, ans = 0;
    memset(h, 0, sizeof(h));

    while(flow < ms.size()) {
        int a = dijkstra();
        flow += a;
        ans += a * h[t];
        for(int p = t; ~prevv[p]; p = prevv[p])
            eg[preve[p]].r -= a, eg[preve[p]^1].r += a;
    }
    return ans;
}

int dis_of(const P &p1, const P &p2)
{
    return abs(p1.first - p2.first) + abs(p1.second - p2.second);
}

int main()
{
    char ch;

    while(scanf("%d%d", &r, &c) == 2 && r + c) {
        egc = 0;
        ms.clear(), hs.clear();
        memset(head, -1, sizeof(head));

        for(int i = 0; i < r; ++i) {
            for(int j = 0; j < c; ++j) {
                scanf(" %c", &ch);
                if(ch == 'm')
                    ms.push_back(P(i, j));
                else if(ch == 'H')
                    hs.push_back(P(i, j));
            }
        }
        s = 0, t = ms.size() + hs.size() + 1;
        for(int i = 1; i <= ms.size(); ++i)
            addedge(s, i, 1, 0);
        for(int i = 1; i <= hs.size(); ++i)
            addedge(ms.size()+i, t, 1, 0);
        for(int i = 0; i < ms.size(); ++i)
            for(int j = 0; j < hs.size(); ++j)
                addedge(i+1, ms.size()+j+1, 1, dis_of(ms[i], hs[j]));
        printf("%d\n", solve());
    }
}
