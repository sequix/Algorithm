// POJ No.1251 Jungle Roads (kruskal) (356K 0MS)
#include <cstdio>
#include <algorithm>
using namespace std;
const int MAX_V = 26;
const int MAX_E = 75;
struct edge {
	int from, to, cost;
	edge(int f=0, int t=0, int c=0): from(f), to(t), cost(c) {}
	bool operator<(const edge &rhs) const { return cost < rhs.cost; }
};

struct DisjointSet {
	int par[MAX_V+5];
	DisjointSet(int n) {
		for(int i = 0; i < n; ++i)
			par[i] = i;
	}
	int getpar(int x) {
		if(par[x] != x)
			par[x] = getpar(par[x]);
		return par[x];
	}
	void unite(int x, int y) {
		x = getpar(x);
		y = getpar(y);
		if(x == y) return;
		par[y] = x;
	}
	bool same(int x, int y) {
		return getpar(x) == getpar(y);
	}
};

int V, E;
edge es[MAX_E+5];

int kruskal()
{
	int res = 0;
	sort(es, es+E);
	DisjointSet ds(V);
	for(int i = 0; i < E; ++i) {
		edge &e = es[i];
		if(!ds.same(e.from, e.to)) {
			ds.unite(e.from, e.to);
			res += e.cost;
		}
	}
	return res;
}

int main()
{
	char buf[4];
	int n, from, cost;

	while(~scanf("%d", &V) && V != 0) {
		E = 0;
		for(int i = 0; i < V-1; ++i) {
			scanf("%s%d", buf, &n);
			from = buf[0] - 'A';
			while(n-- > 0) {
				scanf("%s%d", buf, &cost);
				es[E++] = edge(from, buf[0]-'A', cost);
			}
		}
		printf("%d\n", kruskal());
	}
	return 0;
}
