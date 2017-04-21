// POJ No.1275 Cashier Employment (差分约束) (480K 32MS)
#include <cstdio>
#include <cstring>
using namespace std;

struct Edge {
	int u, v, w;
	Edge(int u=0, int v=0, int w=0): u(u), v(v), w(w) {}
} es[10000];

int N;			// 应聘人数
int E;			// 边数
int need[25];	// need[i] 第i个小时所需人数
int have[25];	// C[i] 第i个小时应聘人数

bool has_negataive_loop()
{
	int dis[25] = {0};

	for(int i = 0; i < 25; ++i) {	// 0到24，共25个点
		bool update = false;
		for(int j = 0; j < E; ++j) {
			if(dis[es[j].v] > dis[es[j].u] + es[j].w) {
				update = true;
				dis[es[j].v] = dis[es[j].u] + es[j].w;
			}
		}
		if(!update) break;
		if(i == 24) return true;
	}
	return false;
}

int main()
{
	int T, tmp;

	for(scanf("%d", &T); T > 0; --T) {
		for(int i = 1; i <= 24; ++i)
			scanf("%d", &need[i]);
		scanf("%d", &N);
		for(int i = 0; i < N; ++i) {
			scanf("%d", &tmp);
			++have[tmp+1];
		}

		E = 0;
		for(int i = 1; i <= 24; ++i) {
			es[E++] = Edge(i-1, i, have[i]);
			es[E++] = Edge(i, i-1, 0);
			if(i >= 8) es[E++] = Edge(i, i-8, -need[i]);
		}

		int lim = 0, oE = E;
		bool has_solution = false;
		for(; lim <= N; ++lim) {
			E = oE;
			for(int i = 1; i <= 8; ++i)
				es[E++] = Edge(i, i-8+24, lim-need[i]);
			es[E++] = Edge(24, 0, -lim);
			if(!has_negataive_loop()) { has_solution = true; break; }
		}

		if(has_solution)
			printf("%d\n", lim);
		else
			puts("No Solution");
	}
}
