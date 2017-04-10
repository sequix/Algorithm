// POJ No.1631 Bridging Signals
#include <stdio.h>
#include <algorithm>
using namespace std;
const int MAX_N = 40000;
int A[MAX_N+5], B[MAX_N+5];

int main(void)
{
	int n, nn;

	for(scanf("%d", &n); n > 0; --n) {
		scanf("%d", &nn);
		for(int i = 0; i < nn; ++i)
			scanf("%d", &A[i]);
		
		B[0] = A[0];
		int len = 1;
		for(int i = 1; i < nn; ++i) {
			int next = lower_bound(B, B+len, A[i])-B;
			B[next] = A[i];
			if(next+1 > len) len = next+1;
		}
		printf("%d\n", len);
	}
	return 0;
}
