// POJ No.3461 Oulipo (1420K 79MS)
// 数字符串s中字符串p出现的次数，kmp解决
#include <cstdio>
#include <cctype>
using namespace std;

char p[10010];
char s[1000010];
int knext[1000010];
int lenp, lens;

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

int kmp()
{
    int ans = 0;
    knext[0] = -1;
    int i = 0, j = -1;

    if(lenp > lens) return 0;

    while(i < lenp) {
        if(j == -1 || p[i] == p[j])
            knext[i] = (p[++i] == p[++j]) ? knext[j] : j;
        else
            j = knext[j];
    }

    i = 0, j = 0;
    while(i < lens && j < lenp) {
        if(j == -1 || s[i] == p[j]) {
            ++i, ++j;
            if(j == lenp) {
                ++ans;
                j = knext[j];
            }
        } else {
            j = knext[j];
        }
    }
    return ans;
}

int main()
{
    int n;
    for(scanf("%d", &n); n > 0; --n) {
        lenp = getline(p);
        lens = getline(s);
        printf("%d\n", kmp());
    }
}
