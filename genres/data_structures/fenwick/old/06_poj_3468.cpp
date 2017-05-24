// POJ No.3468 A Simple Problem with Integers (树状数组) (3484K 2047MS)
#include <cstdio>
using namespace std;
typedef long long LL;
const int MAX_N = 100000;

int N, Q;
LL sum[MAX_N+5];
LL bit0[MAX_N+5], bit1[MAX_N+5], lowbit[MAX_N+5];

void add(LL *bit, int i, LL inc)
{
	for(; i <= N; i += lowbit[i])
		bit[i] += inc;
}

void add_segment(int a, int b, LL inc)
{
	add(bit0, a, -inc*(a-1));
	add(bit0, b+1, inc*b);
	add(bit1, a, inc);
	add(bit1, b+1, -inc);
}

LL query(int i)
{
	LL res0 = 0, res1 = 0;
	for(int ii=i; ii > 0; ii -= lowbit[ii]) {
		res0 += bit0[ii];
		res1 += bit1[ii];
	}
	return res0 + res1 * i;
}

int main()
{
	char cmd[4];
	int a, b; LL tmp;

	for(int i = 1; i <= MAX_N; ++i)
		lowbit[i] = i & (-i);

	scanf("%d%d%lld", &N, &Q, &tmp);
	bit0[1] = sum[1] = tmp;
	for(int i = 2; i <= N; ++i) {
		scanf("%lld", &tmp);
		sum[i] = sum[i-1] + tmp;
		bit0[i] = sum[i] - sum[i-lowbit[i]];
	}

	for(int i = 0; i < Q; ++i) {
		scanf("%s", cmd);
		if(cmd[0] == 'C') {
			scanf("%d%d%lld", &a, &b, &tmp);
			add_segment(a, b, tmp);
		} else {
			scanf("%d%d", &a, &b);
			printf("%lld\n", query(b) - query(a-1));
		}
	}
}
