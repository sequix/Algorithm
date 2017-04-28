// POJ No.2918 Tudoku (DFS) (364K 0MS)
#include <cstdio>
#include <cstring>
using namespace std;

int ans[10][10];
bool rowhas[10][10], colhas[10][10];

void init()
{
    memset(rowhas, 0, sizeof(rowhas));
    memset(colhas, 0, sizeof(colhas));
    for(int i = 0; i < 9; ++i) {
        for(int j = 0; j < 9; ++j) {
            scanf("%1d", &ans[i][j]);
            rowhas[i][ans[i][j]] = colhas[j][ans[i][j]] = 1;
        }
    }
}

bool firstZero(int &r, int &c)
{
    for(int i = 0; i < 9; ++i)
        for(int j = 0; j < 9; ++j)
            if(!ans[i][j]) { r = i, c = j; return 1; }
    return 0;
}

bool dfs()
{
    int r, c;
    if(!firstZero(r, c)) return 1;

    bool has[10] = {0};
    for(int i = 1; i <= 9; ++i)
        has[i] = rowhas[r][i] || colhas[c][i];

    for(int d = 1; d <= 9; ++d) {
        if(has[d]) continue;
        ans[r][c] = d;
        rowhas[r][d] = colhas[c][d] = 1;
        if(dfs()) return 1;
        rowhas[r][d] = colhas[c][d] = 0;
        ans[r][c] = 0;
    }
    return 0;
}

int main()
{
    int T;
    scanf("%d", &T);
    for(int kase = 1; kase <= T; ++kase) {
        init();
        dfs();
        printf("Scenario #%d:\n", kase);
        for(int i = 0; i < 9; ++i) {
            for(int j = 0; j < 9; ++j)
                printf("%d", ans[i][j]);
            putchar(10);
        }
        putchar(10);
    }
}
