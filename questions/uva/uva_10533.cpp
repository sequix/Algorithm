// UVA No.10533 Digit Primes (170ms)
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 10;

int sum[maxn];
bool check[maxn];
int np, prime[maxn];
bool isDigitalPrime[maxn];

bool judge(int x)
{
    int s = 0;
    while(x) s += x%10, x /= 10;
    return !check[s];
}

void init()
{
    for(int i = 2; i < maxn; ++i) {
        if(!check[i]) prime[np++] = i;
        for(int j = 0; j<np && i*prime[j]<maxn; ++j) {
            check[i*prime[j]] = 1;
            if(i % prime[j] == 0) break;
        }
    }
    for(int i = 0; i < np; ++i)
        isDigitalPrime[prime[i]] = judge(prime[i]);
    for(int i = 1; i < maxn; ++i)
        sum[i] = sum[i-1] + isDigitalPrime[i];
}

int main()
{
    init();
    int T, a, b;
    for(scanf("%d", &T); T > 0; --T) {
        scanf("%d%d", &a, &b);
        printf("%d\n", sum[b] - sum[a-1]);
    }
}
