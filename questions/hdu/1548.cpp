// HDU No.1548 A strange lift (BFS) (15MS 1460K)
#include <queue>
#include <cstdio>
using namespace std;
const int MAX_V = 200;
int V, map[MAX_V+5], d[MAX_V+5];
#define inrange(x) (1 <= (x) && (x) <= V)

void bfs(int s, int t)
{
	queue<int> que;
	que.push(s);

	for(int i = 1; i <= V; ++i)
		d[i] = -1;
	d[s] = 0;

	while(!que.empty()) {
		int u = que.front(); que.pop();
		if(u == t) return;
		if(inrange(u-map[u]) && d[u-map[u]]==-1) {
			d[u-map[u]] = d[u] + 1;
			que.push(u-map[u]);
		}
		if(inrange(u+map[u]) && d[u+map[u]]==-1) {
			d[u+map[u]] = d[u] + 1;
			que.push(u+map[u]);
		}
	}
}

int main()
{
	int s, t;

	while(~scanf("%d%d%d", &V, &s, &t), V) {
		for(int i = 1; i <= V; ++i)
			scanf("%d", &map[i]);
		bfs(s, t);
		printf("%d\n", d[t]);
	}
	return 0;
}
