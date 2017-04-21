// POJ No.1087 A Plug for UNIX Dinic (672K 16MS)
#include <map>
#include <string>
#include <cstdio>
#include <cstring>
using namespace std;
const int maxn = 400;
const int inf = 0x3f3f3f3f;
#define min(a, b) ((a) < (b) ? (a) : (b))

int s, t, np, nd, nt;
int lv[maxn];
int cur[maxn];
int egc, head[maxn];
int qf, qb, que[maxn];
struct edge { int v, c, next; } eg[maxn*maxn];

void add(int u, int v, int c)
{
    eg[egc] = (edge){v, c, head[u]}; head[u] = egc++;
    eg[egc] = (edge){u, 0, head[v]}; head[v] = egc++;
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
            if(lv[eg[p].v] == -1 && eg[p].c > 0)
                lv[eg[p].v] = lv[u]+1, que[qb++] = eg[p].v;
    }
    return lv[t] != -1;
}

int dfs(int u, int low)
{
    int a;
    if(u == t) return low;
    for(int &p = cur[u]; p != -1; p = eg[p].next) {
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

int main()
{
    int cnt = 0;
    char dev[30], plg[30];
    egc = s = 0, t = maxn - 1;
    // tab的唯一作用就是string到int的映射
    // 不要让其有其它功能，来扰乱你的思考
    map<string, int> tab;
    memset(head, -1, sizeof(head));

    scanf("%d", &np);
    for(int i = 0; i < np; ++i) {
        scanf("%s", plg);
        if(!tab[plg]) tab[plg] = ++cnt;
        add(tab[plg], t, 1);
    }
    scanf("%d", &nd);
    for(int i = 0; i < nd; ++i) {
        scanf("%s%s", dev, plg);
        if(!tab[dev]) tab[dev] = ++cnt;
        if(!tab[plg]) tab[plg] = ++cnt;
        add(s, tab[dev], 1);
        add(tab[dev], tab[plg], 1);
    }
    scanf("%d", &nt);
    for(int i = 0; i < nt; ++i) {
        scanf("%s%s", dev, plg);
        if(!tab[dev]) tab[dev] = ++cnt;
        if(!tab[plg]) tab[plg] = ++cnt;
        // 不将适配器看为一个顶点，
        // 而将其作为所适配的两种插座间的一条容量无限的边
        // 因为适配器数量无限，所以边的容量无限
        add(tab[dev], tab[plg], inf);
    }
    printf("%d\n", nd - dinic());
}
