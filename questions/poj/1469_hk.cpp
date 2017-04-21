// POJ No.1469 二分图最大匹配 Hopcraft-Karp (592K 391MS)
#include <cstdio>
#include <cstring>
using namespace std;
const int inf = 0x3f3f3f3f;

int dis;                // 当前增广轨的长度
int nx, ny;             // 左右集合的大小
int cx[110];            // cx[i] 左i与右cx[i]配对，可以省掉
int cy[310];            // cy[i] 右i与左cy[i]配对
int dx[110];            // 左点集的标号
int dy[310];            // 右点集的标号
bool vis[310];          // vis[i] 右侧i是否被访问过
int qf, qb, que[310];   // 队列中仅会仅右侧点

int egc, head[110];
struct edge { int v, next; } eg[310*310];

void addedge(int u, int v)
{
    eg[egc] = (edge){v, head[u]};
    head[u] = egc++;
}

int bfs()
{
    qf = qb = 0;
    dis = inf;
    memset(dx, -1, sizeof(dx));
    memset(dy, -1, sizeof(dy));

    for(int i = 1; i <= nx; ++i)
        if(cx[i] == -1) que[qb++] = i, dx[i] = 0;
    while(qf < qb) {
        int x = que[qf++];
        if(dx[x] >= dis) break;
        for(int p = head[x]; p != -1; p = eg[p].next) {
            int y = eg[p].v;
            if(dy[y] == -1) {
                dy[y] = dx[x] + 1;
                if(cy[y] == -1)
                    dis = dy[y];
                else
                    dx[cy[y]] = dy[y] + 1, que[qb++] = cy[y];
            }
        }
    }
    return dis != inf;
}

int dfs(int x)
{
    for(int p = head[x]; p != -1; p = eg[p].next) {
        int y = eg[p].v;
        if(!vis[y] && dy[y] == dx[x] + 1) {
            vis[y] = 1;
            if(cy[y] != -1 && dy[y] == dis) continue;
            if(cy[y] == -1 || dfs(cy[y])) {
                cy[y] = x, cx[x] = y;
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
    while(bfs()) {
        memset(vis, 0, sizeof(vis));
        for(int i = 1; i <= nx; ++i)
            if(cx[i] == -1) ans += dfs(i);
    }
    return ans;
}

int main()
{
    int T, nn, u;
    for(scanf("%d", &T); T > 0; --T) {
        scanf("%d%d", &nx, &ny);
        if(ny < nx) { puts("NO"); continue; }

        egc = 0;
        memset(head, -1, sizeof(head));

        for(int i = 1; i <= nx; ++i) {
            for(scanf("%d", &nn); nn > 0; --nn) {
                scanf("%d", &u);
                addedge(i, u);
            }
        }
        puts(maxmatch() >= nx ? "YES" : "NO");
    }
}
