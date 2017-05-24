// POJ No.2828 Buy Tickets (树状数组) (4080K 2250MS)
#include <cstdio>
using namespace std;
const int MAX_N = 200000;

int N, lowbit[MAX_N+5], C[MAX_N+5];	// C[i]: 前i个作为中有几个空位
int nths[MAX_N+5], vals[MAX_N+5], ans[MAX_N+5];

// 坐第i个座
void takeSeat(int i)
{
	for(; i <= N; i += lowbit[i])
		--C[i];
}

// 返回前i个（包括第i个）座中有多少空位
int seatCnt(int i)
{
	int ret = 0;
	for(; i > 0; i -= lowbit[i])
		ret += C[i];
	return ret;
}

// 二分找这样的首个i，前i个座位有不小于k个空座位
int seatSeek(int k)
{
	int left = 1, right = N;
	while(left <= right) {
		int mid = (left + right) >> 1;
		if(seatCnt(mid) > k) right = mid - 1;
		else left = mid + 1;
	}
	return left;
}

int main()
{
	for(int i = 1; i <= MAX_N; ++i)
		lowbit[i] = i & (-i);

	while(scanf("%d", &N) != EOF) {
		for(int i = 1; i <= N; ++i) {
			scanf("%d%d", &nths[i], &vals[i]);
			C[i] = i - (i - lowbit[i]);
		}
		for(int i = N; i >= 1; --i) {
			int no = seatSeek(nths[i]);
			ans[no] = vals[i];
			takeSeat(no);
		}
		printf("%d", ans[1]);
		for(int i = 2; i <= N; ++i)
			printf(" %d", ans[i]);
		putchar('\n');
	}
	return 0;
}
