// POJ No.3984 迷宫问题
#include <cstdio>
using namespace std;

int tail = 0, head = 0;
struct Point { int x, y; } ans[100];
struct Node { int x, y, pre; } que[100];

void inque(int x, int y, int pre)
{
	que[tail].x = x;
	que[tail].y = y;
	que[tail++].pre = pre;
}
int outque() { return head++; }
bool empty() { return tail - head == 0; }

char maze[5][5];
bool used[5][5];
char dx[] = {0,0,1,-1}, dy[] = {1,-1,0,0};

int main()
{
	int ans_tail;

	for(int i = 0; i < 5; ++i)
		for(int j = 0; j < 5; ++j)
			scanf("%d", &maze[i][j]);

	inque(0, 0, -1);
	used[0][0] = true;
	while(!empty()) {
		int p = outque();
		if(que[p].x == 4 && que[p].y == 4) {
			ans_tail = p;
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
	for(int i = ans_tail; que[i].pre != -1; i = que[i].pre) {
		ans[cnt].x = que[i].x;
		ans[cnt].y = que[i].y;
		++cnt;
	}

	printf("(0, 0)\n");
	for(int i = cnt-1; i >= 0; --i)
		printf("(%d, %d)\n", ans[i].x, ans[i].y);
	return 0;
}
