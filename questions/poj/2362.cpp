// POJ No.2362 Square (DFS+剪枝) (680K 141MS)
#include <cstring>
#include <iostream>
#include <algorithm>
#include <functional>
using namespace std;

bool used[25], quit, flag;
int M, len, sum, sticks[25];

// 正在拼nth条边，已拼长度为curlen
void dfs(int curlen, int nth, int pos)
{
	if(quit) return;
	if(nth == 4) { quit = flag = true; return; }
	if(curlen == len) dfs(0, nth+1, 0);

	for(int i = pos; i < M; ++i) {
		if(used[i]) continue;
		if(curlen + sum < len) { quit = true; return; }
		if(curlen + sticks[i] > len) continue;
		used[i] = true;
		sum -= sticks[i];
		dfs(curlen + sticks[i], nth, i+1);
		sum += sticks[i];
		used[i] = false;
	}
}

int main()
{
	int N;

	for(cin >> N; N > 0; --N) {
		cin >> M;
		sum = 0;
		int maxstick = 0;
		for(int i = 0; i < M; ++i) {
			cin >> sticks[i];
			sum += sticks[i];
			maxstick = max(maxstick, sticks[i]);
		}
		if(sum%4!=0 || maxstick>sum/4) {
			cout << "no" << endl;
		} else {
			len = sum / 4;
			quit = flag = false;
			sort(sticks, sticks+M);
			memset(used, false, sizeof(used));
			dfs(0, 0, 0);
			cout << (flag ? "yes" : "no") << endl;
		}
	}
	return 0;
}
