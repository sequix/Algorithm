// POJ No.3164 Command Network (朱刘算法) (680K 219MS)
// 给有向图，求其最小树形图。
#if 0
最小树形图，就是给有向带权图中指定一个特殊的点root，
求一棵以root为根的有向生成树T，并且T中所有边的总权值最小。
最小树形图的第一个算法是1965年朱永津和刘振宏
提出的复杂度为O(VE)的算法。

判断是否存在树形图的方法很简单，
只需要以v为根作一次图的遍历就可以了，
所以下面的算法中不再考虑树形图不存在的情况。

在所有操作开始之前，我们需要把图中所有的自环全都清除。
很明显，自环是不可能在任何一个树形图上的。
只有进行了这步操作，总算法复杂度才真正能保证是O(VE)。

首先为除根之外的每个点选定一条入边，
这条入边一定要是所有入边中最小的。
现在所有的最小入边都选择出来了， 如果这个入边集不存在有向环的话，
我们可以证明这个集合就是该图的最小树形图。这个证明并不是很难。
如果存在有向环的话，我们就要将这个有向环所称一个人工顶点，
同时改变图中边的权。假设某点u在该环上，
并设这个环中指向u的边权是in[u]，那么对于每条从u出发的边(u, i, w)，
在新图中连接(new, i, w)的边，其中new为新加的人工顶点;
对于每条进入u的边(i, u, w)，在新图中建立边(i, new, w-in[u])的边。
然后可以证明，新图中最小树形图的权加上旧图中被收缩的那个环的权和，
就是原图中最小树形图的权。

说明一下为什么出边的权不变，入边的权要减去in [u]。
对于新图中的最小树形图T，设指向人工节点的边为e。
将人工节点展开以后，e指向了一个环。假设原先e是指向u的，
这个时候我们将环上指向u的边 in[u]删除，
这样就得到了原图中的一个树形图。我们会发现，
如果新图中e的权w'(e)是原图中e的权w(e)减去in[u]权的话，
那么在我们删除掉in[u]，并且将e恢复为原图状态的时候，
这个树形图的权仍然是新图树形图的权加环的权，
而这个权值正是最小树形图的权值。所以在展开节点之后，
我们得到的仍然是最小树形图。逐步展开所有的人工节点，
就会得到初始图的最小树形图了。

如果实现得很聪明的话，可以达到找最小入边O(E)，找环 O(V)，收缩O(E)，
其中在找环O(V)这里需要一点技巧。这样每次收缩的复杂度是O(E)，
然后最多会收缩几次呢？由于我们一开始已经拿掉了所有的自环，
我门可以知道每个环至少包含2个点，收缩成1个点之后，总点数减少了至少1。
当整个图收缩到只有1个点的时候，最小树形图就不不用求了。
所以我们最多只会进行V-1次的收缩，所以总得复杂度自然是O(VE)了。
由此可见，如果一开始不除去自环的话，理论复杂度会和自环的数目有关。

转载自：http://blog.sina.com.cn/s/blog_6af663940100ls4h.html
#endif // comment
#include <cmath>
#include <cstdio>
#include <cstring>
using namespace std;
const int maxn = 1e2 + 10;
const int maxm = 1e4 + 10;
const double inf = 1e15;

int n, m;
int vis[maxn];      // vis[v] 表示在判环时v点是由哪个点进入的
int id[maxn];       // 缩点后的图中每个点的编号
int pre[maxn];      // pre[u] u的最小权值入边的起点，即u的前驱
double in[maxn];    // in[u] u的入边中的最小权值
double x[maxn], y[maxn];
struct edge { int u, v; double w; } eg[maxm];

double zhuliu(int root)
{
    double ans = 0.0;
    while(1) {
        // 初始化
        for(int i = 0; i < n; ++i) in[i] = inf;
        // 找最小入边，并删除自环
        for(int i = 0; i < m; ++i) {
            double w = eg[i].w;
            int u = eg[i].u, v = eg[i].v;
            if(w < in[v] && u != v) in[v] = w, pre[v] = u;
        }
        // 判断图是否连通
        for(int i = 0; i < n; ++i) {
            if(i == root) continue;
            if(in[i] == inf) return -1;
        }
        // 找环，并缩点
        int cnt = 0;    // 用于给环标号，即缩点用
        memset(id, -1, sizeof(id));
        memset(vis, -1, sizeof(vis));
        in[root] = 0;
        for(int i = 0; i < n; ++i) {
            ans += in[i];
            int v = i;
            while(vis[v] != i && id[v] == -1 && v != root) {
                vis[v] = i;
                v = pre[v];
            }
            // 找到自环，即vis[v] == i
            if(v != root && id[v] == -1) {
                // 注意i可能不再环中，所以从pre[v]开始
                for(int u = pre[v]; u != v; u = pre[u])
                    id[u] = cnt;
                id[v] = cnt++;
            }
        }
        // 若没有环，则代表找到了最小树形图
        if(cnt == 0) break;
        // 给不在环中的点编号
        for(int i = 0; i < n; ++i)
            if(id[i] == -1) id[i] = cnt++;
        // 调整边中的编号、权值，和总点数、根编号
        for(int i = 0; i < m; ++i) {
            int v = eg[i].v;
            eg[i].u = id[eg[i].u];
            eg[i].v = id[eg[i].v];
            if(eg[i].u != eg[i].v)
                eg[i].w -= in[v];
        }
        n = cnt;
        root = id[root];
    }
    return ans;
}

int main()
{
    int u, v;
    while(scanf("%d%d", &n, &m) != EOF) {
        for(int i = 0; i < n; ++i)
            scanf("%lf%lf", &x[i], &y[i]);
        for(int i = 0; i < m; ++i) {
            scanf("%d%d", &u, &v); --u, --v;
            eg[i] = (edge){u, v, hypot(x[u]-x[v], y[u]-y[v])};
        }
        double ans = zhuliu(0);
        if(ans < 0)
            puts("poor snoopy");
        else
            printf("%.2f\n", ans);
    }
}
