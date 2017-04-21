// HDU No.2066 一个人的旅行 (Floyd) (TLE)
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int INF = 0x3f3f3f3f;
const int MAX_V = 1000;

int V, T, S, D, ans = INF;
int sour[MAX_V+5], dest[MAX_V+5];
int G[MAX_V+5][MAX_V+5];

void floyd()
{
	for(int k = 1; k <= V; ++k)
		for(int i = 1; i <= V; ++i)
			for(int j = 1; j <= V; ++j) {
				G[i][j] = min(G[i][j], G[i][k] + G[k][j]);
				if(find(sour, sour+S, i)!=sour+S &&
						find(dest, dest+T, j)!=dest+T)
					ans = min(ans, G[i][j]);
			}
}

int main()
{
	int a, b, c;

	while(cin >> T >> S >> D) {
		memset(G, INF, sizeof(G));
		for(int i = 1; i <= MAX_V; ++i)
			G[i][i] = 0;
		for(int i = 0; i < T; ++i) {
			cin >> a >> b >> c;
			V = max(V, max(a, b));
			if(c < G[a][b]) G[a][b] = G[b][a] = c;
		}
		for(int i = 0; i < S; ++i)
			cin >> sour[i];
		for(int i = 0; i < D; ++i)
			cin >> dest[i];
		floyd();
		cout << ans << endl;	
	}
	return 0;
}
