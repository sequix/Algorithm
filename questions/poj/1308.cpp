// POJ No.1308 Is It A Tree? (树的判定) (768K 0MS)
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int MAX_N = 10000;

class UnionFind {
private:
	int par[MAX_N];
public:
	UnionFind() {
		for(int i = 0; i < MAX_N; ++i)
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
	bool equal(int x, int y) {
		return getpar(x) == getpar(y);
	}
};

int ind[MAX_N];
bool exist[MAX_N];

int main()
{
	int from, to, kase = 1;

	while(true) {
		cin >> from >> to;
		if(from == -1 && to == -1) break;

		if(from == 0 && to == 0) {
			printf("Case %d is a tree.\n", kase++);
			continue;
		}

		UnionFind uf;
		memset(ind, 0, sizeof(ind));
		memset(exist, 0, sizeof(exist));

		++ind[to];
		uf.merge(from, to);
		exist[from] = exist[to] = true;
		while(cin >> from >> to) {
			if(from == 0 && to == 0) break;
			++ind[to];
			uf.merge(from, to);
			exist[from] = exist[to] = true;
		}

		int root = -1;
		bool istree = true;
		for(int i = 0; i < MAX_N; ++i) {
			if(!exist[i]) continue;
			if(ind[i] == 0) {
				if(root == -1) {
					root = i;
				} else {
					istree = false;
					break;
				}
			} else if(ind[i] > 1) {
				istree = false;
				break;
			}
		}

		for(int i = 0; i < MAX_N; ++i) {
			if(!exist[i]) continue;
			if(!uf.equal(root, i)) {
				istree = false;
				break;
			}
		}

		printf("Case %d is %sa tree.\n", kase++, istree ? "" : "not ");
	}
}
