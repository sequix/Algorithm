// HUST No.1017 Exact Cover (Dancing Links) (188ms 1928kb)
// 改进插入方式，支持任一顺序的插入（即头插法）
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1010;
const int maxm = maxn * maxn;

struct DLX {
    int n, m;       // 行列数
    int nn;         // number of nodes，head为0
    int hr[maxn];   // 每行首个元素，用于插入行
    int row[maxm], col[maxm];   // 原矩阵中的行列数
    int L[maxm], R[maxm], U[maxm], D[maxm]; // 四个方向的指针
    int ans[maxn];  // 保存都选择了哪些行
    int ccnt[maxn]; // 每一列中1的个数，用于dfs中剪枝

    void init(int _n, int _m) {
        n = _n, m = _m, nn = _m+1;
        memset(hr, -1, sizeof(hr));
        memset(ccnt, 0, sizeof(ccnt));
        for(int i = 0; i <= m; ++i) {
            U[i] = D[i] = i;
            L[i] = i - 1, R[i] = i + 1;
        }
        L[0] = m, R[m] = 0;
    }
    // 将1放到第r行第c列
    void addone(int r, int c) {
        int p = nn++;
        row[p] = r, col[p] = c, ++ccnt[c];
        // 插入列
        D[p] = D[c];
        U[p] = c;
        U[D[p]] = D[c] = p;
        // 插入行
        if(hr[r] == -1) {
            hr[r] = p;
            L[p] = R[p] = p;
        } else {
            L[p] = hr[r];
            R[p] = R[hr[r]];
            L[R[p]] = R[hr[r]] = p;
        }
    }
    // 删除c列，及这些元素所覆盖的行
    // 但并没有删除这些行所覆盖到的其他列
    void remove(int c) {
        L[R[c]] = L[c];
        R[L[c]] = R[c];
        for(int i = D[c]; i != c; i = D[i]) {
            for(int j = R[i]; j != i; j = R[j]) {
                U[D[j]] = U[j];
                D[U[j]] = D[j];
                --ccnt[col[j]];
            }
        }
    }
    // 恢复c列，及其所覆盖的行
    void resume(int c) {
        for(int i = U[c]; i != c; i = U[i]) {
            for(int j = L[i]; j != i; j = L[j]) {
                U[D[j]] = D[U[j]] = j;
                ++ccnt[col[j]];
            }
        }
        L[R[c]] = R[L[c]] = c;
    }
    int dfs(int dep) {
        int ret, minc, c;
        if(R[0] == 0) return dep;

        minc = 0x3f3f3f3f, c = -1;
        for(int i = R[0]; i != 0; i = R[i])
            if(ccnt[i] < minc) minc = ccnt[i], c = i;

        remove(c);
        for(int i = D[c]; i != c; i = D[i]) {
            ans[dep] = row[i];
            // 如果选择了这一行，就要将该行所能覆盖到的且它列删掉
            // 以保证每一列仅由一个1来覆盖
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
