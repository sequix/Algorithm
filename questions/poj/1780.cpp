// POJ No.1780 Code (欧拉路构建) (5628K 63MS)
#include <cstdio>
using namespace std;
const int M = 100000;
const int TEN[] = {1, 10, 100, 1000, 10000, 100000, 1000000};

char ans[M*10];
int acnt, G[M];	// G[i] i号节点还未用过的首条边
int stop, stk[M*10];

void search(int from, int m)
{
	// 与深搜一样，其是在做选边的决策
	// 其其采取了一中贪心的选法：优先选序号小的边
	// 又因为是栈，最后出栈会的到字典序最大的一种答案
	while(G[from] < 10) {				// from节点还有边没有访问过
		int to = from * 10 + G[from];	// 获取下一个节点
		++G[from];						// 标记这条边也用过
		stk[stop++] = to;
		from = to % m;
	}
}

int main()
{
	int n, m, from;

	while(scanf("%d", &n) != EOF && n != 0) {
		if(n == 1) {
			puts("0123456789");
			continue;
		}
		m = TEN[n-1];
		stop = acnt = from = 0;
		for(int i = 0; i < m; ++i) G[i] = 0;
		search(from, m);
		while(stop > 0) {
			from = stk[--stop];
			// from的最后一位是边
			ans[acnt++] = from % 10 + '0';
			// from的前n-1位是点
			from /= 10;
			search(from, m);
		}
		// 注意现在的得到的ans是环状的答案，缺n-1位0
		for(int i = 1; i < n; ++i) putchar('0');
		while(acnt > 0) putchar(ans[--acnt]);
		putchar('\n');
	}
	return 0;
}
