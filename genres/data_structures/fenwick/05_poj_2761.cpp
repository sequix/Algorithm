// POJ No.2761 树状数组求第K小值 (2516K 2485MS)
// A[i] 表示小于等于i的元素的个数
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 1e5 + 10;
const int maxm = 5e4 + 10;
#define lowbit(x) ((x) & -(x))

struct Query {
    int L, R, k, no;
    bool operator < (const Query &q) const
        { return (L != q.L) ? L < q.L : R < q.R; }
} qs[maxm];

int n, m;
int nh, hashtab[maxn];
int A[maxn], C[maxn], ans[maxm];

void add(int i, int a)
{
    for(; i <= n; i += lowbit(i))
        C[i] += a;
}

int kth(int k)
{
    int ans = 0, cnt = 0;
    for(int i = 17; i >= 0; --i) {
        ans |= 1 << i;
        if(ans > n || cnt + C[ans] >= k)
            ans &= ~(1 << i);
        else
            cnt += C[ans];
    }
    return ans + 1;
}

int mhash(int x)
{
    return lower_bound(hashtab+1, hashtab+nh+1, x) - hashtab;
}

int main()
{
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; ++i) {
        scanf("%d", &A[i]);
        hashtab[i] = A[i];
    }
    for(int i = 0; i < m; ++i) {
        scanf("%d%d%d", &qs[i].L, &qs[i].R, &qs[i].k);
        qs[i].no = i;
    }

    sort(hashtab+1, hashtab+n+1);
    nh = unique(hashtab+1, hashtab+n+1) - hashtab - 1;
    sort(qs, qs + m);

    int L = 0, R = -1;
    for(int kq = 0; kq < m; ++kq) {
        if(R < qs[kq].L) {
            for(int j = L; j <= R; ++j)
                add(mhash(A[j]), -1);
            for(int j = qs[kq].L; j <= qs[kq].R; ++j)
                add(mhash(A[j]), 1);
        } else {
            for(int j = L; j < qs[kq].L; ++j)
                add(mhash(A[j]), -1);
            for(int j = R+1; j <= qs[kq].R; ++j)
                add(mhash(A[j]), 1);
        }
        ans[qs[kq].no] = hashtab[kth(qs[kq].k)];
        L = qs[kq].L, R = qs[kq].R;
    }
    for(int i = 0; i < m; ++i) printf("%d\n", ans[i]);
}
