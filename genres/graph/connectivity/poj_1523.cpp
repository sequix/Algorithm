// POJ No.1523 SPF (Tarjan求割点) O(V+E) (1164K 0MS)
// 给一张无向图，求所有割点，和每个割点会将图分成几个连通分量
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXN = 1005;

int V, son[MAXN];
bool G[MAXN][MAXN], vis[MAXN];
// low[u] u或u的子女通过回边可到达的最小深度
int low[MAXN], depth[MAXN];

void dfs(int u, int dep)
{
    vis[u] = 1;
    low[u] = depth[u] = dep;    // 默认情况，为u的深度
    for(int i = 1; i <= V; ++i) {
        if(!G[u][i]) continue;
        if(vis[i]) {  // 回边的情况
            low[u] = min(low[u], depth[i]);
        } else {
            dfs(i, dep+1);
            low[u] = min(low[u], low[i]);   // 存在子女的情况
            // 无法通过子女返回原来的层次，即u分割了i所连接的部分
            if(low[i] >= depth[u]) ++son[u];
        }
    }
}

int main()
{
	int u, v, kase = 1;

	while(1) {
		scanf("%d", &u); if(u == 0) break; scanf("%d", &v);
		V = max(u, v);
		G[u][v] = G[v][u] = 1;
		while(1) {
			scanf("%d", &u); if(u == 0) break; scanf("%d", &v);
			V = max(V, max(u, v));
			G[u][v] = G[v][u] = 1;
		}
		dfs(1, 0);
		// 判断根节点是否为割点，仅需其子女的个数是否大于1
		// 并且将根删掉后，会有子女数个的连通分量
		// 这与将非根顶点删掉有子女数加1个不同，所以减1
		son[1] = (son[1] > 1) ? son[1] - 1: 0;

		bool found = false;
		if(kase > 1) putchar('\n');
		printf("Network #%d\n", kase++);
		for(int i = 1; i <= V; ++i) {
			if(son[i]) {
				found = true;
				printf("  SPF node %d leaves %d subnets\n", i, son[i] + 1);
			}
		}
		if(!found) puts("  No SPF nodes");

		for(int i = 1; i <= V; ++i) {
			depth[i] = vis[i] = low[i] = son[i] = 0;
			for(int j = 1; j <= V; ++j) G[i][j] = 0;
		}
	}
}
