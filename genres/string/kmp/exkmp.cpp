// 扩展kmp
// test input: aaaabaa aaaaa
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10;

int knext[maxn], ex[maxn];
char str[maxn], pattern[maxn];

void getnext(char *p)
{
    int i, j, po;   // po 为取得最远点的点
    int len = strlen(p);

    knext[0] = len;
    for(i = 0; p[i] == p[i+1] && i+1 < len; ++i);
    knext[1] = i;
    po = 1;

    for(i = 2; i < len; ++i) {
        // i == k + 1
        // po + knext[po] == P + 1
        if(i + knext[i-po] < po + knext[po]) {
            knext[i] = knext[i-po];
        } else {
            j = po + knext[po] - i; // j == P - k
            if(j < 0) j = 0;        // i+j == P + 1
            while(i+j < len && p[j] == p[i+j]) ++j;
            knext[i] = j;
            po = i;
        }
    }
}

void exkmp(char *s, char *p)
{
    int i, j, po;
    int lens = strlen(s), lenp = strlen(p);

    getnext(p);
    for(i = 0; s[i]==p[i] && i<lens && i < lenp; ++i);
    ex[0] = i;
    po = 0;

    for(i = 1; i < lens; ++i) {
        if(i + knext[i-po] < po + ex[po]) {
            ex[i] = knext[i-po];
        } else {
            j = po + ex[po] - i;
            if(j < 0) j = 0;
            while(i+j<lens && j<lenp && s[i+j]==p[j]) ++j;
            ex[i] = j;
            po = i;
        }
    }
}

int main()
{
    while(scanf("%s%s", str, pattern) != EOF) {
        exkmp(str, pattern);
        int lens = strlen(str);
        int lenp = strlen(pattern);

        printf("next:\n");
        for(int i = 0; i < lenp; ++i)
            printf("%2d ", knext[i]);
        putchar(10);

        printf("extend:\n");
        for(int i = 0; i < lens; ++i)
            printf("%2d ", ex[i]);
        putchar(10);
    }
}
