// POJ No.1798 Truck History (prim) (16128K 625MS)
#include <queue>
#include <cstdio>
using namespace std; 
const int MAX_V = 2000;
const int INF = 0x3f3f3f3f;
typedef pair<int, int> P;

int V, G[MAX_V+5][MAX_V+5];
char str[MAX_V+5][8];

int prim()
{
	int mincost[MAX_V+5], res = 0;
	priority_queue<P, vector<P>, greater<P> > que;

	for(int i = 0; i < V; ++i)
		mincost[i] = INF;
	mincost[0] = 0;
	que.push(P(0, 0));

	while(!que.empty()) {
		P p = que.top(); que.pop();
		int u = p.second;
		if(mincost[u] < p.first) continue;
		res += p.first;
		for(int i = 0; i < V; ++i) {
			if(G[u][i] < mincost[i]) {
				mincost[i] = G[u][i];
				que.push(P(mincost[i], i));
			}
		}
	}
	return res;
}

int dis(int x, int y)
{
	int cnt = 0;
	for(int i = 0; i < 7; ++i)
		if(str[x][i] != str[y][i])
			++cnt;
	return cnt;
}

int main()
{
	while(~scanf("%d", &V), V) {
		for(int i = 0; i < V; ++i)
			scanf("%s", str[i]);
		for(int i = 0; i < V; ++i)
			for(int j = 0; j < V; ++j)
				G[i][j] = dis(i, j);
		printf("The highest possible quality is 1/%d.\n", prim());
	}
	return 0;
}
