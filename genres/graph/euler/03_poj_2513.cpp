// POJ No.2513 Colored Sticks (欧拉路判定+并查集+trie) (59268K 422MS)
// 用trie来做hash
#include <cstdio>
using namespace std;

class UnionFind {
private:
	int par[500005];
public:
	UnionFind(int n=500004) {
		for(int i = 0; i <= n; ++i)
			par[i] = i;
	}
	int getpar(int x) {
		if(par[x] != x)
			par[x] = getpar(par[x]);
		return par[x];
	}
	void merge(int x, int y) {
		par[getpar(x)] = getpar(y);
	}
	bool query(int x, int y) {
		return getpar(x) == getpar(y);
	}
};

struct Node { int id; Node *next[26]; };

UnionFind uf;
int cnt, deg[500005];
char buf1[16], buf2[16];
Node trie[1000000], *palloc = trie+1;

int str2id(char *s)
{
	Node *p = trie;
	for(; *s != '\0'; ++s) {
		int k = *s - 'a';
		if(p->next[k] == NULL)
			p->next[k] = palloc++;
		p = p->next[k];
	}
	if(p->id == 0) p->id = ++cnt;
	return p->id;
}

int main()
{
	while(scanf("%s%s", buf1, buf2) != EOF) {
		int u = str2id(buf1), v = str2id(buf2);
		uf.merge(u, v);
		++deg[u], ++deg[v];
	}

	bool connected = true;
	int oddcnt = 0, first_par = -1;
	for(int i = 1; i <= cnt; ++i) {
		if(first_par == -1) {
			first_par = uf.getpar(i);
		} else {
			if(uf.getpar(i) != first_par) {
				connected = false;
				break;
			}
		}
		if(deg[i] % 2 == 1 && ++oddcnt > 2)
			break;
	}

	if(!connected)
		puts("Impossible");
	else {
		if(oddcnt == 0 || oddcnt == 2)
			puts("Possible");
		else
			puts("Impossible");
	}
	return 0;
}
