#include <iostream>
#include <algorithm>
using namespace std;
const int MAX_N = 1000;

int N, A[MAX_N+5], B[MAX_N+5];

int main()
{
	int len = 0;

	cin >> N;
	for(int i = 1; i <= N; ++i)
		cin >> A[i];
	for(int i = 1; i <= N; ++i) {
		int next = lower_bound(B, B+len, A[i])-B;
		if(next+1 > len) len = next+1;
		B[next] = A[i];
	}
	cout << len << endl;
	return 0;
}
