// POJ No.1469 二分图最大匹配 匈牙利DFS算法O(VE) (408K 469MS)
// 找左侧点的右侧点进行匹配
// 若右侧点已被匹配，递归地找该右侧点匹配的左侧点下一个右侧点进行匹配
// 来把当前点需要的右侧点让出来为止
#include <cstdio>
#include <cstring>
using namespace std;

int p, n;               // 左右集合的大小
bool vis[310];          // vis[i] 右侧i是否被访问过
char G[110][310];       // G[1][1] 代表边 左1->右1，仅保存左到右的边
int cx[110];            // cx[i] 左i与右cx[i]配对，可以省掉
int cy[310];            // cy[i] 右i与左cy[i]配对

int dfs(int u)
{
    for(int i = 1; i <= n; ++i) {
        if(G[u][i] && !vis[i]) {
            vis[i] = 1;
            if(cy[i] == -1 || dfs(cy[i])) {
                cy[i] = u;
                cx[u] = i;
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
    for(int i = 1; i <= p; ++i) {
        if(cx[i] == -1) {
            memset(vis, 0, sizeof(vis));
            ans += dfs(i);
        }
    }
    return ans;
}

int main()
{
    int T, nn, u;
    for(scanf("%d", &T); T > 0; --T) {
        memset(G, 0, sizeof(G));
        scanf("%d%d", &p, &n);
        for(int i = 1; i <= p; ++i) {
            for(scanf("%d", &nn); nn > 0; --nn) {
                scanf("%d", &u);
                G[i][u] = 1;
            }
        }
        puts(maxmatch() >= p ? "YES" : "NO");
    }
}
