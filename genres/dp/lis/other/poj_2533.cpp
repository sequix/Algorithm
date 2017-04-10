// POJ No.2533 Longest Ordered Subsequence
#include <iostream>
using namespace std;
const int MAX_N = 10000;
int A[MAX_N+5], dp[MAX_N+5];

int main(void)
{
	int n, ans = 1;

	cin >> n;
	for(int i = 0; i < n; ++i)
		cin >> A[i];

	for(int i = 0; i < n; ++i) {
		dp[i] = 1;
		for(int j = 0; j < i; ++j)
			if(A[j] < A[i] && dp[j]+1 > dp[i])
				dp[i] = dp[j]+1;
		if(dp[i] > ans)
			ans = dp[i];
	}
	cout << ans << endl;
	return 0;
}
