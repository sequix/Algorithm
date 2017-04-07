#include <iostream>
using namespace std;
const int MAX_N = 1000;

int A[MAX_N+5], dp[MAX_N+5];

int main()
{
	int n, ans = 1;

	cin >> n;
	for(int i = 1; i <= n; ++i) {
		cin >> A[i];
		dp[i] = 1;
	}
	for(int i = 2; i <= n; ++i) {
		for(int j = 1; j < i; ++j) {
			if(A[j] < A[i]) {
				dp[i] = max(dp[i], dp[j]+1);
				ans = max(ans, dp[i]);
			}
		}
	}
	cout << ans << endl;
	return 0;
}
