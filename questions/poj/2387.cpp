// POJ No.2387 Til the Cows Come Home (dijkstra) (4504K 32MS)
#include <queue>
#include <cstdio>
using namespace std;
const int MAX_V = 1000;
const int INF = 0x3f3f3f3f;
typedef pair<int, int> P;

int V, E, G[MAX_V+5][MAX_V+5];

int dijkstra(int s, int t)
{
	int d[MAX_V+5];
	priority_queue<P, vector<P>, greater<P> > que;

	for(int i = 1; i <= V; ++i)
		d[i] = INF;
	d[s] = 0;
	que.push(P(0, s));

	while(!que.empty()) {
		P p = que.top(); que.pop();
		int u = p.second;
		if(u == t) break;
		if(d[u] < p.first) continue;
		for(int i = 1; i <= V; ++i) {
			if(d[i] > d[u] + G[u][i]) {
				d[i] = d[u] + G[u][i];
				que.push(P(d[i], i));
			}
		}
	}
	return d[t];
}

int main()
{
	int a, b, c;

	while(~scanf("%d%d", &E, &V)) {
		for(int i = 1; i <= V; ++i)
			for(int j = 1; j <= V; ++j)
				G[i][j] = INF;
		for(int i = 0; i < E; ++i) {
			scanf("%d%d%d", &a, &b, &c);
			if(c < G[a][b]) G[a][b] = G[b][a] = c;
		}
		printf("%d\n", dijkstra(V, 1));
	}
	return 0;
}
