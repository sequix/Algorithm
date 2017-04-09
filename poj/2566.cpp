// POJ No.2566 Bound Found (1172K 94MS)
// 给1<=N<=1e5个整数(<=1e4)，可正可负，
// 问子串和的绝对值与0<=t<=1e9最接近的子串最短长度。
// 考虑到N的大小，复杂度应控制在O(N)，又由子串想到尺取法
// 但尺取法要求元素单调，那么，计算原数组的前缀和sum[]
// 并将其排序，保证其单调，再次使用尺取，解决之
#include <cstdio>
#include <algorithm>
using namespace std;
typedef pair<int, int> P;    // <sum[i], i>
const int inf = 0x3f3f3f3f;
const int maxn = 1e5 + 10;

P sum[maxn];
int N, k, t, A[maxn];

int update(int ss, int tt, int &L, int &R, int &cur_ans)
{
    // 如果区间sum[tt]-sum[ss]中没有元素，
    // 则将cur_sum设为t距离最远的初始状态
    if(ss >= tt) return -inf; 
    int new_sum = sum[tt].first - sum[ss].first;
    if(abs(new_sum-t) < abs(cur_ans-t)) {
        cur_ans = new_sum;
        L = min(sum[tt].second, sum[ss].second);
        R = max(sum[tt].second, sum[ss].second);
    }
    return new_sum;
}

int main()
{
    int cur_sum, cur_ans;
    int x, ss, tt, L, R;

    while(scanf("%d%d", &N, &k) == 2 && N+k) {
        sum[0] = P(0, 0);
        for(int i = 1; i <= N; ++i) {
            scanf("%d", &sum[i].first);
            sum[i].first += sum[i-1].first;
            sum[i].second = i;
        }
        sort(sum, sum+N+1);

        while(k--) {
            scanf("%d", &t);
            ss = tt = L = R = 0;
            cur_ans = cur_sum = -inf;   // 最初与t的距离为无穷大
            while(1) {
                while(tt < N && cur_sum < t)
                    cur_sum = update(ss, ++tt, L, R, cur_ans);
                if(cur_sum < t) break;
                cur_sum = update(++ss, tt, L, R, cur_ans);
            }
            printf("%d %d %d\n", cur_ans, L+1, R);
        }
    }
}
