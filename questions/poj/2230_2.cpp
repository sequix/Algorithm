// POJ No.2230 Watchcow (Fleury) (6472K 1172MS)
// 一条边拆成两条边，找一条从1开始的欧拉回路
#include <vector>
#include <cstdio>
using namespace std;
const int MAX_V = 10000;

struct Edge {
	int to; bool used;
	Edge(int t=0, bool u=false): to(t), used(u) {}
};

int V, E;
vector<Edge> G[MAX_V+5];

void dfs(int from)
{
	for(int i = 0; i < G[from].size(); ++i) {
		if(G[from][i].used) continue;
		G[from][i].used = true;
		dfs(G[from][i].to);
	}
	printf("%d\n", from);	// 因为整个行走的过程是对称的，所
}

int main()
{
	int from, to, ecnt = 0;

	scanf("%d%d", &V, &E);
	for(int i = 0; i < E; ++i) {
		scanf("%d%d", &from, &to);
		G[from].push_back(Edge(to));
		G[to].push_back(Edge(from));
	}
	dfs(1);
	return 0;
}
