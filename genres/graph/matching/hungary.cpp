// 匈牙利算法(Hungarian Algorithm) 求最大匹配数

// DFS实现 O(VE) 适合稠密图
int nx, ny;         // 左右点集的大小
int cx[maxx];       // cx[x] 与x配对y点 (可省略)
int cy[maxy];       // cy[y] 与y配对x点
int g[maxx][many];  // 对二分图的邻接阵，仅保存从x点到y点的边
bool vis[maxy];     // vis[i] y点i是否被访问过

// 以x为起点找增广路，找得到返回1，否则返回0
// 找左侧点的右侧点进行匹配，若右侧点已被匹配，
// 递归地找该右侧点匹配的左侧点下一个右侧点进行匹配
// 来把当前点需要的右侧点让出来为止
int dfs(int x)
{
    for(int y = 0; y < ny; ++y) {
        if(G[x][y] && !vis[y]) {
            vis[y] = 1;
            if(cy[y] == -1 || dfs(cy[y])) {
                cy[y] = x, cx[x] = y;
                return 1;
            }
        }
    }
    return 0;
}

// 返回最大匹配数
int hungary()
{
    int ans = 0;
    memset(cx, -1, sizeof(cx));
    memset(cy, -1, sizeof(cy));
    for(int x = 0; x < nx; ++x) {
        if(cx[x] == -1) {
            memset(vis, 0, sizeof(vis));
            ans += dfs(x);
        }
    }
    return ans;
}

// BFS实现 O(VE) 适合稀疏图 可增广轨短的
int nx, ny;         // 左右集合的大小
int g[maxx][maxy];  // 保存二分图，点从0开始
int cx[maxx];       // cx[i] 与左点i匹配的右点
int cy[maxy];       // cy[i] 与右点i匹配的左点
bool vis[maxy];     // vis[i] 右点i是否访问过
int pre[maxy];      // pre[i] 增广轨上右点i的前一个右点
int qf, qb, que[maxy];

int maxmatch()
{
    int y, ans = 0;
    memset(cx, -1, sizeof(cx));
    memset(cy, -1, sizeof(cy));

    for(int i = 0; i < nx; ++i) {
        if(cx[i] != -1) continue;
        qf = qb = 0;
        memset(vis, 0, sizeof(vis));
        memset(pre, -1, sizeof(pre));

        for(int j = 0; j < ny; ++j)
            if(G[i][j]) vis[j]=1, que[qb++] = j;

        while(qf < qb) {
            y = que[qf];
            if(cy[y] == -1) break;
            ++qf;
            for(int j = 0; j < ny; ++j)
                if(G[cy[y]][j] && !vis[j])
                    vis[j] = 1, pre[j] = y, que[qb++] = j;
        }
        if(qf == qb) continue;
        while(pre[y] > -1) {
            cx[cy[pre[y]]] = y;
            cy[y] = cy[pre[y]];
            y = pre[y];
        }
        cx[i] = y, cy[y] = i;
        ++ans;
    }
    return ans;
}
