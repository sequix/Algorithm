// POJ No.3468 树状数组: 段修改，段查询 (3484K 1922MS)
// http://www.cnblogs.com/lcf-2000/p/5866170.html
// https://wenku.baidu.com/view/cff30f88cc22bcd126ff0c25.html
#include <cstdio>
using namespace std;
typedef long long LL;
const int maxn = 1e5 + 10;
inline int lowbit(int x) { return x & -x; }

int n, q;
LL A[maxn], B[maxn];
LL C1[maxn], C2[maxn];

void add(int x, LL a)
{
    for(int i = x; i <= n; i += lowbit(i))
        C1[i] += a, C2[i] += x * a;
}

LL query(int x)
{
    LL r=0;
    for(int i = x; i > 0; i -= lowbit(i))
        r += (x+1)*C1[i] - C2[i];
    return r;
}

int main()
{
    char cmd[2]; int a, b; LL c;

    scanf("%d%d", &n, &q);
    for(int i = 1; i <= n; ++i) scanf("%lld", &A[i]);
    for(int i = n; i >= 1; --i) A[i] = A[i] - A[i-1];
    for(int i = 1; i <= n; ++i) B[i] = i * A[i];
    for(int i = 2; i <= n; ++i) A[i] += A[i-1], B[i] += B[i-1];
    for(int i = 1; i <= n; ++i) C1[i] = A[i] - A[i-lowbit(i)];
    for(int i = 1; i <= n; ++i) C2[i] = B[i] - B[i-lowbit(i)];

    while(q--) {
        scanf("%s", cmd);
        if(cmd[0] == 'Q') {
            scanf("%d%d", &a, &b);
            printf("%lld\n", query(b) - query(a-1));
        } else {
            scanf("%d%d%lld", &a, &b, &c);
            add(a, c), add(b+1, -c);
        }
    }
}
