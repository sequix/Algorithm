// Kuhn-Munkres算法 带权二分图最优匹配 O(V^3)

int lx[maxn];       // x点的标号
int ly[maxn];       // y点的标号 
int cy[maxn];       // cy[y]与y点匹配的x点
int slack[maxn];    // slack[y]没在交错树中点的lx[x]+ly[y]-g[x][y]
bool visx[maxn];    // visx[x]交错树中是否有x点
bool visy[maxn];    // visy[y]交错树中是否有x点
int g[maxn][maxn];  // 二分图的邻接矩阵，保存权值

int dfs(int x)
{
    visx[x] = 1;
    for(int y = 0; y < ny; ++y) {
        if(visy[y]) continue;
        if(lx[x] + ly[y] == g[x][y]) {
            visy[y] = 1;
            if(cy[y] == -1 || dfs(cy[y])) {
                cy[y] = x;
                return 1;
            }
        } else {
            slack[y] = min(slack[y], lx[x] + ly[y] - g[x][y]);
        }
    }
    return 0;
}

void km()
{
    memset(cy, -1, sizeof(cy));
    memset(ly, 0, sizeof(ly));
    memset(lx, 0, sizeof(lx));
    for(int i = 0; i < nx; ++i)
        for(int j = 0; j < ny; ++j)
            lx[i] = max(lx[i], g[i][j]);
    for(int i = 0; i < nx; ++i) {
        memset(slack, inf, sizeof(slack));
        while(1) {
            memset(visx, 0, sizeof(visx));
            memset(visy, 0, sizeof(visy));
            if(dfs(i)) break;
            int d = inf;
            for(int j = 0; j < ny; ++j)
                if(!visy[j]) d = min(d, slack[j]);
            for(int j = 0; j < nx; ++j)
                if(visx[j]) lx[j] -= d;
            for(int j = 0; j < ny; ++j)
                if(visy[j]) ly[j] += d;
// 下面这句保证下一次执行时，不会选择到这次的y点
// 因为至少a所对应的slack[j]会变成0，又由相等子图的定义
// 有 A[i] + B[i] >= w[i, j]，所以保证了不会选择重复的y点
                else slack[j] -= d;
        }
    }
}
