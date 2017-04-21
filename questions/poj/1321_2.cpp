// POJ No.1321 棋盘问题 (DFS) (692K 47MS)
#include <cstring>
#include <iostream>
using namespace std;
const int MAX_N = 8;

int N, K, ans;
char A[MAX_N+5][MAX_N+5];
bool rowflag[MAX_N+5], colflag[MAX_N+5];
#define setflag(r, c, f) (rowflag[r] = colflag[c] = (f))
#define isok(r, c) (!rowflag[r] && !colflag[c])

// 本次处理row行，已经选择cnt个位置
void dfs(int row, int cnt)
{
	if(cnt == K) { ++ans; return; }
	if(row == N) return;

	for(int i = 0; i < N; ++i)
		if(A[row][i] == '#' && isok(row, i)) {
			setflag(row, i, true);
			dfs(row+1, cnt+1);
			setflag(row, i, false);
		}
	dfs(row+1, cnt);	// 当前行谁也不选
}

int main()
{
	while(cin >> N >> K) {
		if(N == -1 && K == -1) break;
		for(int i = 0; i < N; ++i)
			for(int j = 0; j < N; ++j)
				cin >> A[i][j];
		memset(rowflag, 0, sizeof(rowflag));
		memset(colflag, 0, sizeof(colflag));
		ans = 0;
		dfs(0, 0);
		cout << ans << endl;
	}
	return 0;
}
