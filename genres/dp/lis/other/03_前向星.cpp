// 递推法+前向星求一个LIS (首个)
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int MAX_N = 10000;

int N, A[MAX_N+5], lis[MAX_N+5];
int pre[MAX_N+5], dp[MAX_N+5];

int main()
{
	int pmax = 0;

	cin >> N;
	for(int i = 0; i < N; ++i)
		cin >> A[i];
	dp[0] = 1;
	memset(pre, -1, sizeof(pre));
	for(int i = 1; i < N; ++i) {
		for(int j = 0; j < i; ++j) {
			if(A[j] < A[i] && dp[i] < dp[j]+1) {
				pre[i] = j;
				dp[i] = dp[j] + 1;
				if(dp[pmax] < dp[i]) pmax = i;
			}
		}
	}
	printf("%d:", dp[pmax]);
	for(int i=pmax, cnt=0; i != -1; i = pre[i])
		lis[cnt++] = A[i];
	for(int i = dp[pmax]-1; i >= 0; --i)
		printf(" %d", lis[i]);
	cout << endl;
	return 0;
}
