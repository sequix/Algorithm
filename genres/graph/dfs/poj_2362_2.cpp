// POJ No.2362 Square (DFS+剪枝) (676K 110MS)
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

bool used[25], quit, flag;
int M, len, sticks[25];

// 正在拼nth条边，已拼长度为curlen
void dfs(int curlen, int nth, int pos)
{
	if(quit) return;
	if(nth == 4) { quit = flag = true; return; }
// 注意dfs(0, nth+1, pos)错误，因为在拼下一条边之前可能有较小的棍还没有用到
	if(curlen == len) dfs(0, nth+1, 0);

// 因为所有的棍是有序的，所以当在拼同一条边时，之前无法选的棍现在也选不了
// 所以i从pos开始，每次调用又将i+1（因为本次把sticks[i]用掉了）
	for(int i = pos; i < M; ++i) {
		if(used[i]) continue;
		if(curlen + sticks[i] > len) continue;
		used[i] = true;
		dfs(curlen + sticks[i], nth, i+1);
		used[i] = false;
	}
}

int main()
{
	int N;

	for(cin >> N; N > 0; --N) {
		cin >> M;
		int sum = 0, maxstick = 0;
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
// 从大到小排序：每条边的拼凑到最后都需要补一个较小的棍，
// 而较小的棍在数组后面，也就是加深了dfs的深度，所以会慢
			//sort(sticks, sticks+M, greater<int>());
// 从小到大排序：首条边用较多条较小的棍加较少条较多的棍构成，
// 而剩下的每条边也会先看较小的棍，后看较大的棍，
// 所以每条边的拼凑都是很均匀的，减少了无谓的dfs调用，所以会比前面快一些
			sort(sticks, sticks+M);
			memset(used, false, sizeof(used));
			dfs(0, 0, 0);
			cout << (flag ? "yes" : "no") << endl;
		}
	}
	return 0;
}
