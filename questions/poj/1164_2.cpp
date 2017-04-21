// POJ No.1164 The Castle (DFS + stack) (732K 32MS)
#include <stack>
#include <iostream>
using namespace std;
const int MAX_N = 50;

int R, C, roomNum, roomArea, maxRoomArea;
int rooms[MAX_N+5][MAX_N+5], color[MAX_N+5][MAX_N+5];
struct Room { int r, c; Room(int rr, int cc): r(rr), c(cc) {} };

void dfs(int r, int c)
{
	stack<Room> stk;
	stk.push(Room(r, c));
	while(!stk.empty()) {
		Room rm = stk.top(); stk.pop();
		if(color[rm.r][rm.c] != 0) continue;
		++roomArea; color[rm.r][rm.c] = roomNum;
		if((rooms[rm.r][rm.c] & 1) == 0) stk.push(Room(rm.r, rm.c-1));
		if((rooms[rm.r][rm.c] & 2) == 0) stk.push(Room(rm.r-1, rm.c));
		if((rooms[rm.r][rm.c] & 4) == 0) stk.push(Room(rm.r, rm.c+1));
		if((rooms[rm.r][rm.c] & 8) == 0) stk.push(Room(rm.r+1, rm.c));
	}
}

int main()
{
	cin >> R >> C;
	for(int i = 1; i <= R; ++i)
		for(int j = 1; j <= C; ++j)
			cin >> rooms[i][j];
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
