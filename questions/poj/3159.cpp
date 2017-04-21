// POJ No.3159 Candies (dijkstra) (3204K 1454MS)
#include <queue>
#include <cstdio>
#include <vector>
using namespace std;
const int MAX_V = 30000;
const int inf = 0x3f3f3f3f;
typedef pair<int, int> P;
struct edge {
	int to, cost;
	edge(int t=0, int c=0): to(t), cost(c) {}
};
typedef vector<edge> VCT_EDGE;

int V, E, d[MAX_V+5];
vector<VCT_EDGE> G(MAX_V+5);

int dijkstra()
{
	priority_queue<P, vector<P>, greater<P> > que;

	for(int i = 1; i <= V; ++i)
		d[i] = inf;
	d[1] = 0;
	que.push(P(0, 1));

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
	return d[V];
}

int main()
{
	int a, b, c;

	scanf("%d%d", &V, &E);
	for(int i = 0; i < E; ++i) {
		scanf("%d%d%d", &a, &b, &c);
		G[a].push_back(edge(b, c));
	}
	printf("%d\n", dijkstra());
	return 0;
}
