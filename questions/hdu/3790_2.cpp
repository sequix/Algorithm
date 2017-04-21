// HDU No.3790 最短路径问题 (memset改为手工初始化) (280MS 9416K)
#include <queue>
#include <vector>
#include <cstdio>
using namespace std;
const int INF = 0x3f3f3f3f;
const int MAX_V = 1000;
const int MAX_E = 100000;
struct T {
	int no, d0, d1;
	T(int n, int c0, int c1): no(n), d0(c0), d1(c1) {}
	bool operator>(const T &rhs) const {
		if(d0 == rhs.d0)
			return d1 > rhs.d1;
		return d0 > rhs.d0;
	}
};
int s, t, V, E, d[MAX_V+5][2];
int G[MAX_V+5][MAX_V+5][2];

void dijkstra()
{
	priority_queue<T, vector<T>, greater<T> > que;

	for(int i = 1; i <= V; ++i)
		d[i][0] = d[i][1] = INF;
	d[s][0] = d[s][1] = 0;
	que.push(T(s, 0, 0));

	while(!que.empty()) {
		T t = que.top(); que.pop();
		int u = t.no;
		if(d[u][0] < t.d0) continue;
		if(d[u][0] == t.d0 && d[u][1] < t.d1) continue;
		for(int i = 1; i <= V; ++i) {
			if(G[u][i][0] == INF) continue;
			if(d[i][0]>d[u][0]+G[u][i][0] || (d[i][0]==d[u][0]+G[u][i][0] &&
					d[i][1]>d[u][1]+G[u][i][1])) {
				d[i][0] = d[u][0] + G[u][i][0];
				d[i][1] = d[u][1] + G[u][i][1];
				que.push(T(i, d[i][0], d[i][1]));
			}
		}
	}
}

int main()
{
	int a, b, d0, d1;

	while(~scanf("%d%d", &V, &E), V+E) {
		for(int i = 1; i <= V; ++i)
			for(int j = 1; j <= V; ++j)
				G[i][j][0] = G[i][j][1] = INF;

		for(int i = 0; i < E; ++i) {
			scanf("%d%d%d%d", &a, &b, &d0, &d1);
			if(G[a][b][0]>d0 || (G[a][b][0]==d0 && G[a][b][1]>d1)) {
				G[a][b][0] = G[b][a][0] = d0;
				G[a][b][1] = G[b][a][1] = d1;
			}
		}
		scanf("%d%d", &s, &t);

		dijkstra();
		printf("%d %d\n", d[t][0], d[t][1]);
	}
	return 0;
}
