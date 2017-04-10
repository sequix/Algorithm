// Hopcraft-Karp O(sqrt(V) * E)
int egc, head[maxy];
struct edge { int v, next; } eg[maxm];

void addedge(int u, int v)
{
    eg[egc] = (edge){v, head[u]};
    head[u] = egc++;
}

int dis;            // 当前增广路的长度
int nx, ny;         // 左右点集的大小
int cx[maxx];       // cx[i] 与左点i匹配的右点
int cy[maxy];       // cy[i] 与右点i匹配的左点
int dx[maxx];       // dx[i] 左点i在某条增广路中距起点的距离
int dy[maxy];       // dy[i] 点i在某条增广路中距起点的距离
int qf, qb, que[maxy];  // que中仅放左点
bool vis[maxy];         // vis[i] 右点i是否访问过

// 每次使用调用BFS查找到多条增广路的路径长度都是相等的
// 且都以第一次得到的dis为该次查找增广路径的最大长度。
int bfs()
{
    dis = inf;
    qf = qb = 0;
    memset(dx, -1, sizeof(dx));
    memset(dy, -1, sizeof(dy));

    for(int x = 0; x < nx; ++x)
        if(cx[x] == -1) dx[x] = 0, que[qb++] = x;

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
        for(int x = 0; x < nx; ++x)
            if(cx[x] == -1) ans += dfs(x);
    }
    return ans;
}
