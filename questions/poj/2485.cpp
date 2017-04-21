// POJ No.2485 Highways (prim) (960K 157MS)
#include <queue>
#include <cstdio>
using namespace std;
const int MAX_V = 500;
const int INF = 0x3f3f3f3f;
typedef pair<int, int> P;

int V, G[MAX_V+5][MAX_V+5];

int prim()
{
	int res = 0;
	int mincost[MAX_V+5];
	priority_queue<P, vector<P>, greater<P> > que;

	for(int i = 1; i <= V; ++i)
		mincost[i] = INF;
	mincost[1] = 0;
	que.push(P(0, 1));

	while(!que.empty()) {
		P p = que.top(); que.pop();
		int u = p.second;
		if(mincost[u] < p.first) continue;
		res = max(res, p.first);	// 题目仅要求最小树中的最长边的长度
		for(int i = 1; i <= V; ++i) {
			if(G[u][i] < mincost[i]) {
				mincost[i] = G[u][i];
				que.push(P(mincost[i], i));
			}
		}
	}
	return res;
}


int main()
{
	int T;

	for(scanf("%d", &T); T > 0; --T) {
		scanf("%d", &V);
		for(int i = 1; i <= V; ++i)
			for(int j = 1; j <= V; ++j)
				scanf("%d", &G[i][j]);
		printf("%d\n", prim());
	}
	return 0;
}
