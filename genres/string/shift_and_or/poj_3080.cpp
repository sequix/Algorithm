// POJ No.3080 Blue Jeans (shift_or) (376K 16MS)
// 给m个长度为60的字符串，求最长公共子串
// 枚举其中一个字符串的所有子串，判断其在其它串中是否存在
// 记录最长子串且字典序最小子串即可
#include <cstdio>
#include <cstring>
using namespace std;
typedef long long LL;
const int maxn = 65;
const int maxm = 12;

int m;
LL b[128];  // b[i] 字符i在哪些位置出现
char str[maxm][maxn];

bool isok(char *s, int len)
{
    LL shift = 1;
    memset(b, -1, sizeof(b));
    for(int i = 0; i < len; ++i) {
        b[s[i]] &= ~shift;
        shift <<= 1;
    }

    LL mask = ~(1LL << len-1);
    for(int i = 1; i < m; ++i) {
        LL d = -1;
        bool found = 0;
        for(int j = 0; j < 60; ++j) {
            d = (d << 1) | b[str[i][j]];
            if(~(d | mask)) { found = 1; break; }
        }
        if(!found) return 0;
    }
    return 1;
}

int main()
{
    int T;

    for(scanf("%d", &T); T; --T) {
        scanf("%d", &m);
        for(int i = 0; i < m; ++i)
            scanf("%s", str[i]);

        int ans_i = -1, ans_len = -1;
        for(int i = 0; i < 60; ++i) {
            for(int len = 60-i; len >= 1; --len) {
                if(isok(&str[0][i], len)) {
                    if(len > ans_len)
                        ans_i = i, ans_len = len;
                    else if(len == ans_len &&
                            strcmp(&str[0][i], &str[0][ans_i]) < 0)
                        ans_i = i, ans_len = len;
                }
            }
        }

        if(ans_len < 3) {
            puts("no significant commonalities");
        } else {
            str[0][ans_i + ans_len] = 0;
            puts(&str[0][ans_i]);
        }
    }
}
