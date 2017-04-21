//// kruskal: 求加权图的最小生成森林，需要用到并查集

class UnionFind {
private:
	int par[MAX_N];
public:
	UnionFind(int n) {
		for(int i = 0; i < n; ++i)
			par[i] = i;
	}
	int getpar(int x) {
		if(par[x] != x)
			par[x] = getpar(par[x]);
		return par[x];
	}
	void merge(int x, int y) {
		par[getpar(x)] = getpar(y);
	}
	bool query(int x, int y) {
		return getpar(x) == getpar(y);
	}
};

struct edge {
	int from, to, cost;
	bool operator<(const edge &e) const { return cost < e.cost; }
};

int V, E;
edge es[MAX_E];

int kruskal()
{
	int res = 0;
	sort(es, es+E);
	Union_find uf(V);
	for(int i = 0; i < E; ++i) {
		edge &e = es[i];
		if(!uf.query(e.from, e.to)) {
			uf.merge(e.from, e.to);
			res += e.cost;
		}
	}
	return res;
}
