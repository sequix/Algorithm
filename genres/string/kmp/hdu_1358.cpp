// HDU No.1358 Period (KMP) (171MS 6456K)
// 问可由循环节构成的前缀的长度，和循环节出现次数
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 10;

char S[maxn];
int knext[maxn];

int main()
{
    int len, kase = 1;

    while(~scanf("%d", &len) && len) {
        scanf("%s", S);
         
        knext[0] = -1;
        int i = 0, j = -1;

        while(i < len) {
            if(j == -1 || S[i] == S[j])
                knext[++i] = ++j;
            else
                j = knext[j];
        }

        printf("Test case #%d\n", kase++);
        for(i = 2; i <= len; ++i) {
            int cl = i - knext[i];    // 循环节长度
            if(i != cl && i % cl == 0)
                printf("%d %d\n", i, i / cl);
        }
        putchar(10);
    }
}
