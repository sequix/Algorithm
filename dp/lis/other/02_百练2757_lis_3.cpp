#include <iostream>
#include <algorithm>
using namespace std;
const int MAX_N = 1000;

int N, A[MAX_N+5], dp[MAX_N+5];

int main()
{
	cin >> N;
	for(int i = 1; i <= N; ++i) {
		cin >> A[i];
		dp[i] = 1;
	}
	for(int i = 1; i <= N; ++i)
		for(int j = i + 1; j <= N; ++j)
			if(A[j] > A[i])
				dp[j] = max(dp[j], dp[i]+1);
	cout << *max_element(dp+1, dp+1+N) << endl;
	return 0;
}
