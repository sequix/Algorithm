// HDU No.1874 畅通工程续 (dijkstra) (62MS 1772K)
#include <queue>
#include <cstring>
#include <iostream>
using namespace std;
const int INF = 0x3f3f3f3f;
const int MAX_V = 200;
typedef pair<int, int> P;

int V, E, d[MAX_V+5], G[MAX_V+5][MAX_V+5];

void dijkstra(int s)
{
	priority_queue<P, vector<P>, greater<P> > que;

	memset(d, INF, sizeof(d));
	d[s] = 0;
	que.push(P(0, s));

	while(!que.empty()) {
		P p = que.top(); que.pop();
		int u = p.second;
		if(d[u] < p.first) continue;
		for(int i = 0; i < V; ++i) {
			if(G[u][i] == INF) continue;
			if(d[i] > d[u] + G[u][i]) {
				d[i] = d[u] + G[u][i];
				que.push(P(d[i], i));
			}
		}
	}
}

int main()
{
	int a, b, c, s, t;

	while(cin >> V >> E) {
		memset(G, INF, sizeof(G));
		for(int i = 0; i < E; ++i) {
			cin >> a >> b >> c;
			if(c < G[a][b]) G[a][b] = G[b][a] = c;
		}
		cin >> s >> t;
		dijkstra(s);
		cout << (d[t]==INF ? -1 : d[t]) << endl;
	}
	return 0;
}
