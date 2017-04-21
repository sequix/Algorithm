// POJ No.3259 Wormholes (spfa) (804K 469MS)
// 给一个混合图，判断是否有负环
#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;
const int inf = 0x3f3f3f3f;
struct edge {
	int to, cost;
	edge(int t=0, int c=0): to(t), cost(c) {}
};

int V, E;
vector<edge> G[1000];

int updateTimes[1000], d[1000];

bool spfa(int s)
{
	queue<int> que;

	for(int i = 1; i <= V; ++i) {
		d[i] = inf;
		updateTimes[i] = 0;
	}
	d[s] = 0;
	que.push(s);

	while(!que.empty()) {
		int s = que.front(); que.pop();
		for(int i = 0; i < G[s].size(); ++i) {
			edge &e = G[s][i];
			if(d[e.to] > d[s] + e.cost) {
				d[e.to] = d[s] + e.cost;
				que.push(e.to);
				++updateTimes[e.to];
				if(updateTimes[e.to] >= V) return true;
			}
		}
	}
	return false;
}

int main()
{
	int T, E1, E2, a, b, c;

	for(cin >> T; T > 0; --T) {
		cin >> V >> E1 >> E2;
		E = E1 + E2;
		for(int i = 1; i < 1000; ++i)
			G[i].clear();
		for(int i = 0; i < E1; ++i) {
			cin >> a >> b >> c;
			G[a].push_back(edge(b, c));
			G[b].push_back(edge(a, c));
		}
		for(int i = 0; i < E2; ++i) {
			cin >> a >> b >> c;
			G[a].push_back(edge(b, -c));
		}
		cout << (spfa(1) ? "YES" : "NO") << endl;
	}
	return 0;
}
