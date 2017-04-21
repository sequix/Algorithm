// HDU No.2112 Today (map+dijkstra) (3120MS 1772K)
#include <map>
#include <queue>
#include <string>
#include <cstring>
#include <iostream>
using namespace std;
const int INF = 0x3f3f3f3f;
const int MAX_V = 150;
const int MAX_E = 10000;
typedef pair<int, int> P;

map<string, int> tab;
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
		for(int i = 1; i <= V; ++i) {
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
	int c;
	string a, b, s, t;

	while(cin >> E && E != -1) {
		V = 0;
		tab.clear();
		int cnt = 0;
		cin >> s >> t;
		if(tab[s] == 0) { tab[s] = ++cnt; ++V; }
		if(tab[t] == 0) { tab[t] = ++cnt; ++V; }
		memset(G, INF, sizeof(G));

		for(int i = 0; i < E; ++i) {
			cin >> a >> b >> c;
			if(tab[a] == 0) { tab[a] = ++cnt; ++V; }
			if(tab[b] == 0) { tab[b] = ++cnt; ++V; }
			if(c < G[tab[a]][tab[b]])
				G[tab[a]][tab[b]] = G[tab[b]][tab[a]] = c;
		}

		dijkstra(tab[s]);
		cout << (d[tab[t]]==INF ? -1 : d[tab[t]]) << endl;
	}
	return 0;
}
