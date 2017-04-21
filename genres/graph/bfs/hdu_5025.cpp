// HDU No.5025 Saving Tang Monk (bfs+状态压缩) (358MS 5200K)
#include <map>
#include <queue>
#include <cctype>
#include <cstring>
#include <iostream>
using namespace std;
const int MAX_N = 100;
typedef pair<int, int> Point;
struct P {
	int r, c, steps, key, snake;
	P(int r=0, int c=0, int s1=0, int k=0, int s2=0):
		r(r), c(c), steps(s1), key(k), snake(s2) {}
	bool operator>(const P &p) const { return steps > p.steps; }
};

map<Point, int> snake2bit;	// 将一个有蛇的点映射到一个比特位
int N, K, sr, sc, tr, tc;
char A[MAX_N+5][MAX_N+5];
bool used[MAX_N+5][MAX_N+5][1<<5][10];	// used[r][c][T][K] 有前K把钥匙，打过T的比特所表示的蛇，到达过(r, c)
char dr[] = {0,0,1,-1}, dc[] = {1,-1,0,0};

int bfs()
{
	// 因为打蛇的操作会花费时间(即所有边的权值不再相等)
	// 所以为保证得到最短路径，用优先队列而不用队列（类似于dijkstra)
	priority_queue<P, vector<P>, greater<P> > que;

	que.push(P(sr, sc));
	memset(used, 0, sizeof(used));
	used[sr][sc][0][0] = true;

	while(!que.empty()) {
		P p = que.top(); que.pop();
		if(p.r == tr && p.c == tc && p.key == K)	// 拥有了前K把钥匙到达(tr,tc)才算终止
			return p.steps;
		for(int i = 0; i < 4; ++i) {
			int nr = p.r+dr[i], nc = p.c+dc[i];
			if(0<=nr&&nr<N && 0<=nc&&nc<N && A[nr][nc]!='#' && !used[nr][nc][p.snake][p.key]) {
				if(A[nr][nc] == '.') {
					used[nr][nc][p.snake][p.key] = true;
					que.push(P(nr, nc, p.steps+1, p.key, p.snake));
				} else if(A[nr][nc] == 'S') {
					if(p.snake & snake2bit[Point(nr, nc)]) {	// 已打过这条蛇
						used[nr][nc][p.snake][p.key] = true;
						que.push(P(nr, nc, p.steps+1, p.key, p.snake));
					} else {	// 没打过这条蛇
						int newSnake = p.snake | snake2bit[Point(nr, nc)];
						used[nr][nc][newSnake][p.key] = true;
						que.push(P(nr, nc, p.steps+2, p.key, newSnake));
					}
				} else if(isdigit(A[nr][nc])) {
					if(A[nr][nc]-'0' - p.key == 1) {	// 有前n把钥匙才能拿第n+1把
						used[nr][nc][p.snake][p.key+1] = true;
						que.push(P(nr, nc, p.steps+1, p.key+1, p.snake));
					} else {
						used[nr][nc][p.snake][p.key] = true;
						que.push(P(nr, nc, p.steps+1, p.key, p.snake));
					}
				}
			}
		}
	}
	return -1;
}

int main()
{
	while(cin >> N >> K) {
		if(N == 0 && K == 0) break;

		int snakeCnt = 0;
		for(int i = 0; i < N; ++i) {
			for(int j = 0; j < N; ++j) {
				cin >> A[i][j];
				if(A[i][j] == 'K') {
					A[i][j] = '.';
					sr = i, sc = j;
				} else if(A[i][j] == 'T') {
					A[i][j] = '.';
					tr = i, tc = j;
				} else if(A[i][j] == 'S') {
					snake2bit[Point(i, j)] = 1 << snakeCnt;
					++snakeCnt;
				}
			}
		}
		int ans = bfs();
		if(ans == -1)
			cout << "impossible" << endl;
		else
			cout << ans << endl;
	}
	return 0;
}
