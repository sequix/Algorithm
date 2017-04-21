// HDU No.1546 (map<string, vector<int> > + dijkstra) (187MS 5416K)
#include <map>
#include <queue>
#include <string>
#include <vector>
#include <cstdio>
#include <utility>
#include <iostream>
using namespace std;
typedef pair<int, int> P;
const int INF = 0x3f3f3f3f;
const int MAX_V = 1000;

int V, G[MAX_V+5][MAX_V+5];
string tails[MAX_V+5];		// tails[i] i号节点的末尾汉字
int cost[MAX_V+5];			// cost[i] i号节点的花费
map<string, vector<int> > heads;	// heads[s] 一个vector<int>包含以s开头的几点的编号

int dijkstra(int s, int e)
{
	int d[MAX_V+5];
	priority_queue<P, vector<P>, greater<P> > que;

	for(int i = 0; i < V; ++i)
		d[i] = INF;
	d[s] = 0;
	que.push(P(0, s));

	while(!que.empty()) {
		P p = que.top(); que.pop();
		int u = p.second;
		if(u == e) break;
		if(d[u] < p.first) continue;
		for(int i = 0; i < V; ++i) {
			if(d[i] > d[u] + G[u][i]) {
				d[i] = d[u] + G[u][i];
				que.push(P(d[i], i));
			}
		}
	}
	return d[e] != INF ? d[e] : -1;
}

int main()
{
	string str;

	while(~scanf("%d", &V) && V != 0) {
		for(int i = 0; i < V; ++i) {
			cin >> cost[i] >> str;
			tails[i] = str.substr(str.size()-4);
			heads[str.substr(0, 4)].push_back(i);
		}
		for(int i = 0; i < V; ++i)
			for(int j = 0; j < V; ++j)
				G[i][j] = INF;
		for(int i = 0; i < V; ++i) {
			vector<int> &v = heads[tails[i]];
			for(int j = 0; j < v.size(); ++j)
				G[i][v[j]] = cost[i];
		}
		printf("%d\n", dijkstra(0, V-1));
		heads.clear();
	}
	return 0;
}
