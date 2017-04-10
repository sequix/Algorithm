// POJ No.3320 Jessica's Reading Problem O(N) (1916K 454MS)
// 给一本P(1<=P<=1e6)的书，第i页由知识点A[i](知识点可能重复)
// 问最少读连续的几页将书读完? 每个知识点由一个32位整数表示
// 尺取法：维护起点s，终点t和当前子串能学到的知识点数cnt
// 用set数一共有多少知识点，map记录当前子串中每个知识点的个数
// 每当遇到一个新知识点时cnt+1，每当一个知识点数降为0时cnt-1
#include <set>
#include <map>
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 1e6 + 10;

int A[maxn];
set<int> ss;
map<int, int> mm;

int main()
{
    int N;  // 知识点数
    int P, s, t, cnt, ans;

    scanf("%d", &P);
    for(int i = 0; i < P; ++i) {
        scanf("%d", &A[i]);
        ss.insert(A[i]);
    }

    N = ss.size();
    ans = P;
    s = t = cnt = 0;

    while(1) {
        while(t < P && cnt < N) {
            if(mm[A[t]] == 0) ++cnt;
            ++mm[A[t++]];
        }
        if(cnt < N) break;
        ans = min(ans, t - s);
        if(--mm[A[s++]] == 0) --cnt;
    }
    printf("%d\n", ans);
}
