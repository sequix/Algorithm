// POJ No.1961 Period (KMP) (5248K 485MS)
// 求2到len长的s的前缀可由几个“最小循环节”构成
// 求法同poj2406
#include <cstdio>
#include <algorithm>
using namespace std;
const int MAX_N = 1000000;

char buf[MAX_N+5];
int len, knext[MAX_N+5];

void kmpinit()
{
	knext[0] = -1;
	int i = 0, j = -1;

	while(i < len) {
		if(j == -1 || buf[i] == buf[j])
			knext[++i] = ++j;
		else
			j = knext[j];
	}
}

int main()
{
	int kase = 1;

	while(scanf("%d", &len) != EOF && len != 0) {
		scanf("%s", buf);
		kmpinit();
		if(kase >= 2) putchar('\n');
		printf("Test case #%d\n", kase++);
		for(int i = 2; i <= len; ++i)
			if(knext[i] > 0 && i % (i - knext[i]) == 0)
				printf("%d %d\n", i, i / (i - knext[i]));
	}
}
