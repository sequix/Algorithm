// POJ No.3713 Transferring Sylla (Tarjan) O(V*(V+E)) (624K 3110MS)
// 判断图是否为3连通图。
// 首先原图要连通。其次
// 因为3连通图满足：“任一对顶点间都至少存在3条没有公共顶点的路”
// 所以在删去任一点后，图中应该没有割点并且依旧连通。
#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 5e2 + 10;
const int maxm = 4e4 + 10;

int n, m;
int low[maxn];
int depth[maxn];
char tag[maxn]; // 0未访问，1已访问，2被删除

int root;
bool has_cut_vertex;

int egc, head[maxn];
struct edge { int v, next; } eg[maxm];

void addedge(int u, int v)
{
    eg[egc] = (edge){v, head[u]}; head[u] = egc++;
    eg[egc] = (edge){u, head[v]}; head[v] = egc++;
}

void tarjan(int u, int from, int dep)
{
    int ns = 0; // 子树个数
    tag[u] = 1;
    low[u] = depth[u] = dep;

    for(int p = head[u]; ~p; p = eg[p].next) {
        int v = eg[p].v;
        if(v == from) continue;

        if(tag[v] == 0) {
            ++ns;
            tarjan(v, u, dep+1);
            if(has_cut_vertex) return;
            low[u] = min(low[u], low[v]);
            if((u==root && ns>1) || (u!=root && low[v]>=depth[u])) {
                has_cut_vertex = 1;
                return;
            }
        } else if(tag[v] == 1) {
            low[u] = min(low[u], depth[v]);
        }
    }
}

bool solve()
{
    for(int i = 0; i < n; ++i) {
        memset(tag, 0, sizeof(tag));
        memset(depth, 0, sizeof(depth));
        memset(low, 0, sizeof(low));

        tag[i] = 2;
        root = (i == 0);
        has_cut_vertex = 0;
        tarjan(root, -1, 0);

        if(has_cut_vertex) return 0;
        for(int i = 0; i < n; ++i)
            if(tag[i] == 0) return 0;
    }
    return 1;
}

int main()
{
    int u, v;
    while(scanf("%d%d", &n, &m)==2 && n+m) {
        egc = 0;
        memset(head, -1, sizeof(head));
        for(int i = 0; i < m; ++i) {
            scanf("%d%d", &u, &v);
            addedge(u, v);
        }
        puts(solve() ? "YES" : "NO");
    }
}
