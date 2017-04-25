// POJ No.3255 Roadblocks (Dijkstra求次短路) (3532K 219MS)
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
