// POJ No.1631 Bridging Signals
#include <cstdio>
#include <iostream>
using namespace std;
const int MAX_N = 40000;
int A[MAX_N+5], B[MAX_N+5];

int binsearch(int left, int right, int key)
{
	if(B[right] < key)
		return right + 1;
	while(left < right) {
		int mid = (left + right) / 2;
		if(key >= B[mid])
			left = mid + 1;
		else
			right = mid;
	}
	return right;
}

int main(void)
{
	int n, nn;

	for(cin >> n; n > 0; --n) {
		cin >> nn;
		for(int i = 0; i < nn; ++i)
			scanf("%d", &A[i]);

		B[1] = A[0];
		int maxlen = 1;
		for(int i = 0; i < nn; ++i) {
			int next = binsearch(1, maxlen, A[i]);
			B[next] = A[i];
			if(next > maxlen) maxlen = next;
		}
		cout << maxlen << endl;
	}
	return 0;
}
