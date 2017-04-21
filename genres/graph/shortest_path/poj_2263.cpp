// POJ No.2263 Heavy Cargo (floyd求最大容量) (892K 125MS)
// 给一无向图，每条边有容量上限，问uv之间的路径的最大容量是？
// 相当与求uv之间的增广量，因为图很小，用floyd解决
// G[u][v] = max(G[u][v], min(G[u][k], G[k][v]))
#include <map>
#include <cstring>
#include <iostream>
using namespace std;
const int MAX_V = 200;

int V, E;
map<string, int> str2int;
int G[MAX_V+5][MAX_V+5];

int main()
{
	string str1, str2;
	int u, v, w, kase = 1;

	while(cin >> V >> E) {
		if(V == 0 && E == 0) break;
		str2int.clear();
		memset(G, 0, sizeof(G));

		int ncts = 0;
		for(int i = 0; i < E; ++i) {
			cin >> str1 >> str2 >> w;
			if(str2int[str1] == 0) str2int[str1] = ++ncts;
			if(str2int[str2] == 0) str2int[str2] = ++ncts;
			u = str2int[str1], v = str2int[str2];
			G[u][v] = G[v][u] = w;
		}
		
		for(int k = 1; k <= V; ++k)
			for(int i = 1; i <= V; ++i)
				for(int j = 1; j <= V; ++j)
					G[i][j] = max(G[i][j], min(G[i][k], G[k][j]));
		cin >> str1 >> str2;
		u = str2int[str1], v = str2int[str2];
		
		cout << "Scenario #" << kase++ << endl;
		cout << G[u][v] << " tons\n" << endl;
	}
}
