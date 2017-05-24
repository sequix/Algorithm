// POJ No.3321 Apple Tree (树状数组) (12120K 1297MS)
#include <vector>
#include <cstdio>
using namespace std;
const int MAX_N = 220000;
typedef vector<int> VCT_INT;

bool hasApple[MAX_N/2];
vector<VCT_INT> G(MAX_N/2);
int start[MAX_N], end[MAX_N];
int C[MAX_N], lowbit[MAX_N], nCount = 0;

// 用dfs给每个叉编号
void dfs(int v)
{
	start[v] = ++nCount;
	for(int i = 0; i < G[v].size(); ++i)
		dfs(G[v][i]);
	end[v] = ++nCount;
}

int querySum(int p)
{
	int sum = 0;
	for(; p > 0; p -= lowbit[p])
		sum += C[p];
	return sum;
}

void modify(int p, int val)
{
	for(; p <= nCount; p += lowbit[p])
		C[p] += val;
}

int main()
{
	char cmd[10];
	int n, m, a, b;

	scanf("%d", &n);
	for(int i = 0; i < n-1; ++i ) {
		scanf("%d%d", &a, &b);
		G[a].push_back(b);
	}
	dfs(1);
	for(int i = 1; i <= nCount; ++i)
		lowbit[i] = i & (-i);
	for(int i = 1; i <= n; ++i)
		hasApple[i] = 1;

	for(int i = 1; i <= nCount; ++i)
		C[i] = i - (i - lowbit[i]);
		// C[i] = sum[i] - sum[i-lowbit[i]];

	scanf("%d", &m);
	for(int i = 0; i < m; ++i) {
		scanf("%s%d", cmd, &a);
		if(cmd[0] == 'C') {
			if(hasApple[a]) {
				modify(start[a], -1);
				modify(end[a], -1);
				hasApple[a] = 0;
			} else {
				modify(start[a], 1);
				modify(end[a], 1);
				hasApple[a] = 1;
			}
		} else {
			int t1 = querySum(end[a]);
			int t2 = querySum(start[a]-1);
			printf("%d\n", (t1-t2)/2);
		}
	}
	return 0;
}

