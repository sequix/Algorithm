// POJ No.1195 Mobile Phones (二维树状数组) (4532K 1047MS)
#include <cstdio>
#include <cstring>
using namespace std;
const int MAX_N = 1024;

int N, C[MAX_N+5][MAX_N+5], lowbit[MAX_N+5];

void update(int y, int x, int a)
{
	// C中的每一行都是一个树状数组
	for(int i = y; i <= N; i += lowbit[i])
		for(int j = x; j <= N; j += lowbit[j])
			C[i][j] += a;
}

// 第1行到第y行，第1列到第x列的和
int getsum(int y, int x)
{
	int sum = 0;
	for(int i = y; i > 0; i -= lowbit[i])
		for(int j = x; j > 0; j -= lowbit[j])
			sum += C[i][j];
	return sum;
}

int main()
{
	int cmd, x, y, a, l, b, r, t;

	for(int i = 1; i <= MAX_N; ++i)
		lowbit[i] = i & (-i);

	while(true) {
		scanf("%d", &cmd);
		switch(cmd) {
			case 0:
				scanf("%d", &N);
				memset(C, 0, sizeof(C));
				break;
			case 1:	// 树状数组的下标是从1开始的
				scanf("%d%d%d", &x, &y, &a);
				update(y+1, x+1, a);
				break;
			case 2:
				scanf("%d%d%d%d", &l, &b, &r, &t);
				++l, ++b, ++r, ++t;
				// 注意所求的是包含4条边界的
				printf("%d\n", getsum(t, r) +
					getsum(b-1, l-1) - getsum(t, l-1) - getsum(b-1, r));
				break;
			case 3:
				return 0;
		}
	}
}
