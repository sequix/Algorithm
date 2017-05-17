// POJ No.2752 Seek the Name, Seek the Fame
// 求所有公共前后缀（包含原串）的长度，升序输出
#include <cstdio>
#include <cctype>
using namespace std;
const int maxn = 4e5 + 10;

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

void print(int p)
{
    if(p <= 0) return;
    print(knext[p]);
    printf("%d ", p);
}

int main()
{
    int n;
    while((len = getline(s)) > 0) {
        kmp();
        print(knext[len]);
        printf("%d\n", len);
    }
}
