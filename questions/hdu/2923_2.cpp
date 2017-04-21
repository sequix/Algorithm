// HDU No.2923 (floyd+重边处理+题意理解) (280MS 1696K)
#include <map>
#include <cstdio>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;
const int MAX_V = 100;
const int MAX_C = 1000;
const int INF = 0x3f3f3f3f;

int C, es[MAX_C+5];
int V, E, d[MAX_V+5][MAX_V+5];

void floyd()
{
	for(int k = 1; k <= V; ++k)
		for(int i = 1; i <= V; ++i)
			if(d[i][k] != INF)
				for(int j = 1; j <= V; ++j)
					d[i][j] = min(d[i][j], d[i][k]+d[k][j]);
}


int main()
{
	int a, b, c, kase = 0;
	string str1, str2, str3, start;

	while(~scanf("%d%d%d", &V, &C, &E) && V+C+E) {
		int cnt = 0;
		map<string, int> tab;
		cin >> start;
		tab[start] = ++cnt;
		for(int i = 0; i < C; ++i) {
			cin >> str1;
			if(tab[str1] == 0) tab[str1] = ++cnt;
			es[i] = tab[str1];
		}

		for(int i = 1; i <= V; ++i)
			for(int j = 1; j <= V; ++j)
				d[i][j] = (i==j) ? 0 : INF;
		for(int i = 0; i < E; ++i) {
			cin >> str1 >> str2 >> str3;
			if(tab[str1] == 0) tab[str1] = ++cnt;
			if(tab[str3] == 0) tab[str3] = ++cnt;
			a = tab[str1], b = tab[str3];
			sscanf(str2.substr(2).c_str(), "%d", &c);
// 注意此处：混合图的重边处理
			if(str2.find("--") != string::npos) {
				if(str2.find("<-") == 0) {
					if(c < d[b][a]) d[b][a] = c;
				} else {
					if(c < d[a][b]) d[a][b] = c;
				}
			} else {
				if(c < d[a][b]) d[a][b] = c;
				if(c < d[b][a]) d[b][a] = c;
			}
		}

		floyd();
		int ans = 0;
		for(int i = 0; i < C; ++i)
			ans += d[1][es[i]] + d[es[i]][1];
		printf("%d. %d\n", ++kase, ans);
	}
	return 0;
}
