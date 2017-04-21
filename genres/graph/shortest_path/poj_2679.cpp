// POJ No.2679 Adventurous Driving (SPFA+DFS) (876K 47MS)
/*
给出一个有向图，每条边有两个属性：一个长度一个费用。费用可能是负数。
长度一定是非负的。给出一个起点和一个终点，现要求，从起点走到终点，
且从每个点走出时选择的那条边必须是以该点作为起点的边中费用最小或
并列费用最小的边。如果依据这个原则无法走到终点则输出VOID。并且要求
从起点到终点的过程中，先要保证费用最小，在有多解时，保证长度最小。
最后输出最小费用和长度。如果费用可以无限小则输出UNBOUND。
*/
#include <queue>
#include <cstdio>
#include <cctype>
#include <vector>
using namespace std;
const int MAX_V = 1100;
const int INF = 0x3f3f3f3f;

struct Edge {
	int to, len, fee;
	Edge(int t=0, int l=0, int f=0): to(t), len(l), fee(f) {}
};

int V, E, S, D;
bool reachable[MAX_V+5];	// reachable[u] 节点u是否可到达终点
vector<Edge> G[MAX_V+5];
vector<int> rG[MAX_V+5];

// 遍历逆图rG，标记哪些点可达终点
void dfs(int u)
{
	if(reachable[u]) return;
	reachable[u] = true;
	for(int i = 0; i < rG[u].size(); ++i)
		dfs(rG[u][i]);
}

void spfa()
{
	queue<int> que;
	int cnt[MAX_V+5] = {0};
	bool inq[MAX_V+5] = {0};
	int dis[MAX_V+5], fee[MAX_V+5];

	for(int i = 0; i < V; ++i)
		dis[i] = INF, fee[i] = INF;
	dis[S] = fee[S] = 0;
	que.push(S);
	inq[S] = true;

	while(!que.empty()) {
		int u = que.front(); que.pop();
		inq[u] = false;
		if(++cnt[u] > V) { puts("UNBOUND"); return; }
		for(int i = 0; i < G[u].size(); ++i) {
			Edge &e = G[u][i];
			if(fee[e.to] > fee[u] + e.fee) {
				fee[e.to] = fee[u] + e.fee;
				dis[e.to] = dis[u] + e.len;
				if(!inq[e.to]) que.push(e.to), inq[e.to] = true;
			} else if(fee[e.to] == fee[u] + e.fee
					&& dis[e.to] > dis[u] + e.len) {
				dis[e.to] = dis[u] + e.len;
				if(!inq[e.to]) que.push(e.to), inq[e.to] = true;
			}
		}
	}
	if(fee[D] == INF)
		puts("VOID");
	else
		printf("%d %d\n", fee[D], dis[D]);
}

int main()
{
	char ch;
	int u, v, fuv, fvu, L;
	int least_fee[MAX_V+5];	// least_fee[u] 从节点u出发最小的费用
	vector<Edge>::iterator it;

	while(true) {
		while(isspace(ch = getchar())) ;
		ungetc(ch, stdin);
		if(scanf("%d%d%d%d", &V, &E, &S, &D) == EOF) break;

		for(int i = 0; i < V; ++i) {
			G[i].clear(), rG[i].clear();
			least_fee[i] = INF, reachable[i] = false;
		}

		for(int i = 0; i < E; ++i) {
			while(isspace(getchar()));
			scanf("%d,%d,%d[%d]%d)", &u, &v, &fuv, &L, &fvu);
			G[u].push_back(Edge(v, L, fuv));
			G[v].push_back(Edge(u, L, fvu));
			least_fee[u] = min(least_fee[u], fuv);
			least_fee[v] = min(least_fee[v], fvu);
		}
		// 删除费用比最小费用大的边
		for(int i = 0; i < V; ++i) {
			for(it = G[i].begin(); it != G[i].end();) {
				if(it->fee > least_fee[i])
					it = G[i].erase(it);
				else
					++it;
			}
		}
		// 创建逆图，从终点在逆图上dfs确认不可到终点的点
		for(int i = 0; i < V; ++i)
			for(int j = 0; j < G[i].size(); ++j)
				rG[G[i][j].to].push_back(i);
		dfs(D);
		// 删除无法到达终点的节点
		for(int i = 0; i < V; ++i) {
			if(!reachable[i]) {
				G[i].clear();
				continue;
			}
			for(it = G[i].begin(); it != G[i].end();) {
				if(!reachable[it->to])
					it = G[i].erase(it);
				else
					++it;
			}
		}
		// spfa求最短路，判负环
		spfa();
	}
}
