// POJ No.1465 Multiple (BFS + 同余判重) (460K 47MS)
#include <cstdio>
#include <algorithm>
using namespace std;
const int MAX_N = 5000;

struct P {
	int d, r, pre;
	P(int d=0, int r=0, int p=-1): d(d), r(r), pre(p) {}
} que[MAX_N*2];

int N, M, A[10];
int qhead, qtail;

// 用递归倒序输出可免除开数组的麻烦
void output(int p)
{
	if(p == -1) return;
	output(que[p].pre);
	putchar('0' + que[p].d);
}

void solve()
{
	sort(A, A+M);
	qhead = qtail = 0;
	bool used[MAX_N+5] = {0};

	for(int i = 0; i < M; ++i) {
		if(A[i] == 0) continue;
		que[qtail++] = P(A[i], A[i] % N);
		used[A[i] % N] = true;
	}

	int anshead = -1;
	while(qhead != qtail) {
		P &p = que[qhead++];
		if(p.r == 0) { anshead = qhead-1; break; }
		for(int i = 0; i < M; ++i) {
			int r = (10 * p.r + A[i]) % N;
			if(used[r]) continue;
			que[qtail++] = P(A[i], r, qhead-1);
			used[r] = true;
		}
	}

	if(anshead == -1) {
		puts("0");
	} else {
		output(anshead);
		putchar('\n');
	}
}

int main()
{
	while(scanf("%d%d", &N, &M) != EOF) {
		for(int i = 0; i < M; ++i)
			scanf("%d", &A[i]);
		if(N == 0) { puts("0"); continue; }
		solve();
	}
}
