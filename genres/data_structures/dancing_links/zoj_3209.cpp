// ZOJ No.3209 Treasure Map (DLX精确覆盖) (200ms 9216kb)
// 用所给小矩形不覆盖地拼出一个大矩形。
// 为避免公共边的覆盖，这里将每个矩形的上和左侧各截去一个单位
// 同时将原(m+1)*(n+1)的矩形截为m*n（对，是m行n列!!!)
// 注意精确覆盖求得仅是一组可行解，并非最小解
#include <bits/stdc++.h>
using namespace std;
const int maxn = 505;
const int maxm = 905;
const int maxnode = maxn * maxm;

struct DLX {
    int ans, m, size;
    int h[maxn], cnt[maxm], col[maxnode];
    int L[maxnode], R[maxnode], D[maxnode], U[maxnode];

    void init(int _m) {
        m = _m, size = _m + 1, ans = -1;
        memset(h, -1, sizeof(h));
        for(int i = 0; i <= m; ++i) {
            cnt[i] = 0;
            col[i] = D[i] = U[i] = i;
            L[i] = i - 1, R[i] = i + 1;
        }
        L[0] = m, R[m] = 0;
    }
    void addone(int r, int c) {
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
        L[R[c]] = L[c], R[L[c]] = R[c];
        for(int i = D[c]; i != c; i = D[i])
            for(int j = R[i]; j != i; j = R[j])
                U[D[j]] = U[j], D[U[j]] = D[j], --cnt[col[j]];
    }
    void resume(int c) {
        for(int i = U[c]; i != c; i = U[i])
            for(int j = L[i]; j != i; j = L[j])
                U[D[j]] = D[U[j]] = j, ++cnt[col[j]];
        L[R[c]] = R[L[c]] = c;
    }
    void dfs(int dep) {
        int ret, c;
        if(ans != -1 && dep >= ans) return;
        if(R[0] == 0) {
            ans = (ans == -1) ? dep : min(ans, dep);
            return;
        }
        c = R[0];
        for(int i = R[0]; i != 0; i = R[i])
            if(cnt[i] < cnt[c]) c = i;
        remove(c);
        for(int i = D[c]; i != c; i = D[i]) {
            for(int j = R[i]; j != i; j = R[j]) remove(col[j]);
            dfs(dep + 1);
            for(int j = L[i]; j != i; j = L[j]) resume(col[j]);
        }
        resume(c);
    }
    int dance() { dfs(0); return ans; }
} dlx;

int main()
{
    int T, n, m, p, x1, x2, y1, y2;

    for(scanf("%d", &T); T > 0; --T) {
        scanf("%d%d%d", &n, &m, &p);
        dlx.init(n * m);    // m行n列
        for(int i = 1; i <= p; ++i) {
            scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
            for(int y = y1; y < y2; ++y)
                for(int x = x1+1; x <= x2; ++x)
                    dlx.addone(i, y * n + x);
        }
        printf("%d\n", dlx.dance());
    }
}
