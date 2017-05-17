// POJ No.1084 Square Destroyer (DLX重复覆盖) (612K 0MS)
// 给n*n的不完整网格图，去掉最少的边使图中没有正方形。
// 行为边，列为正方形，问题转化为重复覆盖问题
#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 65;
const int maxm = 60;
const int maxnode = maxn * maxm;

struct {
    int size, ans;
    int H[maxn], cnt[maxm], col[maxnode];
    int D[maxnode], U[maxnode], L[maxnode], R[maxnode];

    void init(int m) {
        size = m + 1, ans = 0x3f3f3f3f;
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
        for(int i = D[c]; i != c; i = D[i])
            L[R[i]] = R[L[i]] = i;
    }
    int A() {
        int h = 0;
        bool vis[maxm] = {0};
        for(int c = R[0]; c; c = R[c]) {
            if(vis[c]) continue;
            vis[c] = 1, ++h;
            for(int i = D[c]; i != c; i = D[i])
                for(int j = R[i]; j != i; j = R[j])
                    vis[col[j]] = 1;
        }
        return h;
    }
    void dfs(int dep) {
        if(dep + A() >= ans) return;
        if(!R[0]) { ans = min(ans, dep); return; }

        int c = R[0];
        for(int i = R[0]; i; i = R[i])
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

int n;
bool nostick[maxn];
enum SIDE { U, D, L, R };
struct P { int i, j, k; };  // 标识左上角为(i,j)的k阶正方形

int getside(int i, int j, SIDE side)
{
    switch(side) {
        case U: return (i-1)*(2*n+1) + j;
        case D: return i*(2*n+1) + j;
        case L: return i*(2*n+1) + j - n - 1;
        case R: return i*(2*n+1) + j - n;
    }
}

bool existSquare(int i, int j, int k)
{
    for(int kk = 0; kk < k; ++kk)
        if(nostick[getside(i, j+kk, U)]) return 0;
    for(int kk = 0; kk < k; ++kk)
        if(nostick[getside(i+k-1, j+kk, D)]) return 0;
    for(int kk = 0; kk < k; ++kk)
        if(nostick[getside(i+kk, j, L)]) return 0;
    for(int kk = 0; kk < k; ++kk)
        if(nostick[getside(i+kk, j+k-1, R)]) return 0;
    return 1;
}

void addSquare(int i, int j, int k, int col)
{
    for(int kk = 0; kk < k; ++kk)
        dlx.add(getside(i, j+kk, U), col);
    for(int kk = 0; kk < k; ++kk)
        dlx.add(getside(i+k-1, j+kk, D), col);
    for(int kk = 0; kk < k; ++kk)
        dlx.add(getside(i+kk, j, L), col);
    for(int kk = 0; kk < k; ++kk)
        dlx.add(getside(i+kk, j+k-1, R), col);
}

int solve()
{
    vector<P> squares;

    for(int k = 1; k <= n; ++k)
        for(int i = 1; i+k <= n+1; ++i)
            for(int j = 1; j+k <= n+1; ++j)
                if(existSquare(i, j, k))
                    squares.push_back((P){i, j, k});

    dlx.init(squares.size());
    for(int i = 0; i < squares.size(); ++i)
        addSquare(squares[i].i, squares[i].j, squares[i].k, i+1);
    return dlx.dance();
}

int main()
{
    int T, x, nn;

    for(scanf("%d", &T); T; --T) {
        scanf("%d%d", &n, &nn);
        memset(nostick, 0, sizeof(nostick));

        for(int i = 0; i < nn; ++i) {
            scanf("%d", &x);
            nostick[x] = 1;
        }
        printf("%d\n", solve());
    }
}
