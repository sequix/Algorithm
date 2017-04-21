// HDU No.1010 Tempter of the Bone (DFS) (156MS 1584K)
#include <cstring>
#include <iostream>
using namespace std;

int N, M, T;
int sr, sc, dr, dc;
char maze[9][9];
char dir[][2] = {{-1,0}, {1,0}, {0,1}, {0,-1}};

bool dfs(int r, int c, int dep)
{
	if(r == dr && c == dc && dep == T) return true;

	int needed_steps = T - dep;
	int distance = abs(dr-r) + abs(dc-c);
	int t = needed_steps - distance;
	if(t < 0 || t % 2 == 1) return false;	// 奇偶剪枝

	for(int i = 0; i < 4; ++i) {
		int nr = r + dir[i][0], nc = c + dir[i][1];
		if(0<=nr&&nr<N && 0<=nc&&nc<M && maze[nr][nc] != 'X') {
			maze[nr][nc] = 'X';
			if(dfs(nr, nc, dep+1)) return true;
			maze[nr][nc] = '.';
		}
	}
	return false;
}

int main()
{
	while(cin >> N >> M >> T) {
		if(N == 0 && M == 0 && T == 0) break;

		int nwall = 0;
		for(int i = 0; i < N; ++i) {
			for(int j = 0; j < M; ++j) {
				cin >> maze[i][j];
				if(maze[i][j] == 'S') sr = i, sc = j;
				else if(maze[i][j] == 'D') dr = i, dc = j;
				else if(maze[i][j] == 'X') ++nwall;
			}
		}
		if(N*M - nwall - 1 < T) {	// 减1是排除起始点，因为它不占时间
			cout << "NO" << endl;
			continue;
		}
		maze[sr][sc] = 'X';
		cout << (dfs(sr, sc, 0) ? "YES" : "NO") << endl;
	}
}
