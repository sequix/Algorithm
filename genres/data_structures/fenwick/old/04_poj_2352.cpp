// POJ No.2352 Stars (树状数组) (692K 360MS)
#include <cstdio>
using namespace std;
const int MAX_N = 32001;

int level[MAX_N+5];
int N, A[MAX_N+5], lowbit[MAX_N+5];

void add(int i)
{
	for(; i <= MAX_N; i += lowbit[i])
		++A[i];
}

int getsum(int i)
{
	int sum = 0;
	for(; i > 0; i -= lowbit[i])
		sum += A[i];
	return sum;
}

int main()
{
	int x, y;

	for(int i = 1; i <= MAX_N; ++i)
		lowbit[i] = i & (-i);

	scanf("%d", &N);
	for(int i = 0; i < N; ++i) {
		scanf("%d%d", &x, &y);
		++level[getsum(x+1)];
		add(x+1);
	}
	for(int i = 0; i < N; ++i)
		printf("%d\n", level[i]);
	return 0;
}
