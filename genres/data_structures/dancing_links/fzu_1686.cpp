// FZU No.1686 神龙的难题 (重复覆盖) (562ms 1972KB)
// 用所给小矩形覆盖大矩形中的所有1。要求覆盖次数最少。
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 300;
const int maxm = 300;
const int maxnode = maxn * maxm;

struct DLX {
    int size, ans;
    int h[maxn], cnt[maxm], col[maxnode];
    int L[maxnode], R[maxnode], U[maxnode], D[maxnode];

    void init(int m) {
        size = m + 1, ans = 0x3f3f3f3f;
        memset(h, -1, sizeof(h));
        for(int i = 0; i <= m; ++i) {
            cnt[i] = 0;
            col[i] = D[i] = U[i] = i;
            L[i] = i - 1, R[i] = i + 1;
        }
        L[0] = m, R[m] = 0;
    }
    void add(int r, int c) {
        int i = size++;
        col[i] = c, ++cnt[c];
        U[i] = c, D[i] = D[c];
        U[D[i]] = D[U[i]] = i;
        if(h[r] == -1) {
            h[r] = L[i] = R[i] = i;
        } else {
            L[i] = h[r], R[i] = R[h[r]];
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
        int ans = 0;
        bool vis[maxm] = {0};
        for(int i = R[0]; i != 0; i = R[i]) {
            if(vis[i]) continue;
            vis[i] = 1; ++ans;
            for(int j = D[i]; j != i; j = D[j])
                for(int k = R[j]; k != j; k = R[k])
                    vis[col[k]] = 1;
        }
        return ans;
    }
    void dfs(int dep) {
        if(dep + A() >= ans) return;
        if(R[0] == 0) { ans = min(ans, dep); return; }

        int c = R[0];
        for(int i = R[0]; i != 0; i = R[i])
            if(cnt[i] < cnt[c]) c = i;
        for(int i = D[c]; i != c; i = D[i]) {
            remove(i);
            for(int j = R[i]; j != i; j = R[j]) remove(j);
            dfs(dep + 1);
            for(int j = L[i]; j != i; j = L[j]) resume(j);
            resume(i);
        }
    }
    int dance() { dfs(0); return ans; }
} dlx;

int main()
{
    int n, m, nn, mm, id[20][20];

    while(~scanf("%d%d", &n, &m)) {
        int dlx_m = 0, dlx_n = 1;
        memset(id, 0, sizeof(id));
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < m; ++j) {
                scanf("%d", &id[i][j]);
                if(id[i][j] == 1) id[i][j] = ++dlx_m;
            }
        }
        dlx.init(dlx_m);
        scanf("%d%d", &nn, &mm);
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < m; ++j) {
                for(int x = 0; x < nn && i+x < n; ++x)
                    for(int y = 0; y < mm && j+y < m; ++y)
                        if(id[i+x][j+y]) dlx.add(dlx_n, id[i+x][j+y]);
                ++dlx_n;
            }
        }
        printf("%d\n", dlx.dance());
    }
}
