// POJ No.1659 Frog's Neighborhood (合法度序列判断+构图) (692K 0MS)
// 应用Havel-Hakimi定理
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

bool G[12][12];
struct Node {
	int degree, no;
	bool operator > (const Node &n) const { return degree > n.degree; }
} A[12];

int main()
{
	int N, T;

	for(cin >> T; T > 0; --T) {
		cin >> N;
		for(int i = 0; i < N; ++i) {
			cin >> A[i].degree;
			A[i].no = i;
		}
		bool islegal = true;
		memset(G, 0, sizeof(G));
		for(int k = 0; k < N && islegal; ++k) {
			sort(A+k, A+N, greater<Node>());
			if(N-k-1 < A[k].degree) { islegal = false; break; }
			int u = A[k].no;
			for(int i = 1; i <= A[k].degree && islegal; ++i) {
				if(--A[k+i].degree < 0) { islegal = false; break; }
				int v = A[k+i].no;
				G[u][v] = G[v][u] = 1;
			}
		}
		if(islegal) {
			puts("YES");
			for(int i = 0; i < N; ++i) {
				for(int j = 0; j < N; ++j) {
					if(j > 0) putchar(' ');
					putchar(G[i][j] ? '1' : '0');
				}
				putchar('\n');
			}
		} else {
			puts("NO");
		}
		if(T > 1) putchar('\n');
	}
	return 0;
}
