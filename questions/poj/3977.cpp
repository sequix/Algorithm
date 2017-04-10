// POJ No.3977 Subset (折半枚举) (7564K 15172MS)
// 从N个数中挑出非空子集使得和的绝对值最小
// 枚举前半，二分后半，O(n^2logn)
#include <map>
#include <cstdio>
#define abs(x) ((x) < 0 ? -(x) : (x))
using namespace std;
typedef long long LL;

int n;
LL A[40];
map<LL, int> mm;    // 和，与计算这个和所用的元素个数

int main()
{
    while(scanf("%d", &n) != EOF && n != 0) {
        mm.clear();

        for(int i = 0; i < n; ++i)
            scanf("%lld", &A[i]);

        pair<LL, int> ans(abs(A[0]), 1);

        for(int i = 1; i < (1 << n/2); ++i) {
            LL sum = 0;
            int cnt = 0;
            for(int j = 0; j < n/2; ++j)
                if(i & (1 << j)) sum += A[j], ++cnt;

            ans = min(ans, make_pair(abs(sum), cnt));
            map<LL, int>::iterator it = mm.find(sum);

            if(it != mm.end())
                it->second = min(it->second, cnt);
            else
                mm[sum] = cnt;
        }

        for(int i = 1; i < (1 << n-n/2); ++i) {
            LL sum = 0;
            int cnt = 0;
            for(int j = 0; j < n-n/2; ++j)
                if(i & (1 << j)) sum += A[n/2 + j], ++cnt;

            ans = min(ans, make_pair(abs(sum), cnt));

            // lower_bound返回首个不小于sum的迭代器
            // 所以可能的位置是it和it-1
            map<LL, int>::iterator it = mm.lower_bound(-sum);

            if(it != mm.end()) {
                ans = min(ans,
                    make_pair(abs(it->first+sum), it->second+cnt));
            }

            if(it != mm.begin()) {
                --it;
                ans = min(ans,
                    make_pair(abs(it->first+sum), it->second+cnt));
            }
        }
        printf("%lld %d\n", ans.first, ans.second);
    }
}
