// 最长严格下降子序列
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
const int MAX_N = 10000;

int N, A[MAX_N+5], B[MAX_N+5];

int search(int left, int right, int key)
{
	while(left <= right) {
		int mid = (left + right) >> 1;
		if(key < B[mid]) left = mid + 1;
		else right = mid - 1;
	}
	return left;
}

int main()
{
	int len = 0;
	cin >> N;
	for(int i = 0; i < N; ++i)
		cin >> A[i];
	for(int i = 0; i < N; ++i) {
		int next = search(0, len, A[i]);
		if(next+1 > len) len = next + 1;
		B[next] = A[i];
	}
	cout << len << endl;
	return 0;
}
