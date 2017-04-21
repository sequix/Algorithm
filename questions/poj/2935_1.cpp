// HDU No.2935 Basic Wall Maze (BFS+扩图表示墙) (348K 0MS)
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

struct P {
	char dc;	// 从前一步到这步的走法
	int r, c, pre;
	P(int r=0, int c=0, int p=0, char m=0):
		r(r), c(c), pre(p), dc(m) {}
};

P que[1000];
int qhead, qtail;

int G[13][13];	// G[i][j] == 1表示(i,j)位置有墙
bool used[13][13];
int sr, sc, dr, dc;
const char dirch[] = "SNWE";
const int dir1[][2] = {{1,0}, {-1,0}, {0,-1}, {0,1}};
const int dir2[][2] = {{2,0}, {-2,0}, {0,-2}, {0,2}};

int bfs()
{
	memset(used, false, sizeof(used));
	used[sr][sc] = true;
	que[qtail++] = P(sr, sc, -1);

	while(qtail != qhead) {
		P p = que[qhead++];
		if(p.r == dr && p.c == dc)
			return qhead-1;
		for(int i = 0; i < 4; ++i) {
			if(G[p.r+dir1[i][0]][p.c+dir1[i][1]] == 1) continue;
			int nr = p.r + dir2[i][0], nc = p.c + dir2[i][1];
			if(nr<0 || nr>=12 || nc<0 || nc>=12 || used[nr][nc]) continue;
			used[nr][nc] = true;
			que[qtail++] = P(nr, nc, qhead-1, dirch[i]);
		}
	}
	return -1;
}

int main()
{
	char ans[64];
	int wr1, wr2, wc1, wc2;

	while(scanf("%d%d", &sc, &sr) != EOF && sr+sc != 0) {
		scanf("%d%d", &dc, &dr);
		sr = 2*sr-1, sc = 2*sc-1;
		dr = 2*dr-1, dc = 2*dc-1;

		qtail = qhead = 0;
		memset(G, 0, sizeof(G));

		for(int i = 0; i < 3; ++i) {
			scanf("%d%d%d%d", &wc1, &wr1, &wc2, &wr2);
			wr1*=2, wr2*=2, wc1*=2, wc2*=2;
			if(wr1 == wr2) {	// 横墙
				if(wc1 > wc2) swap(wc1, wc2);
				for(int i = wc1; i < wc2; ++i)
					G[wr1][i] = 1;
			} else {			// 竖墙
				if(wr1 > wr2) swap(wr1, wr2);
				for(int i = wr1; i < wr2; ++i)
					G[i][wc1] = 1;
			}
		}

		int cnt = 0;
		for(int i = bfs(); i != -1; i = que[i].pre)
			ans[cnt++] = que[i].dc;
		// 注意，上面循环会把起点的dc也加入ans，所以要-2而不是-1
		for(int i = cnt-2; i >= 0; --i)
			putchar(ans[i]);
		putchar('\n');
	}
}
