#include <cstdio>
#include <cstring>
using namespace std;
const int maxn = 1e6;

int n, a, b, L, R;
char s[maxn], t[maxn];

int knext[maxn];

int main()
{
    scanf("%d%d%d%d%d%s", &n, &a, &b, &L, &R, t);
    int n2 = strlen(t);

    int w = b;
    for(int i = 0; i < n; ++i) {
        if(L <= w && w <= R) {
            s[i] = "AT"[w & 1];
        } else {
            s[i] = "GC"[w & 1];
        }
        w = (w + a) % n;
    }
    s[n] = 0;
    puts(s);

    int i = 0, j = -1;
    knext[0] = -1;

    while(i < n2) {
        if(j == -1 || t[i] == t[j]) {
            ++i, ++j;
            if(t[i] == t[j])
                knext[i] = knext[j];
            else
                knext[i] = j;
        } else {
            j = knext[j];
        }
    }

    int ans = 0;
    i = 0, j = 0;
    while(i < n && j < n2) {
        if(j == -1 || s[i] == t[j]) {
            ++i, ++j;
            if(j == n2) ++ans, j = knext[j];
        } else {
            j = knext[j];
        }
    }
    printf("%d\n", ans);
}
