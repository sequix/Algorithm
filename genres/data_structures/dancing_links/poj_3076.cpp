// POJ No.3076 Sudoku (1456K 407MS)
#include <cstdio>
#include <cctype>
#include <cstring>
using namespace std;
const int maxn = 1e5;

struct DLX {
    int m, nn, ans[maxn];
    int R[maxn], L[maxn], U[maxn], D[maxn];
    int hr[maxn], ccnt[maxn], row[maxn], col[maxn];

    void init(int _m) {
        nn = _m + 1, m = _m;
        memset(ccnt, 0, sizeof(ccnt));
        memset(hr, -1, sizeof(hr));
        for(int i = 0; i <= m; ++i) {
            U[i] = D[i] = i;
            L[i] = i - 1, R[i] = i + 1;
        }
        L[0] = m, R[m] = 0;
    }
    void addone(int r, int c) {
        int i = nn++;
        row[i] = r, col[i] = c, ++ccnt[c];
        U[i] = c, D[i] = D[c];
        U[D[i]] = D[U[i]] = i;
        if(hr[r] < 0) {
            hr[r] = L[i] = R[i] = i;
        } else {
            L[i] = hr[r], R[i] = R[hr[r]];
            L[R[i]] = R[L[i]] = i;
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
        int c, ret;
        if(R[0] == 0) return dep;

        c = R[0];
        for(int i = R[0]; i != 0; i = R[i])
            if(ccnt[i] < ccnt[c]) c = i;

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

int encode(int a, int b, int c)
{
    return 256*a + 16*b + c + 1;
}

void decode(int p, int &a, int &b, int &c)
{
    --p;
    c = p % 16; p /= 16;
    b = p % 16; p /= 16;
    a = p;
}

void adddig(int r, int c, int d)
{
    enum TYPE { GRD, ROW, COL, BLK };
    int k = encode(r, c, d); 
    dlx.addone(k, encode(GRD, r, c));
    dlx.addone(k, encode(ROW, r, d));
    dlx.addone(k, encode(COL, c, d));
    dlx.addone(k, encode(BLK, (r/4)*4+(c/4), d));
}

int main()
{
    int r, c, d, ch;
    bool firCase = 1;
    char ans[17][17];

    while(1) {
        dlx.init(1024);
        for(int i = 0; i < 16; ++i) {
            scanf("%s", ans[i]);
            for(int j = 0; j < 16; ++j) {
                if(ans[i][j] == '-')
                    for(int d = 0; d < 16; ++d) adddig(i, j, d);
                else
                    adddig(i, j, ans[i][j]-'A');
            }
        }
        int cnt = dlx.dance();
        for(int i = 0; i < cnt; ++i) {
            decode(dlx.ans[i], r, c, d);
            ans[r][c] = d + 'A';
        }
        if(firCase) firCase = 0; else putchar(10);
        for(int i = 0; i < 16; ++i) puts(ans[i]);
        while(isspace(ch = getchar()));
        if(ch == EOF) break; else ungetc(ch, stdin);
    }
}
