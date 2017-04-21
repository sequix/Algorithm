// HDU No.2680 (Dijkstra+逆向建图) (358MS 5432K)
#include <queue>
#include <cstdio>
#include <algorithm>
using namespace std;
const int MAX_V = 1000;
const int INF = 0x3f3f3f3f;
typedef pair<int, int> P;

int d[MAX_V+5];
int V, E, G[MAX_V+5][MAX_V+5];

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
		for(int i = 1; i <= V; ++i) {
			if(d[i] > d[u] + G[u][i]) {
				d[i] = d[u] + G[u][i];
				que.push(P(d[i], i));
			}
		}
	}
}

int main()
{
	int ns, s, t, a, b, c;

	while(~scanf("%d%d%d", &V, &E, &t)) {
		for(int i = 1; i <= V; ++i)
			for(int j = 1; j <= V; ++j)
				G[i][j] = INF;
		for(int i = 0; i < E; ++i) {
			scanf("%d%d%d", &a, &b, &c);
			if(c < G[b][a]) G[b][a] = c;
		}
		dijkstra(t);
		int ans = INF;
		scanf("%d", &ns);
		for(int i = 0; i < ns; ++i) {
			scanf("%d", &s);
			ans = min(ans, d[s]);
		}
		printf("%d\n", ans==INF ? -1 : ans);
	}
	return 0;
}
