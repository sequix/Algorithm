// Snakes and Ladders
#include <cstdio>
#include <cstring>
using namespace std;
const int MAX_N = 20;

int a, b, N, S, L, portal[MAX_N*MAX_N+5];
bool G[MAX_N*MAX_N+5];	// 当前状态
bool LG[MAX_N*MAX_N+5];	// 前一次状态

int main()
{
	while(scanf("%d%d%d", &N, &S, &L) != EOF) {
		memset(G, 0, sizeof(G));
		memset(portal, 0, sizeof(portal));
		for(int i = 0; i < S+L; ++i) {
			scanf("%d%d", &a, &b);
			portal[a] = b;
		}
		G[1] = 1;
		int step = 0;
		while(G[N*N] == 0) {
			memcpy(LG, G, sizeof(G));
			// G中保存每次新走出到的位置，
			// 因为已经处理过的位置不需要再进行处理
			memset(G, 0, sizeof(G));
			for(int i = 1; i <= N*N-1; ++i) {
				if(LG[i] == 0) continue;
				for(int k = 1; k <= 6; ++k)
					G[(portal[i+k] != 0) ? portal[i+k] : i+k] = 1;
			}
			++step;
		}
		printf("%d\n", step);
	}
}
