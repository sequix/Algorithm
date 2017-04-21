// POJ No.1270 Following Orders (用dfs按字典序生成所有的拓扑序) (520K 0MS)
#include <vector>
#include <cstdio>
#include <cstring>
using namespace std;

struct Letter {
	int ind;
	bool exist;
	vector<int> bigger;
} let[26];

int total;
char buf[1000];

int getline(char *s)
{
	int c, cnt = 0;
	while((c = getchar()) != EOF && c != '\n')
		s[cnt++] = c;
	s[cnt] = '\n';
	return cnt;
}

void dfs(int dep)
{
	if(dep == total) {
		buf[dep] = '\0';
		puts(buf);
		return;
	}

	for(int i = 0; i < 26; ++i) {
		if(let[i].exist && let[i].ind == 0) {
			--let[i].ind;	// 这样可以起到标记已用过字母的作用
			for(int j = 0; j < let[i].bigger.size(); ++j)
				--let[let[i].bigger[j]].ind;
			buf[dep] = 'a' + i;
			dfs(dep+1);
			for(int j = 0; j < let[i].bigger.size(); ++j)
				++let[let[i].bigger[j]].ind;
			++let[i].ind;
		}
	}
}

int main()
{
	int len;

	while((len = getline(buf)) != 0) {
		total = 0;
		memset(let, 0, sizeof(let));
		for(int i = 0; i < len; i += 2)
			if(!let[buf[i]-'a'].exist)
				++total, let[buf[i]-'a'].exist = true;

		len = getline(buf);
		for(int i = 0; i < len; i += 4) {
			int u = buf[i] - 'a', v = buf[i+2] - 'a';
			let[u].bigger.push_back(v);
			++let[v].ind;
		}
		dfs(0);
		putchar('\n');
	}
	return 0;
}
