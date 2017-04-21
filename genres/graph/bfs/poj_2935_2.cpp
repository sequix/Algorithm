// HDU No.2935 Basic Wall Maze (BFS+数组加一维表示墙) (332K 16MS)
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

P que[100];
int qhead, qtail;

bool used[7][7];
bool G[7][7][4];	// G[i][j][k] 表示(i,j)位置是否有k方向的墙
int sr, sc, dr, dc;
const char dirch[] = "NESW";	// 上面的方向k与这个一致
const int dir[][2] = {{-1,0}, {0,1}, {1,0}, {0,-1}};

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
			int nr = p.r + dir[i][0], nc = p.c + dir[i][1];
			if(1<=nr&&nr<=6 && 1<=nc&&nc<=6 && !used[nr][nc]
					&& G[p.r][p.c][i] == 0) {
				used[nr][nc] = true;
				que[qtail++] = P(nr, nc, qhead-1, dirch[i]);
			}
		}
	}
	return -1;
}

int main()
{
	char ans[64];
	int wr1, wr2, wc1, wc2;

	while(scanf("%d%d", &sc, &sr) != EOF) {
		if(sr == 0 && sc == 0) break;
		qtail = qhead = 0;
		memset(G, 0, sizeof(G));
		scanf("%d%d", &dc, &dr);

		for(int j = 0; j < 3; ++j) {
			scanf("%d%d%d%d", &wc1, &wr1, &wc2, &wr2);
			if(wr1 == wr2) {	// 横墙
				if(wc1 > wc2) swap(wc1, wc2);
				for(int i = wc1+1; i <= wc2; ++i) {
					G[wr1][i][2] = 1;
					if(wr1 != 6) G[wr1+1][i][0] = 1;
				}
			} else {			// 竖墙
				if(wr1 > wr2) swap(wr1, wr2);
				for(int i = wr1+1; i <= wr2; ++i) {
					G[i][wc1][1] = 1;
					if(wc1 != 6) G[i][wc1+1][3] = 1;
				}
			}
		}

		int cnt = 0;
		for(int i = bfs(); i != -1; i = que[i].pre)
			ans[cnt++] = que[i].dc;
		for(int i = cnt-2; i >= 0; --i)
			putchar(ans[i]);
		putchar('\n');
	}
}
