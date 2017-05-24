// 树状数组：单点修改，查询
// C[i] = A[i] + A[i-1] + ... + A[i-lowbit(i)+1]
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e3 + 10;
#define lowbit(x) ((x)&-(x))

int n, m, a, b, c;
int A[maxn], S[maxn], C[maxn];

void add(int i, int a)
{
    for(; i <= n; i += lowbit(i))
        C[i] += a;
}

int sum(int i)
{
    int ans = 0;
    for(; i > 0; i -= lowbit(i))
        ans += C[i];
    return ans;
}

int main()
{
    cin >> n;
    for(int i = 1; i <= n; ++i)
        cin >> A[i];
    S[1] = A[1];
    for(int i = 2; i <= n; ++i)
        S[i] = S[i-1] + A[i];
    for(int i = 1; i <= n; ++i)
        C[i] = S[i] - S[i-lowbit(i)];

    for(cin >> m; m > 0; --m) {
        cin >> c >> a >> b;
        switch(c) {
            case 1: add(a, b); break;
            case 2: printf("%d\n", sum(b) - sum(a-1)); break;
        }
    }
}
