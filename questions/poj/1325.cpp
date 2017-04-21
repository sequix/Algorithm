// POJ No.1325 二分图求点覆盖数 (396K 32MS)
#include <cstdio>
#include <cstring>
using namespace std;
const int maxx = 110;
const int maxy = 110;

int nx, ny, k;
int cx[maxx];
int cy[maxy];
bool vis[maxy];
int egc, head[maxx];
struct edge { int v, next; } eg[maxx * maxy];

void addedge(int x, int y)
{
    eg[egc] = (edge){y, head[x]};
    head[x] = egc++;
}

int dfs(int x)
{
    for(int p = head[x]; p != -1; p = eg[p].next) {
        int y = eg[p].v;
        if(!vis[y]) {
            vis[y] = 1;
            if(cy[y] == -1 || dfs(cy[y])) {
                cx[x] = y, cy[y] = x;
                return 1;
            }
        }
    }
    return 0;
}

int maxmatch()
{
    int ans = 0;
    memset(cx, -1, sizeof(cx));
    memset(cy, -1, sizeof(cy));
    for(int x = 1; x <= nx; ++x) {
        if(cx[x] == -1) {
            memset(vis, 0, sizeof(vis));
            ans += dfs(x);
        }
    }
    return ans;
}

int main()
{
    int no, x, y;
    while(scanf("%d", &nx) != EOF && nx) {
        egc = 0;
        memset(head, -1, sizeof(head));
        scanf("%d%d", &ny, &k);
        for(int i = 0; i < k; ++i) {
            scanf("%d%d%d", &no, &x, &y);
            // 机器最初工作在0模式，不需要重启
            // 所以忽略所有X0和Y0的边
            if(x && y) addedge(x, y);
        }
        printf("%d\n", maxmatch());
    }
}
