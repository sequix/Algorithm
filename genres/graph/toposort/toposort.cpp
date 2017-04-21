// Topological sort ver.2
#include <stack>
#include <vector>
#include <cstdio>
#include <cstring>
using namespace std;
const int MAX_V = 1000;
typedef vector<int> VCT_INT;

int V, E;
vector<VCT_INT> G(MAX_V+5);
int indegree[MAX_V+5];
int toposeq[MAX_V+5];

// 有环返回false，无环返回true
bool toposort()
{
	int cnt = 0;
	stack<int> st;

	for(int i = 0; i < V; ++i)
		if(indegree[i] == 0) st.push(i);

	for(int i = 0; i < V && !st.empty(); ++i) {
		int u = st.top(); st.pop();
		toposeq[cnt++] = u;
		for(int i = 0; i < G[u].size(); ++i)
			if(--indegree[G[u][i]] == 0) st.push(G[u][i]);
	}
	return cnt == V;
}

int main()
{
	int u, v;
	while(scanf("%d%d", &V, &E) != EOF) {
		for(int i = 0; i < V; ++i) G[i].clear();
		memset(indegree, 0, sizeof(indegree));

		for(int i = 0; i < E; ++i) {
			scanf("%d%d", &u, &v);
			G[u].push_back(v);
			++indegree[v];
		}
		if(toposort()) {
			for(int i = 0; i < V; ++i)
				printf("%d ", toposeq[i]);
			putchar('\n');
		} else {
			printf("Network has a cycle!\n");
		}
	}
}
