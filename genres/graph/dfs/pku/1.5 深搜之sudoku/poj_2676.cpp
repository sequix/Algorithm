4// POJ No.2676 Sudoku (DFS) (712K 0MS)
#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
typedef pair<int, int> Point;

int board[9][9];
vector<Point> blankpoints;
bool rowflags[9][10], colflags[9][10], blkflags[9][10];

int blknum(int r, int c)
{
	return (r/3)*3 + c/3;
}

void setflag(int r, int c, int num, bool flag)
{
	rowflags[r][num] = flag;
	colflags[c][num] = flag;
	blkflags[blknum(r,c)][num] = flag;
}

bool isok(int r, int c, int num)
{
	return !rowflags[r][num] && !colflags[c][num] &&
		!blkflags[blknum(r,c)][num];
}

bool dfs(int n)
{
	if(n < 0) return true;
	int r = blankpoints[n].first, c = blankpoints[n].second;
	for(int i = 1; i <= 9; ++i) {
		if(isok(r, c, i)) {
			board[r][c] = i;
			setflag(r, c, i, true);
			if(dfs(n-1)) return true;
			setflag(r, c, i, false);
		}
	}
	return false;
}

int main()
{
	int T;

	for(cin >> T; T > 0; --T) {
		for(int i = 0; i < 9; ++i) {
			for(int j = 0; j < 9; ++j) {
				char c; cin >> c;
				board[i][j] = c - '0';
				if(board[i][j] == 0) blankpoints.push_back(Point(i, j));
				else setflag(i, j, board[i][j], true);
			}
		}
		if(dfs(blankpoints.size()-1)) {
			for(int i = 0; i < 9; ++i) {
				for(int j = 0; j < 9; ++j)
					putchar('0' + board[i][j]);
				putchar('\n');
			}
		}
		blankpoints.clear();
		memset(rowflags, false, sizeof(rowflags));
		memset(colflags, false, sizeof(colflags));
		memset(blkflags, false, sizeof(blkflags));
	}
	return 0;
}
