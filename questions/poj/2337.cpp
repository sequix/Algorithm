// POJ No.2337 Catenyms (有向欧拉通路) (POJ这题有错误)
#include <cctype>
#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int L = 26;		// L for letters
#define abs(x) ((x) < 0 ? -(x) : (x))

class UnionFind {
private:
	int par[L];
public:
	UnionFind() {
		for(int i = 0; i < L; ++i)
			par[i] = i;
	}
	int getpar(int x) {
		if(par[x] != x)
			par[x] = getpar(par[x]);
		return par[x];
	}
	int merge(int x, int y) {
		par[getpar(x)] = getpar(y);
	}
	bool equal(int x, int y) {
		return getpar(x) == getpar(y);
	}
};

struct Edge {
	int to; char *str; bool used;
	Edge(int t=0, char *s=NULL): to(t), str(s), used(false) {}
};

struct Word {
	int len; char s[21];
	bool operator < (const Word &w) const { return strcmp(s, w.s) <= 0; }
} words[1001];

int E, anscnt;
bool exist[L];
vector<Edge> G[L];
int ind[L], otd[L];
char *ans[1001];

int getword(char *s)
{
	int c, cnt = 0;
	while(isspace(c = getchar()));
	s[cnt++] = c;
	while((c = getchar()) != EOF && !isspace(c))
		s[cnt++] = c;
	s[cnt] = '\0';
	return cnt;
}

bool cmp(const char *&s1, const char *&s2)
{
	return strcmp(s1, s2) <= 0;
}

void dfs(int from)
{
	for(int i = 0; i < G[from].size(); ++i) {
		if(G[from][i].used) continue;
		G[from][i].used = true;
		ans[anscnt++] = G[from][i].str;
		dfs(G[from][i].to);
	}
}

int main()
{
	int T;

	for(scanf("%d", &T); T > 0; --T) {
		anscnt = 0;
		UnionFind uf;
		memset(ind, 0, sizeof(ind));
		memset(otd, 0, sizeof(otd));
		memset(exist, 0, sizeof(exist));
		for(int i = 0; i < L; ++i) G[i].clear();

		// 先对输入排序，再插入邻接表中，保证生成最小字典序
		scanf("%d", &E);
		for(int i = 0; i < E; ++i)
			words[i].len = getword(words[i].s);
		sort(words, words+E);
		for(int i = 0; i < E; ++i) {
			int len = words[i].len;
			int from = words[i].s[0] - 'a';
			int to = words[i].s[len-1] - 'a';
			uf.merge(from, to);
			++otd[from], ++ind[to];
			exist[from] = exist[to] = true;
			G[from].push_back(Edge(to, words[i].s));
		}
		// 判联通
		int first_par = -1;
		bool connected = true;
		for(int i = 0; i < L; ++i) {
			if(!exist[i]) continue;
			if(first_par == -1)
				first_par = uf.getpar(i);
			else if(uf.getpar(i) != first_par) {
				connected = false;
				break;
			}
		}
		if(!connected) { puts("***"); continue; }
		// 判是否可欧拉
		bool eulerable = true;
		int start = 0, p1 = 0, n1 = 0;
		for(int i = 0; i < L; ++i) {
			if(!exist[i]) continue;
			if(abs(otd[i] - ind[i]) >= 2) { eulerable = false; break; }
			if(otd[i] - ind[i] == 1) {
				start = i;
				if(++p1 > 1) { eulerable = false; break; }
			}
			if(otd[i] - ind[i] == -1)
				if(++n1 > 1) { eulerable = false; break; }
		}
		if(!eulerable || p1 != n1) { puts("***"); continue; }
		// 存在欧拉回路时，要保证开始能选到最小字典序的边
		if(p1 == 0 && n1 == 0) {
			for(int i = 0; i < L; ++i)
				for(int j = 0; j < G[i].size(); ++j)
					if(G[i][j].str == words[0].s) { start = i; break; }
		}
		// 求解欧拉通路
		dfs(start);
		printf("%s", ans[0]);
		for(int i = 1; i < anscnt; ++i)
			printf(".%s", ans[i]);
		putchar('\n');
	}
	return 0;
}
