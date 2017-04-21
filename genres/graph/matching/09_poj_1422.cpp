// POJ No.1422 DAG的最小不相交路径覆盖数 (392K 0MS)
#include <cstdio>
#include <cstring>
using namespace std;
const int maxn = 128;

int n, m;
int cy[maxn];
bool vis[maxn];
int egc, head[maxn];
struct edge { int v, next; } eg[maxn*maxn];

void add(int u, int v)
{
    eg[egc] = (edge){v, head[u]};
    head[u] = egc++;
}

int dfs(int x)
{
    for(int p = head[x]; ~p; p = eg[p].next) {
        int y = eg[p].v;
        if(!vis[y]) {
            vis[y] = 1;
            if(cy[y] == -1 || dfs(cy[y])) {
                cy[y] = x;
                return 1;
            }
        }
    }
    return 0;
}

int maxmatch()
{
    int ans = 0;
    memset(cy, -1, sizeof(cy));
    for(int x = 1; x <= n; ++x) {
        memset(vis, 0, sizeof(vis));
        ans += dfs(x);
    }
    return ans;
}

int main()
{
    int T, u, v;
    for(scanf("%d", &T); T > 0; --T) {
        egc = 0;
        memset(head, -1, sizeof(head));
        scanf("%d%d", &n, &m);
        for(int i = 0; i < m; ++i) {
            scanf("%d%d", &u, &v);
            add(u, v);
        }
        printf("%d\n", n - maxmatch());
    }
}
