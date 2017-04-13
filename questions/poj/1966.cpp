// POJ No.1966 Cable TV Network (500K 16MS)
// 求无向图的点连通度，转换为网络流问题：
// 将每个点u拆为入点u'，出点u''，并从入点连向出点，容量为1
// 对每条边(u,v)，拆成<u'', v'>和<v'', u'>，容量inf
// 求u''和v'之间的最大流即可得原图中uv间的独立轨数量
// 固定源点，将汇点分别设成除源点的每个点，求最大流，取其中最小的
// 即为原图的点连通度
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 120;
const int inf = 0x3f3f3f3f;

int n, m;
int pre[maxn];
int cap[maxn][maxn];
int bcap[maxn][maxn];
int qf, qb, que[maxn];

int bfs(int s, int t)
{
    int aug = inf;
    qf = qb = 0;
    que[qb++] = s;
    memset(pre, -1, sizeof(pre));

    while(qf < qb && pre[t] == -1) {
        int u = que[qf++];
        for(int v = 0; v < 2*n; ++v) {
            if(pre[v] == -1 && bcap[u][v] > 0) {
                pre[v] = u;
                que[qb++] = v;
                aug = min(aug, bcap[u][v]);
            }
        }
    }
    return pre[t]==-1 ? 0 : aug;
}

int maxflow(int s, int t)
{
    int a, ans = 0;
    memcpy(bcap, cap, sizeof(cap)); 

    while(1) {
        if((a = bfs(s, t)) == 0) break;
        ans += a;
        for(int v = t; v != s; v = pre[v]) {
            bcap[pre[v]][v] -= a;
            bcap[v][pre[v]] += a;
        }
    }
    return ans;
}

int main()
{
    int u, v, s, t, ans;

    while(scanf("%d%d", &n, &m) != EOF) {
        memset(cap, 0, sizeof(cap));

        for(int i = 0; i < n; ++i)
            cap[i][n+i] = 1; 
        for(int i = 0; i < m; ++i) {
            scanf(" (%d,%d)", &u, &v);
            cap[n+u][v] = cap[n+v][u] = inf;
        }

        ans = s = n;
        for(t = 1; t < n; ++t)  // t从1开始，因为0和n是原图中同一个点
            ans = min(ans, maxflow(s, t));
        printf("%d\n", ans);
    }
}
