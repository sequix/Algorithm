// HDU No.3339 (dijkstra+01背包) (280MS 1548K)
#include <queue>
#include <cstdio>
#include <algorithm>
using namespace std;
const int MAX_V = 100;
const int MAX_P = 10000;
const int INF = 0x3f3f3f3f;
typedef pair<int, int> P;

int V, E, G[MAX_V+5][MAX_V+5], dp[MAX_P+5];
int powersum, power[MAX_V+5], d[MAX_V+5];

void dijkstra(int s)
{
	priority_queue<P, vector<P>, greater<P> > que;

	for(int i = 0; i <= V; ++i)
		d[i] = INF;
	d[s] = 0;
	que.push(P(0, s));

	while(!que.empty()) {
		P p = que.top(); que.pop();
		int u = p.second;
		if(d[u] < p.first) continue;
		for(int i = 0; i <= V; ++i) {
			if(d[i] > d[u] + G[u][i]) {
				d[i] = d[u] + G[u][i];
				que.push(P(d[i], i));
			}
		}
	}
}

int main()
{
	int T, a, b, c;

	for(scanf("%d", &T); T; --T) {
		scanf("%d%d", &V, &E);
		for(int i = 0; i <= V; ++i)
			for(int j = 0; j <= V; ++j)
				G[i][j] = INF;
		for(int i = 0; i < E; ++i) {
			scanf("%d%d%d", &a, &b, &c);
			if(c < G[a][b]) G[a][b] = G[b][a] = c;
		}
		powersum = power[0] = 0;
		for(int i = 1; i <= V; ++i) {
			scanf("%d", &power[i]);
			powersum += power[i];
		}

		dijkstra(0);
		for(int i = 1; i <= powersum; ++i)
			dp[i] = INF;
		dp[0] = 0;
		for(int i = 1; i <= V; ++i)
			for(int j = powersum; j >= power[i]; --j)
				dp[j] = min(dp[j], dp[j-power[i]] + d[i]);

		int ans = INF;
		for(int i = powersum/2+1; i <= powersum; ++i)
			ans = min(ans, dp[i]);
		if(ans == INF)
			puts("impossible");
		else
			printf("%d\n", ans);
	}
	return 0;
}
