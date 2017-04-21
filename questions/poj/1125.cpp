// POJ No.1125 Stockbroker Grapevine (floyd) (360K 0MS)
#include <cstdio>
#include <algorithm>
using namespace std;
const int MAX_V = 100;
const int INF = 0x3f3f3f3f;

int max_distance[MAX_V+5];
int V, G[MAX_V+5][MAX_V+5];

int main()
{
	int n, a, b;

	while(~scanf("%d", &V) && V != 0) {
		for(int i = 1; i <= V; ++i)
			for(int j = 1; j <= V; ++j)
				G[i][j] = (i == j) ? 0 : INF;

		for(int i = 1; i <= V; ++i) {
			scanf("%d", &n);
			while(n-- > 0) {
				scanf("%d%d", &a, &b);
				G[i][a] = b;
			}
		}

		for(int k = 1; k <= V; ++k)
			for(int i = 1; i <= V; ++i)
				for(int j = 1; j <= V; ++j)
					G[i][j] = min(G[i][j], G[i][k] + G[k][j]);

		for(int i = 1; i <= V; ++i) {
			int t = -1;
			for(int j = 1; j <= V; ++j)
				if(G[i][j] > t) t = G[i][j];
			max_distance[i] = t;
		}

		int min_num = 0, min_distance = INF;
		for(int i = 1; i <= V; ++i) {
			if(max_distance[i] < min_distance) {
				min_num = i;
				min_distance = max_distance[i];
			}
		}
		printf("%d %d\n", min_num, min_distance);
	}
	return 0;
}
