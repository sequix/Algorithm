// POJ No.2785 4 Values whose Sum is 0 (49420K 8375MS)
// 给4个数组ABCD，每个数组有n<=4000个绝对值不超过2^28的整数，
// 求从每个数组中选一个元素，并使4个元素和为0的选法数目。
// 考虑到n<=4000，暴力的O(N^4)必超时，采用折半枚举
// 用O(N^2)枚举出所有的CD的所用组合
// 对每一个AB的组合找对应的c+d=-(a+b)的个数，用时O(N^2 * logN)
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 4001;
typedef long long LL;

int n;
LL CD[maxn * maxn];
int A[maxn], B[maxn], C[maxn], D[maxn];

int main()
{
    scanf("%d", &n);
    for(int i = 0; i < n; ++i)
        scanf("%d%d%d%d", &A[i], &B[i], &C[i], &D[i]);

    for(int i = 0; i < n; ++i)
        for(int j = 0; j < n; ++j)
            CD[i*n+j] = (LL)C[i] + D[j];
    sort(CD, CD + n*n);

    LL ans = 0;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            LL x = -((LL)A[i] + B[j]);
            ans += upper_bound(CD, CD + n*n, x) - lower_bound(CD, CD + n*n, x);
        }
    }
    printf("%lld\n", ans);
}
