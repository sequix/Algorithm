// POJ No.2585 Window Pains (topo排序) (560K 0MS)
#include <stack>
#include <vector>
#include <cstdio>
#include <cstring>
using namespace std;

int ind[9];
int tab[4][4][4];	// tab[i][j] 在(i,j)格中的窗口，可能被覆盖
int tabcnt[4][4];	// tabcnt[i][j] 在(i,j)格中的窗口数
vector<vector<int> > G(9);

void init()
{
	for(int k = 0; k < 9; ++k) {
		int i = k / 3, j = k % 3;
		tab[i][j][tabcnt[i][j]++] = k;
		tab[i][j+1][tabcnt[i][j+1]++] = k;
		tab[i+1][j][tabcnt[i+1][j]++] = k;
		tab[i+1][j+1][tabcnt[i+1][j+1]++] = k;
	}
}

// 拓扑排序判是否是DAG
bool isacyclic()
{
	int cnt = 0;
	stack<int> st;
	
	for(int i = 0; i < 9; ++i)
		if(ind[i] == 0) st.push(i);

	while(!st.empty()) {
		++cnt;
		int u = st.top(); st.pop();
		for(int i = 0; i < G[u].size(); ++i)
			if(--ind[G[u][i]] == 0) st.push(G[u][i]);
	}
	return cnt == 9;
}

int main()
{
	int u;
	char buf[64];

	init();
	while(scanf("%s", buf) != EOF) {
		if(strcmp(buf, "ENDOFINPUT") == 0) break;
		for(int i = 0; i < 9; ++i)
			G[i].clear();
		memset(ind, 0, sizeof(ind));
		for(int i = 0; i < 4; ++i) {
			for(int j = 0; j < 4; ++j) {
				scanf("%d", &u); --u;
				// 构图依据：A窗口覆盖B窗口则有由A到B的边
				// 某格被某窗口覆盖，则该窗口覆盖该格上的其它窗口
				for(int k = 0; k < tabcnt[i][j]; ++k) {
					if(tab[i][j][k] != u) {
						++ind[tab[i][j][k]];
						G[u].push_back(tab[i][j][k]);
					}
				}
			}
		}
		printf("THESE WINDOWS ARE %s\n", isacyclic() ? "CLEAN" : "BROKEN");
		scanf("%s", buf);
	}
}
