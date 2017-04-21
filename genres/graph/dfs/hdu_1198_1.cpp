// HDU No.1198 Farm Irrigation (DFS) (15MS 1624K)
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

int N, M;
bool used[55][55];
char map[55][55];
vector<pair<int,int> > pipe[11];

void init()
{
	pipe[0].push_back(make_pair(0, -1));
	pipe[0].push_back(make_pair(-1, 0));
	pipe[1].push_back(make_pair(-1, 0));
	pipe[1].push_back(make_pair(0, 1));
	pipe[2].push_back(make_pair(1, 0));
	pipe[2].push_back(make_pair(0, -1));
	pipe[3].push_back(make_pair(1, 0));
	pipe[3].push_back(make_pair(0, 1));
	pipe[4].push_back(make_pair(-1, 0));
	pipe[4].push_back(make_pair(1, 0));
	pipe[5].push_back(make_pair(0, -1));
	pipe[5].push_back(make_pair(0, 1));
	pipe[6].push_back(make_pair(0, -1));
	pipe[6].push_back(make_pair(0, 1));
	pipe[6].push_back(make_pair(-1, 0));
	pipe[7].push_back(make_pair(-1, 0));
	pipe[7].push_back(make_pair(1, 0));
	pipe[7].push_back(make_pair(0, -1));
	pipe[8].push_back(make_pair(0, -1));
	pipe[8].push_back(make_pair(0, 1));
	pipe[8].push_back(make_pair(1, 0));
	pipe[9].push_back(make_pair(-1, 0));
	pipe[9].push_back(make_pair(1, 0));
	pipe[9].push_back(make_pair(0, 1));
	pipe[10].push_back(make_pair(0, 1));
	pipe[10].push_back(make_pair(0, -1));
	pipe[10].push_back(make_pair(-1, 0));
	pipe[10].push_back(make_pair(1, 0));
}

// 可从dir方向流入map[r][c]
bool canflowin(int r, int c, pair<int,int> dir)
{
	int t = map[r][c] - 'A';
	vector<pair<int,int> >::iterator it = pipe[t].end();
	if(dir == make_pair(-1, 0))
		return find(pipe[t].begin(), pipe[t].end(), make_pair(1,0)) != it;
	else if(dir == make_pair(1, 0))
		return find(pipe[t].begin(), pipe[t].end(), make_pair(-1,0)) != it;
	else if(dir == make_pair(0, 1))
		return find(pipe[t].begin(), pipe[t].end(), make_pair(0,-1)) != it;
	else if(dir == make_pair(0, -1))
		return find(pipe[t].begin(), pipe[t].end(), make_pair(0,1)) != it;
}

void dfs(int r, int c)
{
	used[r][c] = true;
	int t = map[r][c] - 'A';
	for(int i = 0; i < pipe[t].size(); ++i) {
		int nr = r + pipe[t][i].first, nc = c + pipe[t][i].second;
		if(0<=nr&&nr<N && 0<=nc&&nc<M && !used[nr][nc]
				&& canflowin(nr, nc, pipe[t][i]))
			dfs(nr, nc);
	}
}

int main()
{
	init();
	while(cin >> N >> M) {
		if(N == -1 && M == -1) break;
		for(int i = 0; i < N; ++i)
			for(int j = 0; j < M; ++j)
				cin >> map[i][j];
		int cnt = 0;
		memset(used, 0, sizeof(used));
		for(int i = 0; i < N; ++i)
			for(int j = 0; j < M; ++j)
				if(!used[i][j]) { ++cnt; dfs(i, j); }
		cout << cnt << endl;
	}
}
