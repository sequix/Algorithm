// HDU No.1102 Constructing Roads (prim+多组数据+去掉used数组) (15MS 1476K)
#include <queue>
#include <cstdio>
#include <utility>
using namespace std;
const int MAX_V = 100;
const int INF = 0x3f3f3f3f;
typedef pair<int, int> P;

int V, E, G[MAX_V+5][MAX_V+5];

int prim()
{
	int res = 0, d[MAX_V+5];
	priority_queue<P, vector<P> , greater<P> > que;

	for(int i = 1; i <= V; ++i)
		d[i] = INF;
	d[1] = 0;
	que.push(P(0, 1));
	while(!que.empty()) {
		P p = que.top(); que.pop();
		int u = p.second;
		if(d[u] < p.first) continue;
		res += p.first;
		for(int i = 1; i <= V; ++i) {
			if(G[u][i] < d[i]) {
				d[i] = G[u][i];
				que.push(P(d[i], i));
			}
		}
	}
	return res;
}

int main()
{
	int a, b;

	while(~scanf("%d", &V)) {
		for(int i = 1; i <= V; ++i)
			for(int j = 1; j <= V; ++j)
				scanf("%d", &G[i][j]);
		scanf("%d", &E);
		for(int i = 0; i < E; ++i) {
			scanf("%d%d", &a, &b);
			G[a][b] = G[b][a] = 0;
		}
		printf("%d\n", prim());
	}
	return 0;
}
