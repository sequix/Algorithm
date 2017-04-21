// POJ No.1128 Frame Stacking (toposort) (344K 0MS)
#include <cstdio>
#include <vector>
#include <cstring>
using namespace std;
const int INF = 0x3f3f3f3f;

int ind[26];
int R, C, K;			// K代表出现的字母数
int ltr[26], ltc[26];	// 各左上角的r、c坐标
int rbr[26], rbc[26];	// 各右下角的r、c坐标
char M[26][26], buf[30];
bool exist[26], G[26][26];

void dfs(int dep)
{
	if(dep == K) {
		buf[dep] = '\0';
		puts(buf);
		return;
	}

	for(int i = 0; i < 26; ++i) {
		if(!exist[i] || ind[i] != 0) continue;
		--ind[i];
		for(int j = 0; j < 26; ++j)
			if(G[i][j]) --ind[j];
		buf[dep] = i + 'A';
		dfs(dep + 1);
		++ind[i];
		for(int j = 0; j < 26; ++j)
			if(G[i][j]) ++ind[j];
	}
}

int main()
{
	while(scanf("%d%d", &R, &C) != EOF) {
		K = 0;
		getchar();
		memset(exist, false, sizeof(exist));
		for(int i = 0; i < R; ++i) {
			for(int j = 0; j < C; ++j) {
				M[i][j] = getchar();
				if(M[i][j] != '.' && !exist[M[i][j]-'A'])
					++K, exist[M[i][j]-'A'] = true;
			}
			getchar();
		}
		// 确定各字母左上、右下角坐标
		// 每个边框的左上右下下标由所出现字母的坐标的最值确定
		memset(ltr, INF, sizeof(ltr));
		memset(ltc, INF, sizeof(ltc));
		memset(rbr, 0, sizeof(rbr));
		memset(rbc, 0, sizeof(rbc));
		for(int i = 0; i < R; ++i) {
			for(int j = 0; j < C; ++j) {
				if(M[i][j] == '.') continue;
				int k = M[i][j] - 'A';
				if(i < ltr[k]) ltr[k] = i;
				if(j < ltc[k]) ltc[k] = j;
				if(i > rbr[k]) rbr[k] = i;
				if(j > rbc[k]) rbc[k] = j;
			}
		}
		// 建图，统计入度
		memset(G, false, sizeof(G));
		memset(ind, 0, sizeof(ind));
		for(int i = 0; i < 26; ++i) {
			if(!exist[i]) continue;
			for(int r = ltr[i]; r <= rbr[i]; ++r) {
				for(int c = ltc[i]; c <= rbc[i]; ++c) {
					// 跳过边框中间的空隙
					if(r>ltr[i] && c>ltc[i] && r<rbr[i] && c<rbc[i])
						continue;
					int k = M[r][c] - 'A';
					if(k != i && !G[i][k])
						G[i][k] = true, ++ind[k];
				}
			}
		}
		// dfs按字典序求toposeq
		dfs(0);
	}
}
