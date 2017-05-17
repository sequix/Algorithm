// HDU No.3498 whosyourdaddy (DLX重复覆盖 + A*) (1981MS 1676K)
// 每次将一个点和其相邻的点去除，问最少多少步将一个无向图删完？
// 每个点对应DLX中的一个列，每一行对应一个点和其相邻的点
// 求重负覆盖数即可。
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e4;

struct DLX {
    int m, nn, ans;
    int L[maxn], R[maxn], U[maxn], D[maxn];
    int hr[maxn], ccnt[maxn], row[maxn], col[maxn];

    void init(int _m) {
        ans = m = _m, nn = _m + 1;
        memset(hr, -1, sizeof(hr));
        memset(ccnt, 0, sizeof(ccnt));
        for(int i = 0; i <= m; ++i) {
            U[i] = D[i] = i;
            L[i] = i-1, R[i] = i+1;
        }
        L[0] = m, R[m] = 0;
    }
    void addone(int r, int c) {
        int i = nn++;
        row[i] = r, col[i] = c, ++ccnt[c];
        U[i] = c, D[i] = D[c];
        U[D[i]] = D[U[i]] = i;
        if(hr[r] == -1) {
            hr[r] = L[i] = R[i] = i;
        } else {
            L[i] = hr[r], R[i] = R[hr[r]];
            L[R[i]] = R[L[i]] = i;
        }
    }
    // 与精确覆盖不同:
    //     remove的参数c是一个1的编号，不是某一列
    //     仅删一列，而不是某一列及其所覆盖的行
    void remove(int c) {
        for(int i = D[c]; i != c; i = D[i])
            L[R[i]] = L[i], R[L[i]] = R[i];
    }
    // 与精确覆盖不同:
    //     resume的参数c是一个1的编号，不是某一列
    //     仅恢复一列，而不是某一列及其所覆盖的行
    void resume(int c) {
        for(int i = U[c]; i != c; i = U[i])
            L[R[i]] = R[L[i]] = i;
    }
    int predictedDistance() {
        int ans = 0;
        bool vis[80] = {0};
        for(int c = R[0]; c != 0; c = R[c]) {
            if(vis[c]) continue;
            ++ans;
            vis[c] = 1;
            for(int i = D[c]; i != c; i = D[i])
                for(int j = R[i]; j != i; j = R[j])
                    vis[col[j]] = 1;
        }
        return ans;
    }
    void dfs(int dep) {
        if(R[0] == 0) { ans = min(ans, dep); return; }
        // 注意这里：
        //   如果当前代价 + 预计代价 >= 已得到的结果
        //   则没有必要继续搜索
        if(dep + predictedDistance() >= ans) return;

        int c = R[0];
        for(int i = R[0]; i != 0; i = R[i])
            if(ccnt[i] < ccnt[c]) c = i;
        for(int i = D[c]; i != c; i = D[i]) { remove(i);
            // 若选择该行，则将该行能覆盖的所有列去掉
            // 但并没有去掉其所能覆盖到的行
            // 所以接下来的搜索中还是有可能选到之前列被去掉过的行
            // 即某一列可以被重复覆盖到
            for(int j = R[i]; j != i; j = R[j])
                remove(j);
            dfs(dep+1);
            for(int j = L[i]; j != i; j = L[j])
                resume(j);
            resume(i);
        }
    }
    int dance() { dfs(0); return ans; }
} dlx;

int main()
{
    int n, m, u, v;
    while(~scanf("%d%d", &n, &m)) {
        dlx.init(n);
        for(int i = 1; i <= n; ++i)
            dlx.addone(i, i);
        for(int i = 0; i < m; ++i) {
            scanf("%d%d", &u, &v);
            dlx.addone(u, v);
            dlx.addone(v, u);
        }
        printf("%d\n", dlx.dance());
    }
}
