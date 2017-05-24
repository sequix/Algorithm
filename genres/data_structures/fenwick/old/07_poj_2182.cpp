// POJ No.2182 Lost Cows (树状数组) (480K 110MS)
// 原数组由1, 2, ... , N构成
// 给第i个元素前比其小的元素的个数，求原数组
#include <cstdio>
using namespace std;
const int MAX_N = 8000;

int A[MAX_N+5], ans[MAX_N+5];
// bit维护前i个编号中还有几个没用
int N, bit[MAX_N+5], lowbit[MAX_N+5];

void take(int i)
{
	for(; i <= N; i += lowbit[i])
		--bit[i];
}

int query(int i)
{
	int ret = 0;
	for(; i > 0; i -= lowbit[i])
		ret += bit[i];
	return ret;
}

// 二分找有n个空编号的前x个编号，返回x
int seek(int n)
{
	int left = 1, right = N;
	while(left <= right) {
		int mid = (left + right) >> 1;
		if(query(mid) >= n) right = mid - 1;
		else left = mid + 1;
	}
	return left;
}

int main()
{
	for(int i = 1; i <= MAX_N; ++i)
		lowbit[i] = i & (-i);
	scanf("%d", &N);
	bit[1] = 1;
	for(int i = 2; i <= N; ++i) {
		scanf("%d", &A[i]);
		bit[i] = i - (i - lowbit[i]);
	}
	for(int i = N; i >= 1; --i) {
		int next = seek(A[i] + 1);
		ans[i] = next;
		take(next);
	}
	for(int i = 1; i <= N; ++i)
		printf("%d\n", ans[i]);
	return 0;
}
