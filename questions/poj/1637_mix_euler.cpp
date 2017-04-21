// POJ No.1637 Sightseeing Tour (混合图欧拉回路) (408K 16MS)
/*
   把该图的无向边随便定向，计算每个点的入度和出度。如果有某个点出入度之差为奇数，那么肯定不存在欧拉回路。因为欧拉回路要求每点入度 = 出度，也就是总度数为偶数，存在奇数度点必不能有欧拉回路。 
   　　好了，现在每个点入度和出度之差均为偶数。那么将这个偶数除以2，得x。也就是说，对于每一个点，只要将x条边改变方向（入>出就是变入，出>入就是变出），就能保证出 = 入。如果每个点都是出 = 入，那么很明显，该图就存在欧拉回路。 
   　　现在的问题就变成了：我该改变哪些边，可以让每个点出 = 入？构造网络流模型。首先，有向边是不能改变方向的，要之无用，删。一开始不是把无向边定向了吗？定的是什么向，就把网络构建成什么样，边长容量上限1。另新建s和t。对于入 > 出的点u，连接边(u, t)、容量为x，对于出 > 入的点v，连接边(s, v)，容量为x（注意对不同的点x不同）。之后，察看是否有满流的分配。有就是能有欧拉回路，没有就是没有。欧拉回路是哪个？察看流值分配，将所有流量非 0（上限是1，流值不是0就是1）的边反向，就能得到每点入度 = 出度的欧拉图。 
   　　由于是满流，所以每个入 > 出的点，都有x条边进来，将这些进来的边反向，OK，入 = 出了。对于出 > 入的点亦然。那么，没和s、t连接的点怎么办？和s连接的条件是出 > 入，和t连接的条件是入 > 出，那么这个既没和s也没和t连接的点，自然早在开始就已经满足入 = 出了。那么在网络流过程中，这些点属于“中间点”。我们知道中间点流量不允许有累积的，这样，进去多少就出来多少，反向之后，自然仍保持平衡。 
*/
#include <cstdio>
#include <cstring>
using namespace std;
const int maxn = 300;
const int inf = 0x3f3f3f3f;
#define min(a, b) ((a) < (b) ? (a) : (b))

int n, m, s, t;
int deg[maxn];          // 每个点的出入度之差
int lv[maxn];
int cur[maxn];
int ec, head[maxn];
int qf, qb, que[maxn];
struct edge { int v, c, next; } eg[maxn*maxn];

void add(int u, int v, int c)
{
    eg[ec] = (edge){v, c, head[u]}, head[u] = ec++;
    eg[ec] = (edge){u, 0, head[v]}, head[v] = ec++;
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
            if(lv[eg[p].v]==-1 && eg[p].c>0)
                lv[eg[p].v] = lv[u]+1, que[qb++] = eg[p].v;
    }
    return lv[t] != -1;
}

int dfs(int u, int low)
{
    int a;
    if(u == t) return low;
    for(int &p = cur[u]; p != -1; p = eg[p].next) {
        int &v = eg[p].v, &c = eg[p].c;
        if(c>0 && lv[v]==lv[u]+1 && (a=dfs(v,min(low,c)))) {
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
        while(tmp = dfs(s, inf)) ans += tmp;
    }
    return ans;
}

void init()
{
    int u, v, d;
    scanf("%d%d", &n, &m);

    ec = 0, s = 0, t = n + 1;
    memset(head, -1, sizeof(head));
    memset(deg, 0, sizeof(deg));

    for(int i = 0; i < m; ++i) {
        scanf("%d%d%d", &u, &v, &d);
        if(d == 0) add(u, v, 1);
        ++deg[u], --deg[v];
    }
}

int judge()
{
    int maxflow = 0;
    for(int i = 1; i <= n; ++i)
        if(deg[i] & 1) return 0;
    for(int i = 1; i <= n; ++i) {
        if(deg[i] > 0) add(s, i, deg[i]/2), maxflow += deg[i]/2;
        else if(deg[i] < 0) add(i, t, -deg[i]/2);
    }
    return maxflow == dinic();
}

int main()
{
    int T;
    for(scanf("%d", &T); T; --T) {
        init();
        puts(judge() ? "possible" : "impossible");
    }
}
