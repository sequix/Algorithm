// POJ No.1287 Networking (Kruskal) (736K 204MS)
#include <iostream>
#include <algorithm>
using namespace std;

class UnionFind {
private:
	int par[100];
public:
	UnionFind(int n) {
		for(int i = 1; i <= n; ++i)
			par[i] = i;
	}
	int getpar(int x) {
		if(par[x] != x)
			par[x] = getpar(par[x]);
		return par[x];
	}
	int merge(int x, int y) {
		par[getpar(x)] = getpar(y);
	}
	bool equal(int x, int y) {
		return getpar(x) == getpar(y);
	}
};

struct Edge {
	int from, to, cost;
	Edge(int f=0, int t=0, int c=0): from(f), to(t), cost(c) {}
	bool operator < (const Edge &e) const { return cost < e.cost; }
} edges[3000];

int V, E;

int kruskal()
{
	int ret = 0;
	UnionFind uf(V);

	sort(edges, edges+E);
	for(int i = 0; i < E; ++i) {
		Edge &e = edges[i];
		if(uf.equal(e.from, e.to)) continue;
		uf.merge(e.from, e.to);
		ret += e.cost;
	}
	return ret;
}

int main()
{
	int u, v, c;

	while(cin >> V && V != 0) {
		cin >> E;
		for(int i = 0; i < E; ++i) {
			cin >> u >> v >> c;
			edges[i] = Edge(u, v, c);
		}
		cout << kruskal() << endl;
	}
}
