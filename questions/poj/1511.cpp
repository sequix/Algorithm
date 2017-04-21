// POJ No.1511 Initation Cards (71080K 6907MS)
#include <queue>
#include <cstdio>
#include <vector>
using namespace std;
typedef long long LL;
const int MAX_V = 1000000;
const int INF = 0x3f3f3f3f;
struct edge {
	int to; LL cost;
	edge(int t, LL c): to(t), cost(c) {}
};
typedef pair<LL, int> P;

int V, E, d[MAX_V+5];
vector<edge> G[MAX_V+5];
int from[MAX_V+5], to[MAX_V+5];
LL cost[MAX_V+5];

void dijkstra(int s)
{
	priority_queue<P, vector<P>, greater<P> > que;

	for(int i = 1; i <= V; ++i)
		d[i] = INF;
	d[s] = 0;
	que.push(P(0, s));
	
	while(!que.empty()) {
		P p = que.top(); que.pop();
		int u = p.second;
		if(d[u] < p.first) continue;
		for(int i = 0; i < G[u].size(); ++i) {
			edge &e = G[u][i];
			if(d[e.to] > d[u] + e.cost) {
				d[e.to] = d[u] + e.cost;
				que.push(P(d[e.to], e.to));
			}
		}
	}

}

int main()
{
	int T;

	for(scanf("%d", &T); T > 0; --T) {
		LL ans = 0;
		scanf("%d%d", &V, &E);

		for(int i = 0; i < E; ++i) {
			scanf("%d%d%lld", &from[i], &to[i], &cost[i]);
			G[from[i]].push_back(edge(to[i], cost[i]));
		}
		// 在原图上求起点到所有点的最短路
		dijkstra(1);
		for(int i = 1; i <= V; ++i)
			ans += d[i];
		for(int i = 1; i <= V; ++i)
			G[i].clear();

		// 在逆图上求所有点到起点的最短路
		for(int i = 0; i < E; ++i)
			G[to[i]].push_back(edge(from[i], cost[i]));
		dijkstra(1);
		for(int i = 1; i <= V; ++i)
			ans += d[i];
		for(int i = 1; i <= V; ++i)
			G[i].clear();

		printf("%lld\n", ans);
	} return 0;
}
