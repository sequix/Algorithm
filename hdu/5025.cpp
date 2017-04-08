// HDU No.5925 Coconuts (0MS 3612K)
// 给一副RxC的棋盘，0 < R,C < 1e9，上面有n个障碍, 0 <= n <= 200
// 问n个障碍将棋盘分成几个连通的区域和这些区域的面积（方格数）
// 离散化：最直接的搜索限于图的庞大无法直接使用，
// 发现n<=200，可将图按障碍的坐标离散为400x400的图
// 进而由搜索求面积
// 离散的细节：
// 以前有的点，新图中还会有，并且相邻两点间的距离大于1(即不相邻)时，
// 将该段距离的间隙当作一个点，并记录其长度
// 以上所说的离散细节同时应用与x轴和y轴
// 最后可以对每个间隙记录的两个长度相乘求其面积
#include <bits/stdc++.h>
using namespace std;
typedef int64_t LL;
const int maxn = 405;
const int dir[][2] = {{0,1}, {0,-1}, {1,0}, {-1,0}};

int R, C, n;
int dR, dC;                 // 离散后的行列数
LL ans[maxn];
bool g[maxn][maxn];         // 离散后的图，为1代表原图中该点有障碍
int x[maxn], y[maxn];       // 原始的障碍坐标
int bx[maxn], by[maxn];     // 原始坐标的副本，用于离散化
int lx[maxn], ly[maxn];     // 每个点在x，y轴上的长度
map<int, int> xtab, ytab;   // 原始坐标到离散后坐标的映射

int discretize(int *x, int *lx, map<int, int> &xtab, int n)
{
    int dx = 0; // 离散后的点数
    sort(x, x + n);
    int cnt = unique(x, x + n) - x;
    for(int i = 1; i < cnt; ++i) {
        int dis = x[i] - x[i-1];
        // 注意lx记录间隙的长度，所以dis-1
        if(dis > 1) lx[dx++] = dis - 1;
        // 原有的点在新图要保证也有，所以
        if(i < cnt-1) { lx[dx] = 1; xtab[x[i]] = dx++; }
    }
    return dx;
}

void dfs(int x, int y, LL &area)
{
    g[x][y] = 0;
    area += (LL)lx[x] * ly[y];
    for(int i = 0; i < 4; ++i) {
        int nx = x + dir[i][0], ny = y + dir[i][1];
        if(0<=nx&&nx<dR && 0<=ny&&ny<dC && g[nx][ny])
            dfs(nx, ny, area);
    }
}

int main()
{
    int T;
    scanf("%d", &T);

    for(int kase = 1; kase <= T; ++kase) {
        scanf("%d%d%d", &R, &C, &n);
        for(int i = 0; i < n; ++i) {
            scanf("%d%d", &x[i], &y[i]);
            bx[i] = x[i], by[i] = y[i];
        }
        // 在点集中加入边界外一点
        // 以方便计算最边缘的点与边界的距离
        bx[n] = 0, bx[n+1] = R+1;
        by[n] = 0, by[n+1] = C+1;
        // 离散化行列
        dR = discretize(bx, lx, xtab, n+2);
        dC = discretize(by, ly, ytab, n+2);
        // 构造离散化后的图
        for(int i = 0; i < dR; ++i)
            for(int j = 0; j < dC; ++j)
                g[i][j] = 1;
        for(int i = 0; i < n; ++i)
            g[xtab[x[i]]][ytab[y[i]]] = 0;
        // 计算面积
        int ans_cnt = 0;
        for(int i = 0; i < dR; ++i) {
            for(int j = 0; j < dC; ++j) {
                if(g[i][j]) {
                    LL area = 0;
                    dfs(i, j, area);
                    ans[ans_cnt++] = area;
                }
            }
        }
        sort(ans, ans + ans_cnt);

        printf("Case #%d:\n", kase);
        printf("%d\n", ans_cnt);
        printf("%lld", ans[0]);
        for(int i = 1; i < ans_cnt; ++i)
            printf(" %lld", ans[i]);
        putchar('\n');
    }
}
