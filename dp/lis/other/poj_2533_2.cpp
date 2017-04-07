// POJ No.2533 Longest Ordered Subsequence
#include <iostream>
#include <algorithm>
using namespace std;
const int MAXN = 10000;
int A[MAXN+5], B[MAXN+5];

int main(void)
{
	int N, len = 1;

	cin >> N;
	for(int i = 0; i < N; ++i)
		cin >> A[i];
	
	B[0] = A[0];
	for(int i = 1; i < N; ++i) {
		int next = lower_bound(B, B+len, A[i])-B;
		B[next] = A[i];
		if(next+1 > len) len = next+1;
	}
	cout << len << endl;
	return 0;
}
