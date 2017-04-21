// POJ No.1466 求图的点独立数 (388K 391MS)
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
const int maxn = 510;

int n;
int match[maxn];
bool vis[maxn];
int egc, head[maxn];
struct edge { int v, next; } eg[maxn * maxn];

void addedge(int u, int v)
{
    eg[egc] = (edge){v, head[u]};
    head[u] = egc++;
}

int dfs(int x)
{
    for(int p = head[x]; p != -1; p = eg[p].next) {
        int y = eg[p].v;
        if(!vis[y]) {
            vis[y] = 1;
            if(match[y] == -1 || dfs(match[y])) {
                match[x] = y;
                match[y] = x;
                return 1;
            }
        }
    }
    return 0;
}

int maxmatch()
{
    int ans = 0;
    memset(match, -1, sizeof(match));
    for(int i = 0; i < n; ++i) {
        if(match[i] < 0) {
            memset(vis, 0, sizeof(vis));
            ans += dfs(i);
        }
    }
    return ans;
}

int main()
{
    int x, y, nn;

    while(scanf("%d", &n) != EOF) {
        egc = 0;
        memset(head, -1, sizeof(head));
        for(int j = 0; j < n; ++j) {
            scanf("%d: (%d)", &x, &nn);
            for(int i = 0; i < nn; ++i) {
                scanf(" %d", &y);
                addedge(x, y);
            }
        }
        printf("%d\n", n - maxmatch());
    }
}
