#include <cstdio>
#include <bitset>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAX_N = 16;
const int inf = 0x3f3f3f3f;

int V, G[MAX_N+5][MAX_N+5];
bitset<MAX_N+5> used;
int curLen, minLen = inf;
// minLenOf[i][j] 以i城市为当前城市，已经过j所表示的城市的状态下，
// 所能取得的最小代价
int minLenOf[MAX_N+5][(1<<16)+5];
// minLenNeededOf[i][j] 以i城市为当前城市，已经过j所表示的城市的状态下，
// 到达解状态所需的至少代价
int minLenNeededOf[MAX_N+5][(1<<16)+5];

// 已遍历n城市
void dfs(int curCity, int n)
{
	int cities = used.to_ulong();

	if(n == V) {
		minLen = min(minLen, curLen);
		return;
	}
	if(curLen >= minLen) return;
	if(curLen + minLenNeededOf[curCity][used.to_ulong()] >= minLen) return;
	if(minLenOf[curCity][cities]==-1 || curLen < minLenOf[curCity][cities])
		minLenOf[curCity][cities] = curLen;
	else if(curLen >= minLenOf[curCity][cities])
		return;

	if(n < V-1) {
		for(int j = 1; j < V-1; ++j) {
			if(!used[j]) {
				curLen += G[curCity][j];
				used[j] = 1;
				dfs(j, n+1);
				curLen -= G[curCity][j];
				used[j] = 0;
			}
		}
	} else {
		if(!used[V-1]) {
			curLen += G[curCity][V-1];
			used[V-1] = 1;
			dfs(V-1, n+1);
			curLen -= G[curCity][V-1];
			used[V-1] = 0;
		}
	}
}

int main()
{
	scanf("%d", &V);
	for(int i = 0; i < V; ++i)
		for(int j = 0; j < V; ++j)
			scanf("%d", &G[i][j]);

	used[0] = 1;
	memset(minLenOf, -1, sizeof(minLenOf));
	for(int i = 1; i < V; ++i) {
		for(int j = 1; j < (1<<V); ++j) {
			for(int k = 0; k < V; ++k) {
				if(!(j & (1 << k))) {
					int tmp = inf;
					for(int c = 0; c < V; ++c)
						if(c != k) tmp = min(tmp, G[c][k]);
					minLenNeededOf[i][j] += tmp;
				}
			}
		}
	}

	dfs(0, 1);
	printf("%d\n", minLen);
	return 0;
}
