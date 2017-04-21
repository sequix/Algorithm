// POJ No.Conscription (kruskal求最大权森林) (988K 297MS)
#include <cstdio>
#include <algorithm>
using namespace std;
const int MAX_V = 20000;
const int MAX_E = 50000;
const int INF = 0x3f3f3f3f;
struct edge {
	int from, to, cost;
	bool operator<(const edge &rhs) const { return cost < rhs.cost; }
};
struct Union_find {
	int par[MAX_V+5];
	Union_find(int n) {
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
		par[x] = y;
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
	Union_find uni(V);
	for(int i = 0; i < E; ++i) {
		edge &e = es[i];
		if(!uni.same(e.from, e.to)) {
			uni.unite(e.from, e.to);
			res += e.cost;
		}
	}
	return res;
}

int main()
{
	int T, n, m;

	for(scanf("%d", &T); T > 0; --T) {
		scanf("%d%d%d", &n, &m, &E);
		V = n + m;
		for(int i = 0; i < E; ++i) {
			scanf("%d%d%d", &es[i].from, &es[i].to, &es[i].cost);
			es[i].to += n;
// 为使最小生成树算法求权值最大的生成树，可令权值取相反数
			es[i].cost = -es[i].cost;
		}
		printf("%d\n", 10000 * V + kruskal());
	}
	return 0;
}
