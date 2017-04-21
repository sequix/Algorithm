// POJ No.2570 Fiber Network (floyd) (808K 500MS)
#if 0
一些公司决定搭建一个更快的网络，称为“光纤网”。他们已经在全世界建立了许多站点，这 些站点的作用类似于路由器。不幸的是，这些公司在关于站点之间的接线问题上存在争论，这样“光纤网”项目就被迫终止了，留下的是每个公司自己在某些站点之间铺设的线路。 现在，Internet 服务供应商，当想从站点 A传送数据到站点 B，就感到困惑了，到底哪个公司 能够提供必要的连接。请帮助供应商回答他们的查询，查询所有可以提供从站点 A到站定 B的线 路连接的公司。

输入描述：

输入文件包含多个测试数据。每个测试数据第 1行为一个整数 n，代表网络中站点的个数，n = 0 代表输入结束，否则 n的范围为：1≤n≤200。站点的编号为 1, …, n。接下来列出了这些站 点之间的连接。每对连接占一行，首先是两个整数 A和B，A = B = 0 代表连接列表结束，否则 A、 B的范围为：1≤A, B≤n，表示站点 A和站点 B之间的单向连接；每行后面列出了拥有站点 A到 B之间连接的公司，公司用小写字母标识，多个公司的集合为包含小写字母的字符串。 连接列表之后，是供应商查询的列表。每个查询包含两个整数 A和B，A = B = 0 代表查询列 表结束，也代表整个测试数据结束，否则 A、B 的范围为：1≤A, B≤n，代表查询的起始和终止 站点。假定任何一对连接和查询的两个站点都不相同。

输出描述：

对测试数据中的每个查询，输出一行，为满足以下条件的所有公司的标识：这些公司可以通 过自己的线路为供应商提供从查询的起始站点到终止站点的数据通路。如果没有满足条件的公司， 则仅输出字符"-"。每个测试数据的输出之后输出一个空行。 
#endif // comment

#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int MAX_V = 200;

int main()
{
	char buf[64];
	int u, v, w, V, G[MAX_V+5][MAX_V+5];

	while(cin >> V && V != 0) {
		memset(G, 0, sizeof(G));

		while(cin >> u >> v && u+v) {
			cin >> buf;
			--u, --v, w = 0;
			for(int i = 0; buf[i] != '\0'; ++i)
				w |= (1 << (buf[i]-'a'));
			G[u][v] = w;
		}

		for(int k = 0; k < V; ++k)
			for(int i = 0; i < V; ++i)
				for(int j = 0; j < V; ++j)
					G[i][j] |= G[i][k] & G[k][j];

		while(cin >> u >> v && u+v) {
			--u, --v;
			bool printed = false;
			for(int i = 0; i < 26; ++i) {
				if(G[u][v] & (1 << i)) {
					putchar('a' + i);
					printed = true;
				}
			}
			if(!printed) putchar('-');
			putchar('\n');
		}
		putchar('\n');
	}
}
