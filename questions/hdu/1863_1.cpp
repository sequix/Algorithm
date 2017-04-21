// HDU No.1863 畅通工程 (连通图判断+prim) (0MS 1460K)
#include <cstdio>
#include <algorithm>
using namespace std;
const int MAX = 100;
const int INF = 0x3f3f3f3f;

int V, E, G[MAX+5][MAX+5];

int prim()
{
	bool used[MAX+5] = {0};
	int d[MAX+5], res = 0;

	for(int i = 1; i <= V; ++i)
		d[i] = INF;
	d[1] = 0;

	while(true) {
		int v = -1;
		for(int j = 1; j <= V; ++j)
			if(!used[j] && (v==-1 || d[j]<d[v])) v = j;
		if(v == -1) break;	// 节点全用完了
		if(d[v] == INF) return -1;	// 节点没用完的情况下，没有符合条件的节点
		used[v] = true;
		res += d[v];
		for(int j = 1; j <= V; ++j)
			d[j] = min(d[j], G[v][j]);
	}
	return res;
}

int main()
{
	int a, b, c;

	while(~scanf("%d%d", &E, &V) && E != 0) {
		for(int i = 1; i <= V; ++i)
			for(int j = 1; j <= V; ++j)
				G[i][j] = INF;
		for(int i = 0; i < E; ++i) {
			scanf("%d%d%d", &a, &b, &c);
			G[a][b] = G[b][a] = c;
		}
		int ans = prim();
		if(ans == -1) puts("?");
		else printf("%d\n", ans);
	}
	return 0;
}
