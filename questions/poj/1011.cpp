// POJ No.1011 Sticks (DFS+剪枝) (688K 32MS)
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAX_N = 64;

int N, len;
int sticks[MAX_N+5];
bool used[MAX_N+5], flag;

void dfs(int dep, int curlen, int pos)
{
	if(flag) return;
	if(curlen == len) {
		if(dep == N) flag = true;
		else dfs(dep, 0, 0);
		return;
	}
	if(curlen == 0) {
		int k = 0;
		while(used[k]) ++k;
		used[k] = 1;
		dfs(dep+1, sticks[k], k+1);
		used[k] = 0;
		return;
	}
	for(int i = pos; i < N; ++i)
		if(!used[i] && curlen + sticks[i] <= len) {
			if(!used[i-1] && sticks[i] == sticks[i-1]) continue;
			used[i] = 1;
			dfs(dep+1, curlen + sticks[i], i+1);
			used[i] = 0;
		}
}

int main()
{
	while(cin >> N && N != 0) {
		int sum = 0;
		flag = false;
		for(int i = 0; i < N; ++i) {
			cin >> sticks[i];
			sum += sticks[i];
		}
		sort(sticks, sticks+N, greater<int>());
		for(len = sticks[0]; len <= sum / 2; ++len)
			if(sum % len == 0) {
				memset(used, 0, sizeof(used));
				dfs(0, 0, 0);
				if(flag) break;
			}
		cout << (flag ? len : sum) << endl;
	}
	return 0;
}
