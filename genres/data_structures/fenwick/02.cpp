// 树状数组: 段修改，单点查询
// http://www.cnblogs.com/lcf-2000/p/5866170.html
// https://wenku.baidu.com/view/cff30f88cc22bcd126ff0c25.html
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e3 + 10;
inline int lowbit(int x) { return x & -x; }

int n, m, a, b, c;
int A[maxn], C[maxn];

void add(int i, int a)
{
    for(; i <= n; i += lowbit(i)) C[i] += a;
}

void segadd(int L, int R, int a)
{
    add(L, a);
    add(R+1, -a);
}

int query(int i)
{
    int ans = 0;
    for(; i > 0; i -= lowbit(i))
        ans += C[i];
    return ans;
}

int main()
{
    cin >> n;
    for(int i = 1; i <= n; ++i) cin >> A[i];
    for(int i = n; i >= 1; --i) A[i] = A[i] - A[i-1];
    for(int i = 2; i <= n; ++i) A[i] += A[i-1];
    for(int i = 1; i <= n; ++i) C[i] = A[i] - A[i-lowbit(i)];

    for(cin >> m; m > 0; --m) {
        cin >> c;
        switch(c) {
            case 1:
                cin >> a >> b >> c;
                segadd(a, b, c);
                break;
            case 2:
                cin >> a;
                printf("%d\n", query(a));
                break;
        }
    }
}
