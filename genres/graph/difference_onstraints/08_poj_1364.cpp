// POJ No.1364 King (差分约束) (344K 0MS)
#include <cstdio>
#include <cstring>
using namespace std;

struct Edge {
	int u, v, w;
	Edge(int u=0, int v=0, int w=0): u(u), v(v), w(w) {}
} es[105];

int N, M;

bool has_negative_loop()
{
	int dis[105] = {0};

	for(int i = 0; i < N+1; ++i) {	// 从0到N，共有N+1个节点
		bool update = false;
		for(int j = 0; j < M; ++j) {
			if(dis[es[j].v] > dis[es[j].u] + es[j].w) {
				dis[es[j].v] = dis[es[j].u] + es[j].w;
				update = true;
			}
		}
		if(!update) break;
		if(i == N) return true;
	}
	return false;
}

int main()
{
	char s[3];
	int a, b, c;

	while(scanf("%d", &N) != EOF && N != 0) {
		scanf("%d", &M);
		for(int i = 0; i < M; ++i) {
			scanf("%d%d%s%d", &a, &b, s, &c);
			if(s[0] == 'l')
				es[i] = Edge(a-1, a+b, c-1);	
			else
				es[i] = Edge(a+b, a-1, -c-1);
		}
		if(has_negative_loop())
			puts("successful conspiracy");
		else
			puts("lamentable kingdom");
	}
}
