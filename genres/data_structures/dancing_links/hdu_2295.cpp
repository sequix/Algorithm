// HDU No.2295 Radar (二分答案+DLX重复覆盖) (78MS 1520K)
// 找最小半径使使用不超过K个雷达将所城市覆盖。
#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 3000;
const double eps = 1e-8;

int n, m, K;
double dis[55][55];
int cx[55], cy[55];
int rx[55], ry[55];

struct DLX {
    int size;
    int h[maxn], cnt[maxn], col[maxn];
    int L[maxn], R[maxn], D[maxn], U[maxn];

    void init(int n, int m) {
        size = m + 1;
        memset(h, -1, sizeof(h[0]) * (n+1));
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
        for(int i = D[c]; i != c; i = D[i])
            L[R[i]] = L[i], R[L[i]] = R[i];
    }
    void resume(int c) {
        for(int i = U[c]; i != c; i = U[i])
            L[R[i]] = R[L[i]] = i;
    }
    int predictedDistance() {
        int ans = 0;
        bool vis[55] = {0};
        for(int c = R[0]; c != 0; c = R[c]) {
            if(vis[c]) continue;
            ++ans; vis[c] = 1;
            for(int i = D[c]; i != c; i = D[i])
                for(int j = R[i]; j != i; j = R[j])
                    vis[col[j]] = 1;
        }
        return ans;
    }
    bool dfs(int dep) {
        int ret, c;
        if(R[0] == 0) { return dep <= K; }
        if(predictedDistance() + dep > K) return 0;

        c = R[0];
        for(int i = R[0]; i != 0; i = R[i])
            if(cnt[i] < cnt[c]) c = i;
        for(int i = D[c]; i != c; i = D[i]) {
            remove(i);
            for(int j = R[i]; j != i; j = R[j]) remove(j);
            if(dfs(dep+1)) return 1;
            for(int j = L[i]; j != i; j = L[j]) resume(j);
            resume(i);
        }
        return 0;
    }
} dlx;

bool isok(double r)
{
    dlx.init(m, n);
    for(int i = 0; i < m; ++i)
        for(int j = 0; j < n; ++j)
            if(dis[i][j] <= r) dlx.addone(i + 1, j + 1);
    return dlx.dfs(0);
}

int main()
{
    int T;
    for(scanf("%d", &T); T > 0; --T) {
        scanf("%d%d%d", &n, &m, &K);
        for(int i = 0; i < n; ++i) scanf("%d%d", &cx[i], &cy[i]);
        for(int i = 0; i < m; ++i) scanf("%d%d", &rx[i], &ry[i]);

        for(int i = 0; i < m; ++i)
            for(int j = 0; j < n; ++j)
                dis[i][j] = hypot(rx[i]-cx[j], ry[i]-cy[j]);

        double left = 0.0, right = 1500.0;
        while(right - left > eps) {
            double mid = (left + right) / 2;
            if(isok(mid))
                right = mid;
            else
                left = mid;
        }
        printf("%.6f\n", left);
    }
}
