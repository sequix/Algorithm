// POJ No.3660 Cow Contest (floyd) (428K 0MS)
// 给出“A胜B”和总参赛人数，求可以判断出名次的人的数目。
// 将每个“A胜B”抽象成A到B的一条有向边，那么可被判断出名次的
// 人数就等于求传递闭包后，出度加入度等于n-1的点数。
// 另一种做法是：传递闭包后，找A无法到B，B也无法到A的点对
// 这样的点对即是胜负关系无法确定的点，从总数中减去即是所求
#include <cstdio>
#include <algorithm>
using namespace std;
const int MAX_V = 100;
const int inf = 0x3f3f3f3f;

bool unknown[MAX_V+5];
int a, b, V, E, d[MAX_V+5][MAX_V+5];

int main()
{
	scanf("%d%d", &V, &E);
	for(int i = 1; i <= V; ++i)
		for(int j = 1; j <= V; ++j)
			d[i][j] = (i==j) ? 0 : inf;
	for(int i = 0; i < E; ++i) {
		scanf("%d%d", &a, &b);
		d[a][b] = 1;
	}
	for(int k = 1; k <= V; ++k)
		for(int i = 1; i <= V; ++i)
			for(int j = 1; j <= V; ++j)
				d[i][j] = min(d[i][j], d[i][k]+d[k][j]);
	for(int i = 1; i <= V; ++i)
		for(int j = 1; j <= V; ++j)
			if(d[i][j]==inf && d[j][i]==inf)
				unknown[i] = unknown[j] = true;
	int cnt = 0;
	for(int i = 1; i <= V; ++i)
		if(unknown[i]) ++cnt;
	printf("%d\n", V - cnt);
	return 0;
}
