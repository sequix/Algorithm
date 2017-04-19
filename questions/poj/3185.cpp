// POJ No.3185 The Water Bowls (388K 0MS)
// 求一维关灯问题的最小步数，参考POJ3276
// 但注意，首尾翻仅影响2个，而中间会影响3个，所以做以下处理：
// 在队伍A[1...20]的最前面加A[0]，并仅在A[0...19]区间遍历。
// A[0]==0相当于在原串中从第二个开始翻的情况;
// A[0]==1相当于在原串中从第一个开始翻的情况。
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 20;
const int inf = 0x3f3f3f3f;

char A[maxn+5];
char f[maxn+5];

int calc(int first)
{
    A[0] = first;
    int s = 0, cnt = 0;
    for(int i = 0; i <= maxn-1; ++i) {
        f[i] = ((A[i] + s) & 1);
        cnt += f[i];
        s += f[i];
        if(i >= 2) s -= f[i-2];
    }
    return ((A[maxn] + s) & 1) ? inf : cnt;
}

int main()
{
    for(int i = 1; i <= maxn; ++i)
        scanf("%d", &A[i]);
    printf("%d\n", min(calc(0), calc(1)));
}
