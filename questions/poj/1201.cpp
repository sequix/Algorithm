// POJ No.1201 Intervals (差分约束) (1136K 204MS)
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAX_N = 50000;
const int INF = 0x3f3f3f3f;

struct Edge {
	int from, to, weight;
	Edge(int f=0, int t=0, int w=0): from(f), to(t), weight(w) {}
} es[MAX_N+5];

int E, dis[MAX_N+5];	// dis[i]=S[i]-S[mx]，而S[i]-S[mx]<=0，所以初始化为0
int mx = -INF, mn = INF;

void bellmen_ford()
{
	for(int i = 0; i < MAX_N; ++i) {
		bool update = false;
		for(int j = 0; j < E; ++j) {
			Edge &e = es[j];
			if(dis[e.to] > dis[e.from] + e.weight) {
				dis[e.to] = dis[e.from] + e.weight;
				update = true;
			}
		}
		for(int j = mn; j <= mx; ++j) {
			if(dis[j] > dis[j-1] + 1) {
				dis[j] = dis[j-1] + 1;
				update = true;
			}
		}
		for(int j = mx; j >= mn; --j) {
			if(dis[j-1] > dis[j]) {
				dis[j-1] = dis[j];
				update = true;
			}
		}
		if(!update) break;
	}
}

int main()
{
	int a, b, c;

	scanf("%d", &E);
	for(int i = 0; i < E; ++i) {
		scanf("%d%d%d", &a, &b, &c);
		es[i] = Edge(b, a-1, -c);
		mn = min(mn, a);
		mx = max(mx, b);
	}
	bellmen_ford();
	printf("%d\n", dis[mx] - dis[mn-1]);
}
