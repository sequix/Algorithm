// HDU No.3790 最短路径问题
#include <cstdio>
#include <cstring>
using namespace std;

bool used[1001];
int V, E, G[1001][1001][2], dis[1001][2];

void dijkstra(int s, int t)
{
	memset(used, 0, sizeof(used));
	for(int i = 1; i <= V; ++i) {
		G[i][i][0] = G[i][i][1] = 0;
		dis[i][0] = G[i][s][0];
		dis[i][1] = G[i][s][1];
	}
	used[s] = 1;
	dis[V+1][0] = dis[V+1][1] = 0x3f3f3f3f;
	for(int i = 1; i < V; ++i) {
		int u = V + 1;
		for(int j = 1; j <= V; ++j)
			if(!used[j] && dis[j][0] < dis[u][0])
				u = j;
		used[u] = 1;
		for(int j = 1; j <= V; ++j) {
			if(!used[j] && (dis[j][0]>dis[u][0]+G[u][j][0] ||
						dis[j][0]==dis[u][0]+G[u][j][0] &&
						dis[j][1]>dis[u][1]+G[u][j][1])) {
				dis[j][0] = dis[u][0] + G[u][j][0];
				dis[j][1] = dis[u][1] + G[u][j][1];
			}
		}
	}
}

int main()
{
	int s, t, a, b, d1, d2;

	while(~scanf("%d%d", &V, &E), V+E) {
		memset(G, 0x3f, sizeof(G));
		for(int i = 0; i < E; ++i) {
			scanf("%d%d%d%d", &a, &b, &d1, &d2);
			if(G[a][b][0]>d1 || (G[a][b][0]==d1 && G[a][b][1]>d2)) {
				G[a][b][0] = G[b][a][0] = d1;
				G[a][b][1] = G[b][a][1] = d2;
			}
		}
		scanf("%d%d", &s, &t);
		dijkstra(s, t);
		printf("%d %d\n", dis[t][0], dis[t][1]);
	}
	return 0;
}
