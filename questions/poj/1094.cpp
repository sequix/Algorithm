// POJ No.1094 Sorting It All Out (topo排序) (148K 16MS)
#include <vector>
#include <cstdio>
#include <cstring>
using namespace std;
typedef vector<int> VCT_INT;

char seq[26];
bool alpha[26];
vector<VCT_INT> G(26);
int V, E, alpha_cnt, ind[26], ind_bak[26];

int toposort(int n)
{
	int seqcnt = 0;
	bool flag = true;	// 能否得到拓扑序
	memcpy(ind_bak, ind, sizeof(ind));

	while(n--) {
		int cnt = 0, j = -1;
		for(int i = 0; i < V; ++i)
			if(ind_bak[i] == 0) ++cnt, j = i;

		// 注意这里的if必须写成这种形式
		// 因为在拓扑序不唯一时，还要判断是否有环
		if(cnt >= 1) {
			if(cnt > 1) flag = 0;
			for(int i = 0; i < G[j].size(); ++i)
				--ind_bak[G[j][i]];
			seq[seqcnt++] = 'A' + j;
			seq[seqcnt] = '\0';
			ind_bak[j] = -1;
		} else if(cnt == 0)
			return -1;
	}
	return flag ? seqcnt : 0;
}

int main()
{
	char buf[64];

	while(scanf("%d%d", &V, &E) != EOF) {
		if(V == 0 && E == 0) break;
		alpha_cnt = 0;
		int determined = 0, k = -1;
		memset(ind, 0, sizeof(ind));
		memset(alpha, false, sizeof(alpha));
		for(int i = 0; i < V; ++i) G[i].clear();

		for(int i = 1; i <= E; ++i) {
			scanf("%s", buf);
			int u = buf[0]-'A', v = buf[2]-'A';
			if(!alpha[u]) ++alpha_cnt, alpha[u] = true;
			if(!alpha[v]) ++alpha_cnt, alpha[v] = true;
			++ind[v]; G[u].push_back(v);

			if(determined == 0) {
				int tmp = toposort(alpha_cnt);
				if(tmp == -1) determined = -1, k = i;
				else if(tmp == V) determined = 1, k = i;
			}
		}

		if(determined == -1)
			printf("Inconsistency found after %d relations.\n", k);
		else if(determined == 0)
			puts("Sorted sequence cannot be determined.");
		else
			printf("Sorted sequence determined after %d relations: %s.\n", k, seq);
	}
	return 0;
}
