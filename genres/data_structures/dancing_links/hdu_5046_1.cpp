// HUD No.5046 Airport (DLX重复覆盖) (795MS 1684K)
// 选择K个点，使其他点到最近被选择点的最大距离最小。
// 二分距离，由距离构建DLX的行列，行表示选择某个城市
// 列表示该城市所能在该距离能能覆盖到的点
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 65;
const int maxm = 65;
const int maxnode = maxn * maxm;

struct DLX {
    int size, ans;
    int H[maxn], cnt[maxm], col[maxnode];
    int L[maxnode], R[maxnode], U[maxnode], D[maxnode];

    void init(int m, int k) {
        size = m + 1, ans = k;
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
        int h = 0;
        bool vis[maxm] = {0};
        for(int c = R[0]; c; c = R[c]) {
            if(vis[c]) continue;
            ++h, vis[c] = 1;
            for(int i = D[c]; i != c; i = D[i])
                for(int j = R[i]; j != i; j = R[j])
                    vis[col[j]] = 1;
        }
        return h;
    }
    bool dfs(int dep) {
        if(!R[0]) return dep <= ans;
        if(A() + dep > ans) return 0;

        int c = R[0];
        for(int i = R[0]; i; i = R[i])
            if(cnt[i] < cnt[c]) c = i;
        for(int i = D[c]; i != c; i = D[i]) {
            remove(i);
            for(int j = R[i]; j != i; j = R[j]) remove(j);
            if(dfs(dep + 1)) return 1;
            for(int j = L[i]; j != i; j = L[j]) resume(j);
            resume(i);
        }
        return 0;
    }
} dlx;

int T, n, k;
LL dis[maxn][maxn];
LL x[maxn], y[maxn];

bool isok(LL d)
{
    dlx.init(n, k);
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < n; ++j)
            if(dis[i][j] <= d) dlx.add(i+1, j+1);
    return dlx.dfs(0);
}

int main()
{
    scanf("%d", &T);
    for(int kase = 1; kase <= T; ++kase) {
        scanf("%d%d", &n, &k);
        for(int i = 0; i < n; ++i)
            scanf("%lld%lld", &x[i], &y[i]);

        LL left = 0, right = 0;
        for(int i = 0; i < n; ++i) {
            for(int j = i+1; j < n; ++j) {
                dis[i][j] = dis[j][i] = abs(x[i]-x[j])+abs(y[i]-y[j]);
                right = max(right, dis[i][j]);
            }
        }

        while(left < right) {
            LL mid = (left + right) >> 1;
            if(isok(mid))
                right = mid;
            else
                left = mid + 1;
        }
        printf("Case #%d: %lld\n", kase, left);
    }
}
