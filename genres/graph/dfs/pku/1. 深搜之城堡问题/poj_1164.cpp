// POJ No.1164 The Castle (DFS) (752K 16MS)
#include <iostream>
using namespace std;
const int MAX_N = 50;

int R, C, roomNum, roomArea, maxRoomArea;
int map[MAX_N+5][MAX_N+5], color[MAX_N+5][MAX_N+5];

void dfs(int r, int c)
{
	if(color[r][c] != 0) return;
	++roomArea;
	color[r][c] = roomNum;
	if((map[r][c] & 1) == 0) dfs(r, c-1);
	if((map[r][c] & 2) == 0) dfs(r-1, c);
	if((map[r][c] & 4) == 0) dfs(r, c+1);
	if((map[r][c] & 8) == 0) dfs(r+1, c);
}

int main()
{
	cin >> R >> C;
	for(int i = 1; i <= R; ++i)
		for(int j = 1; j <= C; ++j)
			cin >> map[i][j];
	for(int i = 1; i <= R; ++i)
		for(int j = 1; j <= C; ++j) {
			if(color[i][j] == 0) {
				++roomNum; roomArea = 0;
				dfs(i, j);
				maxRoomArea = max(maxRoomArea, roomArea);
			}
		}
	cout << roomNum << endl;
	cout << maxRoomArea << endl;
	return 0;
}
