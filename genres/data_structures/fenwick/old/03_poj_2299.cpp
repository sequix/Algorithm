// POJ No.2299 Ultra-QuickSort (离散化+树状数组算逆序数) (7828K 1047MS)
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAX_N = 500000;
typedef long long LL;

int N, A[MAX_N+5];
// C累加抽象数组B，B[i]表示第i个位置上有多少个元素i
int lowbit[MAX_N+5], C[MAX_N+5];
int hashsize, hashtab[MAX_N+5];

// 将x映射为其在hashtab中的下标值加1
int hash(int x)
{
	return lower_bound(hashtab, hashtab+hashsize, x) - hashtab + 1;
}

void update(int i)
{
	for(; i <= N; i += lowbit[i])
		++C[i];
}

LL getsum(int i)
{
	LL sum = 0;
	for(; i > 0; i -= lowbit[i])
		sum += C[i];
	return sum;
}

int main()
{
	for(int i = 1; i <= MAX_N; ++i)
		lowbit[i] = i & (-i);

	while(~scanf("%d", &N) && N) {
		for(int i = 1; i <= N; ++i) {
			scanf("%d", &A[i]);
			hashtab[i-1] = A[i];
		}
		// 将大范围数映射到小范围的[1,N]，实现离散化
		sort(hashtab, hashtab+N);
		hashsize = unique(hashtab, hashtab+N) - hashtab;

		LL ans = 0;
		// 每插入一个数，统计比他小的数的个数
		for(int i = 1; i <= N; ++i) {
			update(hash(A[i]));
			// i为已插入数的个数，getsum(hash[i])为不大于hash[i]的数的个数
			// i-getsum(hash[i])为大于hash[i]的数的个数
			// 又因为该循环是正序插入元素，所以每次的i-getsum(hash[i])
			// 就是hash[i]"前"大于hash[i]的元素的个数
			ans += i - getsum(hash(A[i]));
		}
		printf("%lld\n", ans);
		memset(C, 0, sizeof(C));
	}
	return 0;
}
