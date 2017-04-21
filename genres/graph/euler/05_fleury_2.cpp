// Fleury 求欧拉回路 & 邻接表
#include <set>
#include <stack>
#include <cstdio>
#include <iostream>
using namespace std;
const int MAX_V = 100;

int V, E;
stack<int> stk;
set<int> G[MAX_V+5];	// 支持高效的插入和删除

// 扩展from，找可扩展节点to，删除to与from间的边，扩展to，递归
void dfs(int from)
{
	stk.push(from);
	if(G[from].size() > 0) {
		int to = *G[from].begin();
		G[from].erase(G[from].begin());
		// 注意erase会移除所有为from的边，所以有重边要特殊处理
		G[to].erase(from);
		dfs(to);
	}
}

void fleury(int start)
{
	stk.push(start);

	while(!stk.empty()) {
		int from = stk.top(); stk.pop();
		if(G[from].size() == 0)
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
		G[from].insert(to);
		G[to].insert(from);
	}

	int oddcnt = 0, start = 0;
	for(int i = 0; i < V; ++i)
		if(G[i].size() % 2 == 1)
			++oddcnt, start = i;

	if(oddcnt != 0 && oddcnt != 2)
		puts("No Euler path.");
	else
		fleury(start);
	return 0;
}
