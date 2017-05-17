// HDU No.3335 Divisibility (DLX重复覆盖) (15MS 1824K)
// 选仅可能多的整数，满足每两个之间不能整除。
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 1e3 + 10;
const int maxm = 1e3 + 10;
const int maxnode = maxn * maxm;

struct DLX {
    int size, ans;
    int H[maxn], cnt[maxm], col[maxnode];
    int L[maxnode], R[maxnode], U[maxnode], D[maxnode];

    void init(int m) {
        size = m + 1, ans = -1;
        memset(H, -1, sizeof(H));
        for(int i = 0; i <= m; ++i) {
            cnt[i] = 0;
            col[i] = U[i] = D[i] = i;
            L[i] = i - 1, R[i] = i + 1;
        }
        L[0] = m, R[m] = 0;
    }
    void add(int r, int c) {
        int i = size++;
        col[i] = c, ++cnt[c];
        U[i] = c, D[i] = D[c];
        U[D[i]] = D[U[i]] = i;
        if(H[r] == -1) {
            H[r] = L[i] = R[i] = i;
        } else {
            L[i] = H[r], R[i] = R[H[r]];
            L[R[i]] = R[L[i]] = i;
        }
    }
    void remove(int c) {
        for(int i = D[c]; i != c; i = D[i])
            L[R[i]] = L[i], R[L[i]] = R[i];
    }
    void resume(int c) {
        for(int i = U[c]; i != c; i = U[i])
            L[R[i]] = R[L[i]] = i;
    }
    int A() {
        int price = 0;
        bool vis[maxm] = {0};
        for(int c = R[0]; c != 0; c = R[c]) {
            if(vis[c]) continue;
            ++price, vis[c] = 1;
            for(int i = D[c]; i != c; i = D[i])
                for(int j = R[i]; j != i; j = R[j])
                    vis[col[j]] = 1;
        }
        return price;
    }
    void dfs(int dep) {
        if(A() + dep <= ans) return;
        if(R[0] == 0) { ans = max(ans, dep); return; }

        int c = R[0];
        for(int i = R[0]; i != 0; i = R[i])
            if(cnt[i] < cnt[c]) c = i;
        for(int i = D[c]; i != c; i = D[i]) {
            remove(i);
            for(int j = R[i]; j != i; j = R[j])
                remove(j);
            dfs(dep + 1);
            for(int j = L[i]; j != i; j = L[j])
                resume(j);
            resume(i);
        }
    }
    int dance() { dfs(0); return ans; }
} dlx;

int T, n;
LL A[maxn];
bool f[maxn][maxn]; // f[i][j] A[i] A[j]之间是否整除

int main()
{
    for(scanf("%d", &T); T > 0; --T) {
        scanf("%d", &n);
        for(int i = 0; i < n; ++i)
            scanf("%lld", &A[i]);

        sort(A, A + n);
        n = unique(A, A + n) - A;
        for(int i = 0; i < n; ++i)
            for(int j = i; j < n; ++j)
                f[i][j] = f[j][i] = (A[j] % A[i] == 0);

        dlx.init(n);
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < n; ++j)
                if(f[i][j]) dlx.add(i+1, j+1);
        printf("%d\n", dlx.dance());
    }
}
