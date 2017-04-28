// HUST No.1017 Exact Cover (Dancing Links) (564ms 1916kb)
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1010;
const int maxm = maxn * maxn;

struct DLX {
    int nn;         // number of nodes，head为0
    int hr[maxn];   // 每行首个元素，用于插入行
    int row[maxm], col[maxm];   // 原矩阵中的行列数
    int L[maxm], R[maxm], U[maxm], D[maxm]; // 四个方向的指针
    int ans[maxn];  // 保存都选择了哪些行

    void init(int _n, int _m) {
        nn = _m+1;
        memset(hr, -1, sizeof(hr));
        for(int i = 0; i <= _m; ++i) {
            U[i] = D[i] = i;
            L[i] = i - 1, R[i] = i + 1;
        }
        L[0] = _m, R[_m] = 0;
    }
    // 将1放到第r行第c列
    void addone(int r, int c) {
        int p = nn++;
        row[p] = r, col[p] = c;
        // 插入列
        U[p] = U[c];
        D[p] = c;
        D[U[p]] = U[D[p]] = p;
        // 插入行
        if(hr[r] == -1) {
            hr[r] = p;
            L[p] = R[p] = p;
        } else {
            L[p] = L[hr[r]];
            R[p] = hr[r];
            L[R[p]] = R[L[p]] = p;
        }
    }
    // 删除c列，及其所覆盖的行
    void remove(int c) {
        L[R[c]] = L[c];
        R[L[c]] = R[c];
        for(int i = D[c]; i != c; i = D[i]) {
            for(int j = R[i]; j != i; j = R[j]) {
                U[D[j]] = U[j];
                D[U[j]] = D[j];
            }
        }
    }
    // 恢复c列，及其所覆盖的行
    void resume(int c) {
        for(int i = U[c]; i != c; i = U[i])
            for(int j = L[i]; j != i; j = L[j])
                U[D[j]] = D[U[j]] = j;
        L[R[c]] = R[L[c]] = c;
    }
    int dfs(int dep) {
        int ret, c;
        if(R[0] == 0) return dep;

        c = R[0];
        remove(c);
        for(int i = D[c]; i != c; i = D[i]) {
            ans[dep] = row[i];
            for(int j = R[i]; j != i; j = R[j])
                remove(col[j]);
            if(ret = dfs(dep+1))
                return ret;
            for(int j = L[i]; j != i; j = L[j])
                resume(col[j]);
        }
        resume(c);
        return 0;
    }
    int dance() { return dfs(0); }
} dlx;

int main()
{
    int nn, c, n, m;   // n为子集数，m为原集合的元素数量

    while(scanf("%d%d", &n, &m) != EOF) {
        dlx.init(n, m);
        for(int r = 1; r <= n; ++r) {
            for(scanf("%d", &nn); nn > 0; --nn) {
                scanf("%d", &c);
                dlx.addone(r, c);
            }
        }
        int ans = dlx.dance();
        if(!ans) {
            puts("NO");
        } else {
            printf("%d", ans);
            for(int i = 0; i < ans; ++i)
                printf(" %d", dlx.ans[i]);
            putchar(10);
        }
    }
}
