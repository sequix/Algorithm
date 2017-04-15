// POJ No.3292 Semi-prime H-numbers (6616K 0MS)
// H-素数：形似4n+1的被称作H-素数(且其没有其他形如4n+1的因子)，
// 两个H-素数相乘得到H-合成数，求n范围内的H-合成数个数。
// 筛法求所有的h-prime，再枚举所有的h-semi-prime打表。
#include <cstdio>
using namespace std;
const int maxn = 1e6 + 10;

int n;
int ans[maxn];
int hcnt, h[maxn];
bool check[maxn];
bool is_h_semi_prime[maxn];

int main()
{
    for(int i = 5; i < maxn; i += 4) {
        if(check[i]) continue;
        h[hcnt++] = i;
        for(int j = i; j < maxn; j += i)
            check[j] = 1;
    }

    for(int i = 0; i < hcnt; ++i) {
        for(int j = 0; j <= i; ++j) {
            unsigned long long  mul = h[i] * h[j];
            if(mul > maxn) break;
            is_h_semi_prime[mul] = 1;
        }
    }

    for(int i = 1; i < maxn; ++i)
        ans[i] = ans[i-1] + is_h_semi_prime[i];

    while(scanf("%d", &n) != EOF && n)
        printf("%d %d\n", n, ans[n]);
}
