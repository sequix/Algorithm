// HDU No.5876 Sparse Graph (补图上的bfs) (1076MS 19532K)
#include <set>
#include <queue>
#include <iostream>
using namespace std;
const int INF = 0x3f3f3f3f;
const int MAX_V = 200000;
const int MAX_E = 20000;

int V, E, dis[MAX_V+5];
set<int> G[MAX_V+5];	// 原图
set<int> unused;		// bfs还未访问过的点

void bfs(int src)
{
	queue<int> que;
	int delcnt, todel[MAX_V+5];

	for(int i = 1; i <= V; ++i) {
		if(i != src) unused.insert(i);
		dis[i] = INF;
	}
	que.push(src);
	dis[src] = 0;

	while(!que.empty()) {
		int u = que.front(); que.pop();
		delcnt = 0;
		set<int>::iterator it;
		for(it = unused.begin(); it != unused.end(); ++it) {
			if(G[u].find(*it) == G[u].end()) {
				dis[*it] = dis[u] + 1;
				todel[delcnt++] = *it;
				que.push(*it);
			}
		}
		for(int i = 0; i < delcnt; ++i)
			unused.erase(todel[i]);
	}
}

int main()
{
	int T, u, v, S;

	for(cin >> T; T > 0; --T) {
		cin >> V >> E;
		for(int i = 1; i <= V; ++i)
			G[i].clear();
		for(int i = 0; i < E; ++i) {
			cin >> u >> v;
			G[u].insert(v);
			G[v].insert(u);
		}
		cin >> S;
		bfs(S);
		for(int i = 1; i <= V; ++i) {
			if(i == S) continue;
			cout << (dis[i] == INF ? -1 : dis[i]);
			if(i == V) cout << endl;
			else cout << " ";
		}
	}
}
