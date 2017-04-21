// POJ No.1679 The Unique MST (Kruskal判MST是否唯一) (524K 79MS)
#include <cstdio>
#include <algorithm>
using namespace std;
const int MAX_V = 100;
const int MAX_E = 10000;

class UnionFind {
private:
	int par[MAX_V+5];
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
	void merge(int x, int y) {
		par[getpar(x)] = getpar(y);
	}
	bool equal(int x, int y) {
		return getpar(x) == getpar(y);
	}
};

struct Edge {
	int u, v, w;
	bool equal;		// 有与该条边权值相同的边
	bool used;		// 该边在mst中
	bool excluded;	// 排除该边
	Edge(int u=0, int v=0, int w=0): u(u), v(v), w(w),
		equal(false), used(false), excluded(false) {}
	bool operator < (const Edge &e) const { return w < e.w; }
} edges[MAX_E+5];

int V, E;

int kruskal(bool tomark=true)
{
	UnionFind uf(V);
	int cnt = 0, sumweight = 0;

	for(int i = 0; i < E && cnt < V; ++i) {
		Edge &e = edges[i];
		if(e.excluded || uf.equal(e.u, e.v)) continue;
		++cnt;
		sumweight += e.w;
		uf.merge(e.u, e.v);
		if(tomark) e.used = true;
	}
	return sumweight;
}

int main()
{
	int T;

	for(scanf("%d", &T); T > 0; --T) {
		scanf("%d%d", &V, &E);
		for(int i = 0; i < E; ++i) {
			scanf("%d%d%d", &edges[i].u, &edges[i].v, &edges[i].w);
			edges[i].equal = edges[i].excluded = edges[i].used = false;
		}
		for(int i = 0; i < E; ++i) {
			for(int j = 0; j < E; ++j) {
				if(i == j) continue;
				if(edges[i].w == edges[j].w) edges[i].equal = true;
			}
		}
		sort(edges, edges+E);
		bool isunique = true;
		int weight1 = kruskal();
		for(int i = 0; i < E; ++i) {
			if(edges[i].used && edges[i].equal) {
				edges[i].excluded = true;
				int weight2 = kruskal(false);
				if(weight1 == weight2) { isunique = false; break; }
				edges[i].excluded = false;
			}
		}
		if(isunique)
			printf("%d\n", weight1);
		else
			puts("Not Unique!");
	}
}
