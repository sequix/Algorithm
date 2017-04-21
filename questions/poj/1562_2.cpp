// POJ No.1562 Oil Deposits (DFS+染色) (768K 16MS)
#include <vector>
#include <iostream>
using namespace std;
const int MAX_N = 100;
struct P { int r, c; P(int rr, int cc): r(rr), c(cc) {} };

int R, C;
char A[MAX_N+5][MAX_N+5];
char dr[]={1,-1,0,0,1,1,-1,-1}, dc[]={0,0,1,-1,1,-1,1,-1};

void dfs(int r, int c)
{
	A[r][c] = '*';
	for(int i = 0; i < 8; ++i) {
		int nr = r + dr[i], nc = c + dc[i];
		if(0<=nr&&nr<R && 0<=nc&&nc<C && A[nr][nc]=='@')
			dfs(nr, nc);
	}
}

int main()
{
	while(cin >> R >> C) {
		if(R == 0 && C == 0) break;
		vector<P> v;
		for(int i = 0; i < R; ++i)
			for(int j = 0; j < C; ++j) {
				cin >> A[i][j];
				if(A[i][j] == '@') v.push_back(P(i, j));
			}
		int ans = 0;
		for(int i = 0; i < v.size(); ++i)
			if(A[v[i].r][v[i].c] == '@')
				++ans, dfs(v[i].r, v[i].c);
		cout << ans << endl;
	}
	return 0;
}
