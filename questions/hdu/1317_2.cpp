// HDU No.1317 XYZZY (floyd+bellman_ford+另一种判断正环的方法) (109MS 1564K)
#include <cstdio>
using namespace std;
const int MAX_V = 100;
const int INF = 0x3f3f3f3f;
struct edge { int from, to, cost; };

int V, E;
int G[MAX_V+5][MAX_V+5];
edge es[MAX_V*MAX_V];
int energy[MAX_V+5];			// energy[i] i房间的能量
int doors[MAX_V+5][MAX_V+5];	// doors[i][0] i房间的门数n，doors[i][1-n]门通向

void floyd()
{
	for(int k = 0; k < V; ++k)
		for(int i = 0; i < V; ++i)
			for(int j = 0; j < V; ++j)
				G[i][j] = G[i][j] || (G[i][k] && G[k][j]);
}

bool bellman_ford(int s, int t)
{
	int d[MAX_V+5], cnt[MAX_V+5] = {0};

	for(int i = 0; i <= V; ++i)
		d[i] = -INF;
	d[s] = 0;
	++cnt[s];

	while(true) {
		bool update = false;
		for(int j = 0; j < E; ++j) {
			edge &e = es[j];
			if(d[e.from] + e.cost > 0 && d[e.to] < d[e.from] + e.cost) {
				d[e.to] = d[e.from] + e.cost;
				if(++cnt[e.to] >= V) return G[e.to][t];
				update = true;
			}
		}
		if(!update) break;
	}
	return d[t] > 0;
}

int main()
{
	while(~scanf("%d", &V) && V != -1) {
		for(int i = 1; i <= V; ++i) {
			scanf("%d%d", &energy[i], &doors[i][0]);
			for(int j = 1; j <= doors[i][0]; ++j)
				scanf("%d", &doors[i][j]);
		}

		E = 0;
		for(int i = 1; i < V; ++i)
			for(int j = 1; j <= doors[i][0]; ++j) {
// 每条边的权值是边所指向的节点的能量
				es[E].from = i;
				es[E].to = doors[i][j];
				es[E++].cost = energy[doors[i][j]];
			}
// 在图前多加一个0节点指向1节点，0到1边的权值为100
		++V;
		es[E].from = 0;
		es[E].to = 1;
		es[E++].cost = 100;

		for(int i = 0; i < V; ++i)
			for(int j = 0; j < V; ++j)
				G[i][j] = (i == j);
		for(int i = 0; i < E; ++i)
			G[es[i].from][es[i].to] = 1;

// 存在正环不代表可以走到终点，所以要先用floyd判断连通性
		floyd();
		if(G[1][V-1] == 0) {
			printf("hopeless\n");
			continue;
		}
// 再用belman_ford判断是否有正环
		if(bellman_ford(0, V-1)) printf("winnable\n");
		else printf("hopeless\n");
	}
	return 0;
}
