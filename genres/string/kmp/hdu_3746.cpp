// HDU No.3746 Cyclic Nacklace (187MS 2056K)
// 最少填多少字符可将字符串变成完全由某个循环节构成的字符串。
// 仅需要计算向最后一个不足的循环节中放多少个字符
// 可使其称为一个循环节
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10;

int m;
char P[maxn];
int knext[maxn];

int getnext()
{
    knext[0] = -1;
    int i = 0, j = -1; 

    while(i < m) {
        if(j == -1 || P[i] == P[j])
            knext[++i] = ++j;
        else
            j = knext[j];
    }
}

int main()
{
    int T;
    for(scanf("%d", &T); T; --T) {
        scanf("%s", P);
        m = strlen(P);
        getnext();

        int len = m - knext[m]; // 循环节长度
        if(len != m && m % len == 0)
            puts("0");
        else
            printf("%d\n", len - knext[m] % len);
    }
}
