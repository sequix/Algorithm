// POJ No.1300 Door Man (无向欧拉路存在判定) (360K 0MS)
#include <cstdio>
#include <cstring>
using namespace std;

int main()
{
	int S, V, deg[25];
	char buf[128], buf2[128];

	while(fgets(buf, sizeof(buf), stdin) != NULL) {
		if(buf[0] == 'E') break;

		int doors = 0;
		memset(deg, 0, sizeof(deg));
		sscanf(buf, "%s%d%d", buf2, &S, &V);
		for(int u = 0; u < V; ++u) {
			fgets(buf, sizeof(buf), stdin);
			int v, k = 0;
			while(sscanf(buf+k, "%d", &v) == 1) {
				++deg[u], ++deg[v], ++doors;
				while(buf[k] != '\0' && buf[k] != ' ') ++k;
				while(buf[k] != '\0' && buf[k] == ' ') ++k;
			}
		}

		int oddcnt = 0, od1 = -1, od2 = -1;
		for(int i = 0; i < V; ++i) {
			if(deg[i] % 2 == 1) {
				if(++oddcnt > 2) break;
				if(od1 == -1) od1 = i;
				else if(od2 == -1) od2 = i;
			}
		}

		if(oddcnt != 0 && oddcnt != 2)
			puts("NO");
		else {
			if(oddcnt == 0) {
				if(S == 0)
					printf("YES %d\n", doors);
				else
					puts("NO");
			} else {
				if((S==od1 && od2==0) || (S==od2 && od1==0))
					printf("YES %d\n", doors);
				else
					puts("NO");
			}
		}
		fgets(buf, sizeof(buf), stdin);
	}
}
