// HDU No.1198 Farm Irrigation (DFS)
// 将图扩充为01形式，再用dfs统计相连的1有几片
#include <cstring>
#include <iostream>
using namespace std;

int N, M;
char cmap[55][55], map[200][200];
const int dir[][2] = {{0,1}, {0,-1}, {1,0}, {-1,0}};

void dfs(int r, int c)
{
	map[r][c] = 0;
	for(int i = 0; i < 4; ++i) {
		int nr = r + dir[i][0], nc = c + dir[i][1];
		if(0<=nr&&nr<N && 0<=nc&&nc<M && map[nr][nc]==1)
			dfs(nr, nc);
	}
}

int main()
{
	while(cin >> N >> M) {
		if(N == -1 && M == -1) break;
		for(int i = 0; i < N; ++i)
			for(int j = 0; j < M; ++j)
				cin >> cmap[i][j];
		memset(map, 0, sizeof(map));
		for(int i = 0; i < N; ++i) {
			for(int r = 0; r < 3; ++r) {
				if(r == 1) {		// 与中间点同行的行
					for(int j=0, c=0; j < M; ++j, c+=3) {
						map[3*i+r][c+1] = 1;
						if(strchr("ACFGHIK", cmap[i][j]) != NULL)	// LEFT
							map[3*i+r][c] = 1;
						if(strchr("BDFGIJK", cmap[i][j]) != NULL)	// RIGHT
							map[3*i+r][c+2] = 1;
					}
				} else if(r == 0) {		// UP
					for(int j=0, c=1; j < M; ++j, c+=3)
						if(strchr("ABEGHJK", cmap[i][j]) != NULL)
							map[3*i+r][c] = 1;
				} else {				// DOWN
					for(int j=0, c=1; j < M; ++j, c+=3)
						if(strchr("CDEHIJK", cmap[i][j]) != NULL)
							map[3*i+r][c] = 1;
				}
			}
		}
		int cnt = 0;
		N *= 3, M *= 3;
		for(int i = 0; i < N; ++i)
			for(int j = 0; j < M; ++j)
				if(map[i][j] == 1) ++cnt, dfs(i, j);
		cout << cnt << endl;
	}
}
