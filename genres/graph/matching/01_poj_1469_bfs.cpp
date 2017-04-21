// POJ No.1469 二分图最大匹配 匈牙利BFS算法O(VE) (412K 610MS)
// 找可增广轨，增广，直到没有增广轨，或所有点都由匹配
// 二分图分左右集合，习惯上左集合大小 <= 右集合大小
// 可以将vis和pre和在一起，
// 当pre[i] == -2表示没有访问，-1表示有访问但还没有前向右侧点
// >=0表示pre[i]其前向右侧点
#include <cstdio>
#include <cstring>
using namespace std;

int p, n;               // 左右集合的大小
char G[110][310];       // G[1][1] 代表边 左1->右1，仅保存左到右的边
int cx[110];            // cx[i] 左i与右cx[i]配对，可以省掉
int cy[310];            // cy[i] 右i与左cy[i]配对
bool vis[310];          // vis[i] 右侧i是否被访问过，
int pre[310];           // pre[i] 表示可增广轨中的右侧点i的前一个右侧点
int qf, qb, que[310];   // 队列中仅会仅右侧点

int maxmatch()
{
    int y, ans = 0;
    memset(cx, -1, sizeof(cx));
    memset(cy, -1, sizeof(cy));

    for(int i = 1; i <= p; ++i) {
        if(cx[i] != -1) continue;   // 从未盖点开始找增广轨
        qf = qb = 0;
        memset(vis, 0, sizeof(vis));
        memset(pre, -1, sizeof(pre));

        for(int j = 1; j <= n; ++j)
            if(G[i][j]) vis[j] = 1, que[qb++] = j;

        while(qf < qb) {
            y = que[qf];
            if(cy[y] == -1) break;  // 找到增广轨（又遇到一个未盖点)
            ++qf;
            // 没找到增广轨，即：
            // y是以个右侧点，其是一个右侧点
            // 所以cy[y]为与其配对的左侧点
            // 从该左侧点将所有没有访问过的右侧点入队
            // 继续寻找增广轨（未盖点）
            for(int j = 1; j <= n; ++j)
                if(!vis[j] && G[cy[y]][j])
                    vis[j] = 1, pre[j] = y, que[qb++] = j;
        }
        if(qf >= qb) continue;  // 每又找到增广轨
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
