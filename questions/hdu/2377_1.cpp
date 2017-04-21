// HDU No.2377 Bus Pass (BFS) (312MS 1996K)
#include <queue>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAX_N = 10000;

int nz, nr, cur;	// cur表示当前公交站点次序，从0开始
int nto[MAX_N];		// nto[i]与i区域相邻的区域数
int res[MAX_N];		// 每条线路上的每个地区到地区i的最大距离
int reach[MAX_N];	// reach[s]==k 表示s地区已经被前k个站点访问过了
int G[MAX_N][10];

void bfs(int s)
{
	int a = 0, b = 1;
	int at, dep = 1;	// 当前节点; 深度（层数）
	queue<int> que[2];	// 为表示层次，使用滚动队列

	if(reach[s] < cur) {	// s地区还未被cur站点访问过
		que[b].push(s);
		reach[s] = cur;
		res[s] = max(res[s], dep);
	}
	while(!que[b].empty()) {
		swap(a, b); ++dep;
		while(!que[a].empty()) {
			at = que[a].front(); que[a].pop();
			for(int i = 0; i < nto[at]; ++i) {
				if(reach[G[at][i]] < cur) {
					que[b].push(G[at][i]);
					reach[G[at][i]] = cur;
					res[G[at][i]] = max(res[G[at][i]], dep);
				}
			}
		}
	}
}

int main()
{
	int T, from, id, to, nnr;

	for(scanf("%d", &T); T > 0; --T) {
		cur = 0;
		memset(reach, -1, sizeof(reach));
		memset(res, 0, sizeof(res));

		scanf("%d%d", &nz, &nr);
		for(int i = 0; i < nz; ++i) {
			//scanf("%d%d", &from, &nto[from]);
			// 注意C/C++实参的传递是无序的
			scanf("%d", &from);
			scanf("%d", &nto[from]);
			for(int j = 0; j < nto[from]; ++j)
				scanf("%d", &G[from][j]);
		}
		for(int i = 0; i < nr; ++i) {
			scanf("%d", &nnr);
			for(int j = 0; j < nnr; ++j) {
				scanf("%d", &id);
				bfs(id), ++cur;
			}
		}
		int threshold = 0x3f3f3f3f, center = -1;
		for(int i = 0; i < MAX_N; ++i) {
			if(reach[i] == cur-1 && res[i] < threshold) {
				threshold = res[i];
				center = i;
			}
		}
		printf("%d %d\n", threshold, center);
	}
}
