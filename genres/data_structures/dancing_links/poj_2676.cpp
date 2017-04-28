// POJ No.2676 Sudoku (DLX) (616K 0MS)
// 1.一个格子里只能放一个数
// 2.每行同一数字只能放一个
// 3.每列同一数字只能放一个
// 4.每个九宫格中同一数字只能放一个
// 以上四个条件分别对应不同的列，共324列
// 而每一行对应(r, c, d)第r行，第c列，为数字d的选择
// 考虑到出现的行，列，数字均为超过9，所以用9进制编码
// 同样的方法可以过POJ 2918,3074,3076
#include <cstdio>
#include <cstring>
using namespace std;
const int maxn = 2e4;

struct DLX {
    int m, nn, nc;
    int row[maxn], col[maxn];
    int hr[maxn], ans[maxn], ccnt[maxn];
    int L[maxn], R[maxn], U[maxn], D[maxn];

    void init(int _m) {
        m = _m, nn = _m+1;
        memset(hr, -1, sizeof(hr));
        memset(ccnt, 0, sizeof(ccnt));
        for(int i = 0; i <= m; ++i) {
            U[i] = D[i] = i;
            L[i] = i - 1, R[i] = i + 1;
        }
        L[0] = m, R[m] = 0;
    }
    void addone(int r, int c) {
        int p = nn++;
        row[p] = r, col[p] = c, ++ccnt[c];
        D[p] = D[c];
        U[p] = c;
        U[D[p]] = D[c] = p;
        if(hr[r] == -1) {
            hr[r] = p;
            L[p] = R[p] = p;
        } else {
            L[p] = hr[r];
            R[p] = R[hr[r]];
            L[R[p]] = R[hr[r]] = p;
        }
    }
    void remove(int c) {
        L[R[c]] = L[c], R[L[c]] = R[c];
        for(int i = D[c]; i != c; i = D[i]) {
            for(int j = R[i]; j != i; j = R[j]) {
                U[D[j]] = U[j], D[U[j]] = D[j];
                --ccnt[col[j]];
            }
        }
    }
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
    int dance() { return nc = dfs(0); }
} dlx;

int encode(int a, int b, int c)
{
    return 81*a + 9*b + c + 1;
}

void decode(int p, int &a, int &b, int &c)
{
    --p;
    c = p % 9; p /= 9;
    b = p % 9; p /= 9;
    a = p;
}

void adddig(int r, int c, int d)
{
    enum TYPE { GRD, ROW, COL, BLK };
    int k = encode(r, c, d); 
    dlx.addone(k, encode(GRD, r, c));
    dlx.addone(k, encode(ROW, r, d));
    dlx.addone(k, encode(COL, c, d));
    dlx.addone(k, encode(BLK, (r/3)*3+(c/3), d));
}

int main()
{
    int T, ans[11][11], r, c, d;

    for(scanf("%d", &T); T > 0; --T) {
        dlx.init(324);
        for(int i = 0; i < 9; ++i) {
            for(int j = 0; j < 9; ++j) {
                scanf("%1d", &ans[i][j]);
                if(ans[i][j])
                    adddig(i, j, ans[i][j]-1);
                else
                    for(int d = 0; d < 9; ++d) adddig(i, j, d);
            }
        }
        int cnt = dlx.dance();
        for(int i = 0; i < cnt; ++i) {
            decode(dlx.ans[i], r, c, d);
            ans[r][c] = d + 1;
        }
        for(int i = 0; i < 9; ++i) {
            for(int j = 0; j < 9; ++j)
                printf("%d", ans[i][j]);
            putchar(10);
        }
    }
}
