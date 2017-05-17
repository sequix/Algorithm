// POJ No.2406 Power Strings (5268K 63MS)
// 求可已构成整个字符串的最小串的重复次数
// 用kmp的next数组求整个串的循环节长度repetend
// 若的确是循环节，则len % repetend == 0，答案为len / repetend
// 否则字符处不是由某个循环节构成，答案为1
#include <cstdio>
#include <cctype>
#include <algorithm>
using namespace std;
const int maxn = 1e6 + 10;

int len;
char s[maxn];
int knext[maxn];

int getline(char *s)
{
    int c, cnt = 0;
    while(isspace(c = getchar()));
    ungetc(c, stdin);
    while((c = getchar()) != EOF && c != '\n')
        s[cnt++] = c;
    s[cnt] = '\0';
    return cnt;
}

void kmp()
{
    knext[0] = -1;
    int i = 0, j = -1;

    while(i < len) {
        if(j == -1 || s[i] == s[j])
            knext[++i] = ++j;
        else
            j = knext[j];
    }
}

int main()
{
    while((len = getline(s)) > 0) {
        if(len == 1 && s[0] == '.') break;
        kmp();
        int repetend = len - knext[len];
        printf("%d\n", len % repetend ? 1 : len / repetend);
    }
}
