// POJ No.3587 Labeling Balls (topo排序) (596K 32MS)
// 输出的是ball1到ball N的重量，而不是轻重关系
#include <queue>
#include <cstdio>
#include <cstring>
using namespace std;

int V, E;
bool G[205][205];
int ind[205];	// 入度
int ans[205];	// 1球到N球的质量
int seq[205];	// 球质量从小到大的拓扑序

bool toposort()
{
	int cnt = V;	// 因为逆向建图，所以这里拓扑序也要反过来
	// 优先选择编号大的，将重量小的尽量留个编号小的
	priority_queue<int> que;

	for(int i = 1; i <= V; ++i)
		if(ind[i] == 0) que.push(i);

	while(!que.empty()) {
		int u = que.top(); que.pop();
		seq[cnt--] = u;
		for(int i = 1; i <= V; ++i)
			if(G[u][i] && --ind[i] == 0) que.push(i);
	}
	return cnt == 0;
}

int main()
{
	int u, v, T;

	for(scanf("%d", &T); T > 0; --T) {
		memset(G, false, sizeof(G));
		memset(ind, 0, sizeof(ind));

		scanf("%d%d", &V, &E);
		for(int i = 0; i < E; ++i) {
			scanf("%d%d", &u, &v);
			// 逆向建图，尽量将较小的重量留个编号小的
			if(G[v][u] != true)
				++ind[u], G[v][u] = true;
		}

		if(toposort()) {
			for(int i = 1; i <= V; ++i)
				ans[seq[i]] = i;
			printf("%d", ans[1]);
			for(int i = 2; i <= V; ++i)
				printf(" %d", ans[i]);
			putchar('\n');
		} else {
			puts("-1");
		}
	}
}
