// POJ No.2449 Remmarguts' Date (A* + spfa 求第K短路) (15292K 313MS)
/* 
 *算法引入： 
 *在单源点最短路径问题中,实际运用时还需知道最短路径外,次短路或者第三短路; 
 *即要知道多条最短路,并排出其长度增加的顺序,即为K最短路问题; 
 * 
 *算法思想： 
 *单源点最短路径+高级搜索A*; 
 *A*算法结合了启发式方法和形式化方法; 
 *启发式方法通过充分利用图给出的信息来动态地做出决定而使搜索次数大大降低; 
 *形式化方法不利用图给出的信息,而仅通过数学的形式分析; 
 * 
 *算法通过一个估价函数f(h)来估计图中的当前点p到终点的距离,并由此决定它的搜索方向; 
 *当这条路径失败时,它会尝试其他路径; 
 *对于A*,估价函数=当前值+当前位置到终点的距离,即f(p)=g(p)+h(p),每次扩展估价函数值最小的一个; 
 * 
 *对于K短路算法来说,g(p)为当前从s到p所走的路径的长度;h(p)为点p到t的最短路的长度; 
 *f(p)的意义为从s按照当前路径走到p后再走到终点t一共至少要走多远; 
 * 
 *为了加速计算,h(p)需要在A*搜索之前进行预处理,只要将原图的所有边反向,再从终点t做一次单源点最短路径就能得到每个点的h(p)了; 
 * 
 *算法步骤： 
 *(1),将有向图的所有边反向,以原终点t为源点,求解t到所有点的最短距离; 
 *(2),新建一个优先队列,将源点s加入到队列中; 
 *(3),从优先级队列中弹出f(p)最小的点p,如果点p就是t,则计算t出队的次数; 
 *如果当前为t的第k次出队,则当前路径的长度就是s到t的第k短路的长度,算法结束; 
 *否则遍历与p相连的所有的边,将扩展出的到p的邻接点信息加入到优先级队列; 
 * 
 *算法测试： 
 *PKU2449(Remmarguts' Date) 
 * 
 *题目大意： 
 *求有向图从s到t的第k短路的长度; 
 *
 * 以上转自：http://blog.csdn.net/jarily/article/details/8871968
 */  
#include <queue>
#include <cstdio>
#include <cstring>
using namespace std;
const int maxn = 1100;
const int maxm = 100100;
const int inf = 0x3f3f3f3f;

struct edge { int v, w, next; } eg[maxm * 2];
struct A {
    int u;  // 当前结点
    int f;  // 启发函数值f(x)
    int g;  // 到前位置的实际代价g(x)
    A(int u, int f, int g): u(u), f(f), g(g) {}
    bool operator < (const A &a) const {
        if(f == a.f) return a.g < g;
        return a.f < f;
    }
};

int n, m;
int h[maxn];    // h[i] 由i到终点的（乐观的）预测代价h(x)
int egc, src, gol, kth;
int head[maxn], rhead[maxn];

void addedge(int u, int v, int w)
{
    eg[egc] = (edge){v, w, head[u]}, head[u] = egc++;
    eg[egc] = (edge){u, w, rhead[v]}, rhead[v] = egc++;
}

// 预处理h(x)
void spfa()
{
    queue<int> que;
    bool inq[maxn] = {0}; 
    memset(h, inf, sizeof(h));

    que.push(gol);
    h[gol] = 0;
    inq[gol] = 1;

    while(!que.empty()) {
        int u = que.front(); que.pop();
        inq[u] = 0;
        for(int p = rhead[u]; ~p; p = eg[p].next) {
            edge &e = eg[p];
            if(h[e.v] > h[u] + e.w) {
                h[e.v] = h[u] + e.w;
                if(!inq[e.v]) que.push(e.v), inq[e.v] = 1;
            }
        }
    }
}

// astar求第k短
int astar()
{
    int k = 0;
    priority_queue<A> que;

    if(src == gol) ++kth;   // 本题中一条边都不经过，不算一条路径
    if(h[src] == inf) return -1;
    que.push(A(src, h[src], 0));

    while(!que.empty()) {
        A a = que.top(); que.pop();
        if(a.u == gol && ++k == kth) return a.g;
        for(int p = head[a.u]; p != -1; p = eg[p].next) {
            edge &e = eg[p];
            que.push(A(e.v, a.g + e.w + h[e.v], a.g + e.w));
        }
    }
    return -1;
}

int main()
{
    int u, v, w;
    memset(head, -1, sizeof(head));
    memset(rhead, -1, sizeof(rhead));

    scanf("%d%d", &n, &m);
    for(int i = 0; i < m; ++i) {
        scanf("%d%d%d", &u, &v, &w);
        addedge(u, v, w);
    }
    scanf("%d%d%d", &src, &gol, &kth);
    spfa();
    printf("%d\n", astar());
}
