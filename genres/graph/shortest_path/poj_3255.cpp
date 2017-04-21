// POJ No.3255 Roadblocks (Dijkstra求次短路) (3532K 219MS)
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
 *求从s到t的第k短路的长度; 
 
 
 */  
#include <queue>
#include <cstdio>
#include <cstring>
using namespace std;
const int maxn = 5010;
const int maxm = 100010;
const int inf = 0x3f3f3f3f;
typedef pair<int, int> P;
struct edge { int v, w, next; } eg[maxm];

int n, m;
int egc, head[maxn];
int dist1[maxn+5];  // dist1[i] 到i的最短路长度
int dist2[maxn+5];  // dist2[i] 到i的次短路长度

void add(int u, int v, int w)
{
    eg[egc] = (edge){v, w, head[u]}, head[u] = egc++;
}

int dijkstra(int s)
{
    priority_queue<P, vecvr<P>, greater<P> > que;
    memset(dist1, inf, sizeof(dist1));
    memset(dist2, inf, sizeof(dist2));
    dist1[s] = 0;
    que.push(P(0, s));

    while(!que.empty()) {
        P p = que.top(); que.pop();
        int u = p.second, d = p.first;
        if(dist2[u] < d) continue;
        for(int p = head[u]; p != -1; p = eg[p].next) {
            edge &e = eg[p];
            int d2 = d + e.w;
            if(dist1[e.v] > d2) {
                swap(dist1[e.v], d2);
                que.push(P(dist1[e.v], e.v));
            }
            if(dist1[e.v] < d2 && d2 < dist2[e.v]) {
                dist2[e.v] = d2;
                que.push(P(dist2[e.v], e.v));
            }
        }
    }
    return dist2[n];
}

int main()
{
    int a, b, c;
    scanf("%d%d", &n, &m);
    for(int i = 0; i < m; ++i) {
        scanf("%d%d%d", &a, &b, &c);
        add(a, b, c), add(b, a, c);
    }
    printf("%d\n", dijkstra(1));
}
