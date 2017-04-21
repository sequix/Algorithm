// HDU No.1245 Saving James Bond (Dijkstra+cstdio) (156MS 1704K)
#include <queue>
#include <cmath>
#include <cstdio>
#include <iostream>
using namespace std;
const int MAX_V = 100;
const double INF = 1e13;
typedef pair<double, int> P;

int V, pre[MAX_V+5];
double D, G[MAX_V+5][MAX_V+5];
double x[MAX_V+5], y[MAX_V+5], d[MAX_V+5];

void dijkstra(int s, int t)
{
	priority_queue<P, vector<P>, greater<P> > que;

// 图论的初始化不要用memset/fill，自己来
	for(int i = 0; i <= V+1; ++i) {
		d[i] = INF;
		pre[i] = -1;
	}
	d[s] = 0.0;
	que.push(P(0.0, s));

	while(!que.empty()) {
		P p = que.top(); que.pop();
		int u = p.second;
		if(u == t) return;
		if(d[u] < p.first) continue;
		for(int i = 0; i <= V+1; ++i) {
			if(d[i] > d[u] + G[u][i]) {
				d[i] = d[u] + G[u][i];
				pre[i] = u;
				que.push(P(d[i], i));
			}
		}
	}
}

int main()
{
	while(~scanf("%d%lf", &V, &D)) {
		if(V == 0) {
			if(D >= 42.5) printf("42.50, 1\n");
			else printf("can't be saved\n");
			continue;
		}
		for(int i = 1; i <= V; ++i)
			scanf("%lf%lf", &x[i], &y[i]);
		x[0] = y[0] = 0;
// 当无法直接将输入作为节点的索引时，可将输入的序号作为节点的索引
		for(int i = 0; i <= V; ++i)
			for(int j = 0; j <= V; ++j) {
				G[i][j] = sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]));
				if(i==0 || j==0) G[i][j] -= 7.5;
				G[i][j] = max(G[i][j], 0.0);
				if(G[i][j] > D) G[i][j] = INF;
			}
// 将问题统一成求节点0到节点V+1的最短路问题
		for(int i = 0; i <= V; ++i) {
			double c = min(50-x[i], 50-y[i]);
			c = min(c, min(50+x[i], 50+y[i]));
			if(c > D) c = INF;
			G[i][V+1] = c;
		}
		dijkstra(0, V+1);
		if(d[V+1] == INF) {
			printf("can't be saved\n");
		} else {
			int cnt = 0;
			for(int i = V+1; pre[i] != -1; i = pre[i])
				++cnt;
			printf("%.2lf %d\n", d[V+1], cnt);
		}
	}
	return 0;
}
