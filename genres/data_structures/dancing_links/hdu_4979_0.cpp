// HDU No.4979 A simple math problem. (DLX重复覆盖)
// 每次从N个数中选M个，用最少次数覆盖所有选R个的情况。
// 考虑到N，M，R均不大于8，用二进制模拟集合
// DLX中的列为每个需被覆盖的选R的组合，行为每个选M个的组合
#include <bits/stdc++.h>
using namespace std;
const int maxn = 100;
const int maxm = 100;
const int maxnode = maxn * maxm;

struct DLX {
    int size, ans;
    int H[maxn], cnt[maxm], col[maxnode];
    int L[maxnode], R[maxnode], U[maxnode], D[maxnode];

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
        for(int i = U[c]; i != c; i = U[i])
            L[R[i]] = R[L[i]] = i;
    }
    int A() {
        int h = 0;
        bool vis[maxm] = {0};
        for(int c = R[0]; c; c = R[c]) {
            if(!vis[c]) {
                vis[c] = 1, ++h;
                for(int i = D[c]; i != c; i = D[i])
                    for(int j = R[i]; j != i; j = R[j])
                        vis[col[j]] = 1;
            }
        }
        return h;
    }
    void dfs(int dep) {
        if(A() + dep >= ans) return;
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

int C[10][10];
int incol[1 << 8];
int bitcnt[1 << 8];
int ans[10][10][10];

void init()
{
    for(int i = 0; i < 1<<8; ++i)
        for(int x = i; x > 0; x &= x-1)
            ++bitcnt[i];
    for(int i = 1; i <= 8; ++i) {
        C[i][0] = C[i][i] = 1;
        for(int j = 1; j < i; ++j)
            C[i][j] = C[i-1][j] + C[i-1][j-1];
    }
}

int solve(int N, int M, int R)
{
    dlx.init(C[N][R]);

    int cnt = 0;
    for(int i = 0; i < 1<<N; ++i)
        if(bitcnt[i] == R)
            incol[i] = ++cnt;

    int rcnt = 0;
    for(int i = 0; i < 1<<N; ++i) {
        if(bitcnt[i] == M) {
            ++rcnt;
            for(int j = i; j; j = i & j-1) // 枚举i的子集
                if(bitcnt[j] == R) dlx.add(rcnt, incol[j]);
        }
    }
    return dlx.dance();
}

void gettable()
{
    for(int N = 1; N <= 8; ++N)
        for(int M = 1; M <= N; ++M)
            for(int R = 1; R <= M; ++R)
                ans[N][M][R] = solve(N, M, R);
}

void printtable()
{
    FILE *fp = fopen("table", "w");

    fprintf(fp, "{\n");
    for(int N = 0; N <= 8; ++N) {
        fprintf(fp, "    {\n");
        for(int M = 0; M <= N; ++M) {
            fprintf(fp, "        {");
            for(int R = 0; R <= M; ++R) {
                if(R >= 1) fprintf(fp, ", ");
                fprintf(fp, "%d", ans[N][M][R]);
            }
            fprintf(fp, "}");
            if(M < N) fprintf(fp, ",");
            fprintf(fp, "\n");
        }
        fprintf(fp, "    }");
        if(N < 8) fprintf(fp, ",");
        fprintf(fp, "\n");
    }
    fprintf(fp, "}\n");
    fclose(fp);
}

int main()
{
    init();
    gettable();
    printtable();
}
