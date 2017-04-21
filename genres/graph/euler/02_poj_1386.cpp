// POJ No.1386 Pla on Words (有向欧拉路判定) (344K 94MS)
#include <cstdio>
#include <cctype>
#include <cstring>
using namespace std;

class UnionFind {
private:
	int par[26];
public:
	UnionFind(int n=26) {
		for(int i = 0; i < n; ++i)
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
	int equal(int x, int y) {
		return getpar(x) == getpar(y);
	}
};

int E;
bool exist[26];
int ind[26], otd[26];

int getline(char *s)
{
	int c, cnt = 0;
	while(isspace(c = getchar())) ;
	s[cnt++] = c;	
	while((c = getchar()) != EOF && c != '\n')
		s[cnt++] = c;
	s[cnt] = '\0';
	return cnt;
}

int main()
{
	int T;
	char buf[1024];

	for(scanf("%d", &T); T > 0; --T) {
		UnionFind uf;
		scanf("%d", &E);
		memset(ind, 0, sizeof(ind));
		memset(otd, 0, sizeof(otd));
		memset(exist, false, sizeof(exist));
		for(int i = 0; i < E; ++i) {
			int len = getline(buf);
			int u = buf[0]-'a', v = buf[len-1]-'a';
			uf.merge(u, v);
			++ind[v], ++otd[u];
			exist[u] = exist[v] = true;
		}
		// 判断基图是否联通
		int first_par = -1;
		bool isconnected = true;
		for(int i = 0; i < 26; ++i) {
			if(!exist[i]) continue;
			if(first_par == -1) {
				first_par = uf.getpar(i);
				continue;
			} else {
				if(uf.getpar(i) != first_par) {
					isconnected = false;
					break;
				}
			}
		}
		if(!isconnected) {
			puts("The door cannot be opened.");
			continue;
		}
		// 判断是否有欧拉路
		int p1 = 0;			// otd[i]-ind[i] == 1 的点数
		int n1 = 0;			// otd[i]-ind[i] == -1 的点数
		bool iseuler = true;
		for(int i = 0; i < 26; ++i) {
			if(!exist[i]) continue;
			if(ind[i]-otd[i] >= 2 || otd[i]-ind[i] >= 2) {
				iseuler = false;
				break;
			}
			if(otd[i]-ind[i] == 1 && ++p1 > 1) {
				iseuler = false;
				break;
			}
			if(otd[i]-ind[i] == -1 && ++n1 > 1) {
				iseuler = false;
				break;
			}
		}
		if(p1 != n1) iseuler = false;
		if(iseuler)
			puts("Ordering is possible.");
		else
			puts("The door cannot be opened.");
	}
}
