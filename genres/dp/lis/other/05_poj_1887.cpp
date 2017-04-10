// POJ No.1887 Testing the CATCHER (O(NlgN)的最长下降子序列)
#include <cstdio>
#include <iostream>
using namespace std;
const int MAX_N = 1000;

int A[MAX_N+5];

int search(int left, int right, int key)
{
	while(left <= right) {
		int mid = (left + right) >> 1;
		if(key <= A[mid]) left = mid + 1;
		else right = right - 1;
	}
	return left;
}

int main()
{
	int t, kase = 1;

	while(cin >> t && t != -1) {
		A[1] = t;
		int len = 1;
		while(cin >> t && t != -1) {
			if(t < A[len]) {
				A[++len] = t;
			} else {
				int next = search(1, len, t);
				A[next] = t;
			}
		}
		if(kase >= 2) putchar('\n');
		printf("Test #%d:\n", kase++);
		printf("  maximum possible interceptions: %d\n", len);
	}
	return 0;
}
