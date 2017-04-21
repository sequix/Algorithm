// Fleury 求欧拉回路 & 邻接阵
#include <stack>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int MAX_V = 100;

int V, E;
stack<int> stk;		// stack没有clear()
int G[MAX_V+5][MAX_V+5];

// 扩展x，找可扩展节点i，删除i与x间的边，扩展i，递归
void dfs(int x)
{
	stk.push(x);
	for(int i = 0; i < V; ++i) {
		if(G[x][i] > 0) {
			G[x][i] = G[i][x] = 0;
			dfs(i);
			break;	// ???
		}
	}
}

void fleury(int start)
{
	stk.push(start);

	while(!stk.empty()) {
		int from = stk.top(); stk.pop();
		bool exntendable = false;
		for(int i = 0; i < V; ++i)
			if(G[from][i] != 0) { exntendable = true; break; }
		if(!exntendable)
			printf("%d ", from);
		else
			dfs(from);
	}
	putchar('\n');
}

int main()
{
	int from, to;

	cin >> V >> E;
	for(int i = 0; i < E; ++i) {
		cin >> from >> to;
		G[from][to] = G[to][from] = 1;
	}

	int oddcnt = 0, start = 0;
	for(int i = 0; i < V; ++i) {
		int deg = 0;
		for(int j = 0; j < V; ++j)
			deg += G[i][j];
		if(deg % 2 == 1)
			++oddcnt, start = i;
	}

	if(oddcnt != 0 && oddcnt != 2)
		puts("No Euler path.");
	else
		fleury(start);
	return 0;
}
