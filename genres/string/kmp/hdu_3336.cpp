// HDU No.3336 Count the string (78ms 3.3MB)
// 求所有前缀出现次数和 % MOD_NUM
#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 10;
const int MOD_NUM = 10007;

int n;
char s[maxn];
int cnt[maxn];      // cnt[i] 长度为i的前缀出现次数
int knext[maxn];

int solve()
{
    knext[0] = -1;
    int i = 0, j = -1;
    memset(cnt, 0, sizeof(cnt));

    while(i < n) {
        if(j == -1 || s[i] == s[j])
            knext[++i] = ++j;
        else
            j = knext[j];
    }

    i = 0, j = 0;
    while(i < n) {
        if(j == -1 || s[i] == s[j]) {
            ++i, ++j;
            for(int k = j; k > 0; k = knext[k])
                cnt[k] = (cnt[k] + 1) % 10007;
        } else {
            j = knext[j];
        }
    }

    int ans = 0;
    for(int i = 1; i <= n; ++i)
        ans = (ans + cnt[i]) % MOD_NUM;
    return ans;
}

int main()
{
    int T;
    for(scanf("%d", &T); T; --T) {
        scanf("%d%s", &n, s);
        printf("%d\n", solve());
    }
}
