// HDU No.2066 一个人的旅行 (Floyd+剪枝) (280MS 5552K)
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int INF = 0x3f3f3f3f;
const int MAX_V = 1000;

int V, T, S, D, ans = INF;
int G[MAX_V+5][MAX_V+5];
bool sour[MAX_V+5], dest[MAX_V+5];

void floyd()
{
	for(int k = 1; k <= V; ++k)
		for(int i = 1; i <= V; ++i) {
			if(G[i][k] == INF) continue;
			for(int j = 1; j <= V; ++j) {
				G[i][j] = min(G[i][j], G[i][k] + G[k][j]);
				if(dest[i] && sour[j]) ans = min(ans, G[i][j]);
			}
		}
}

int main()
{
	int a, b, c, t;

	while(cin >> T >> S >> D) {
		V = 0;
		ans = INF;
		for(int i = 1; i <= MAX_V; ++i) {
			sour[i] = dest[i] = false;
			for(int j = 1; j <= MAX_V; ++j)
				if(i == j) G[i][i] = 0;
				else G[i][j] = INF;
		}

		for(int i = 0; i < T; ++i) {
			cin >> a >> b >> c;
			V = max(V, max(a, b));
			if(c < G[a][b]) G[a][b] = G[b][a] = c;
		}
		floyd();

		for(int i = 0; i < S; ++i) {
			cin >> t;
			sour[t] = true;
		}
		for(int i = 0; i < D; ++i) {
			cin >> t;
			dest[t] = true;
		}
		cout << ans << endl;
	}
	return 0;
}
