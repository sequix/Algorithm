// POJ No.3984 迷宫问题 (BFS) (388K 0MS)
#include <cstdio>
using namespace std;

int tail = 0, head = 0;
struct Node { int x, y, pre; } que[100];

void inque(int x, int y, int pre)
{
	que[tail].x = x;
	que[tail].y = y;
	que[tail++].pre = pre;
}
int outque() { return head++; }
bool empty() { return tail - head == 0; }

int path[100];
char maze[5][5];
bool used[5][5];
char dx[] = {0,0,1,-1}, dy[] = {1,-1,0,0};

int main()
{
	int path_tail;

	for(int i = 0; i < 5; ++i)
		for(int j = 0; j < 5; ++j)
			scanf("%d", &maze[i][j]);

	inque(0, 0, -1);
	used[0][0] = true;
	while(!empty()) {
		int p = outque();
		if(que[p].x == 4 && que[p].y == 4) {
			path_tail = p;
			break;
		}
		for(int i = 0; i < 4; ++i) {
			int nx = que[p].x + dx[i], ny = que[p].y + dy[i];
			if(0<=nx&&nx<5 && 0<=ny&&ny<5 &&
					maze[nx][ny]==0 && !used[nx][ny]) {
				inque(nx, ny, p);
				used[nx][ny] = true;
			}
		}
	}

	int cnt = 0;
	for(int i = path_tail; que[i].pre != -1; i = que[i].pre)
		path[cnt++] = i;

	printf("(0, 0)\n");
	for(int i = cnt-1; i >= 0; --i)
		printf("(%d, %d)\n", que[path[i]].x, que[path[i]].y);
	return 0;
}
