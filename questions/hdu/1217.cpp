// HDU No.1217 Arbitrage (Floyd) (265MS 1704K)
#include <map>
#include <cstdio>
#include <string>
#include <cstring>
#include <iostream>
using namespace std;
const int MAX_V = 30;

int V, E;
double G[MAX_V+5][MAX_V+5];

bool floyd()
{
	for(int k = 0; k < V; ++k)
		for(int i = 0; i < V; ++i)
			for(int j = 0; j < V; ++j)
				G[i][j] = max(G[i][j], G[i][k]*G[k][j]);
	for(int i = 0; i < V; ++i)
// 所谓Arbitrage是指转一圈回来后的汇率大于1的情况
		if(G[i][i] > 1.0)
			return true;
	return false;
}

int main()
{
	double ex;
	int kase = 0;
	string str1, str2;

	while(cin >> V && V != 0) {
		map<string, int> tab;
		for(int i = 0; i < V; ++i) {
			cin >> str1;
			tab[str1] = i;
		}
		cin >> E;
// 求最长路径初始化为0
		memset(G, 0, sizeof(G));
		for(int i = 0; i < E; ++i) {
			cin >> str1 >> ex >> str2;
			G[tab[str1]][tab[str2]] = ex;
		}
		printf("Case %d: %s\n", ++kase, floyd() ? "Yes" : "No");
	}
	return 0;
}
