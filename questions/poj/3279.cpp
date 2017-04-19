// POJ No.3279 Fliptile O(mn2^n) (384K 907MS)
// 求关灯问题的字典序最小解。
// 相当于POJ3276的二维扩展，按字典序枚举第一行的所有翻法
// 对第一行的每种翻法，求最小的可行解，求可行解方法如下：
// 翻下一行来将上一行全部变为0，判断最后一行是否全是0
// 若均为0，则有可行解;
// 若存在1，则无法不影响其他值，来将其置0，即无解
#include <cstdio>
#include <cstring>
using namespace std;
const int maxn = 16;

int r, c;
char opt[maxn][maxn];
char grid[maxn][maxn];
char flip[maxn][maxn];

int getcol(int rr, int cc)
{
    int color = grid[rr][cc];
    const int dir[][2] = {{0,1}, {0,-1}, {1,0}, {-1,0}, {0,0}};

    for(int i = 0; i < 5; ++i) {    // 不要忘记这里是5，不是4
        int nr = rr + dir[i][0], nc = cc + dir[i][1];
        if(0<=nr&&nr<r && 0<=nc&&nc<c && flip[nr][nc])
            ++color;
    }
    return color % 2;
}

int calc()
{
    for(int i = 1; i < r; ++i) {
        for(int j = 0; j < c; ++j)
            if(getcol(i-1, j) == 1) flip[i][j] = 1;
    }

    for(int i = 0; i < c; ++i)
        if(getcol(r-1, i) == 1)
            return -1;

    int cnt = 0;
    for(int i = 0; i < r; ++i)
        for(int j = 0; j < c; ++j)
            cnt += flip[i][j];
    return cnt;
}

int main()
{
    scanf("%d%d", &r, &c);
    for(int i = 0; i < r; ++i)
        for(int j = 0; j < c; ++j)
            scanf("%d", &grid[i][j]);

    int cnt = -1;
    for(int S = 0; S < (1 << c); ++S) {
        memset(flip, 0, sizeof(flip));

        for(int i = 0; i < c; ++i)
            if(S & (1 << i)) flip[0][c-i-1] = 1;
        int ncnt = calc();

        if(ncnt >= 0 && (cnt == -1 || ncnt < cnt)) {
            cnt = ncnt;
            memcpy(opt, flip, sizeof(flip));
        }
    }

    if(cnt == -1) {
        puts("IMPOSSIBLE");
        return 0; 
    }

    for(int i = 0; i < r; ++i) {
        printf("%d", opt[i][0]);
        for(int j = 1; j < c; ++j)
            printf(" %d", opt[i][j]);
        putchar(10);
    }
}
