// Kuhn-Munkres算法 带权二分图最优匹配 O(V^3)

#if 0

KM算法是通过给每个顶点一个标号（叫做顶标）来把求最大权匹配的问题转化为求完备匹配的问题的。

设顶点Xi的顶标为A[i]，顶点Yi的顶标为B[i]，顶点Xi与Yj之间的边权为w[i,j]。

在算法执行过程中的任一时刻，对于任一条边(i,j)， A[i]+B[j]>=w[i,j]始终成立。KM算法的正确性基于以下定理：
　　若由二分图中所有满足A[i]+B[j]=w[i,j]的边(i,j)构成的子图称做相等子图有完备匹配，那么这个完备匹配就是二分图的最大权匹配。
　　这个定理是显然的。因为对于二分图的任意一个匹配，如果它包含于相等子图，那么它的边权和等于所有顶点的顶标和（显然这是最大的）；
    如果它有的边不包含于相等子图，那么它的边权和小于所有顶点的顶标和。所以相等子图的完备匹配一定是二分图的最大权匹配。

初始时为了使A[i]+B[j]>=w[i,j]恒成立，令A[i]为所有与顶点Xi关联的边的最大权，
B[j]=0。如果当前的相等子图没有完备匹配，就按下面的方法修改顶标以使扩大相等子图，直到相等子图具有完备匹配为止。

我们求当前相等子图的完备匹配失败了，是因为对于某个X顶点，我们找不到一条从它出发的交错路。这时我们获得了一棵交错树，
它的叶子结点全部是X顶点（因为dfs中总是走X点，所以找不到相等子图中的下一个点，也是在X点处找不到的）。
现在我们把交错树中X顶点的顶标全都减小某个值d，Y顶点的顶标全都增加同一个值d，那么我们会发现：

1.两端都在交错树中的边(i,j)，A[i]+B[j]的值没有变化。它原来属于相等子图，现在仍属于相等子图。
2.两端都不在交错树中的边(i,j)，A[i]和B[j]都没有变化。它原来属于（或不属于）相等子图，现在仍属于（或不属于）相等子图。
3.X端不在交错树中，Y端在交错树中的边(i,j)，它的A[i]+B[j]的值有所增大。它原来不属于相等子图，现在仍不属于相等子图。
4.X端在交错树中，Y端不在的边(i,j)，它的A[i]+B[j]有所减小。它原来不属于相等子图，现在可能进入相等子图，因而使相等子图得到了扩大。

现在的问题就是求d值了。为了使A[i]+B[j]>=w[i,j]始终成立，且至少有一条边进入相等子图，
d应该等于min{A[i]+B[j]-w[i,j]|Xi在交错树中，Yi不在交错树中}。

以上就是KM算法的基本思路。但是朴素的实现方法，时间复杂度为O(n4)——需要找O(n)次增广路，
每次增广最多需要修改O(n)次顶标，每次修改顶标时由于要枚举边来求d值，复杂度为O(n2)。
实际上KM算法的复杂度是可以做到O(n3)的。
我们给每个Y顶点一个“松弛量”函数slack，每次开始找增广路时初始化为无穷大。
在寻找增广路的过程中，检查边(i,j)时，如果它不在相等子图中，则让slack[j]变成原值与A[i]+B[j]-w[i,j]的较小值。
这样，在修改顶标时，取所有不在交错树中的Y顶点的slack值中的最小值作为d值即可。
但还要注意一点：修改顶标后，要把所有的slack值都减去d。
因为Lx[i］变小了d 而slack[j] = min{Lx[i] + Ly[j] -w[i][j]} 所以slack[j](j不属于交错树)受影响也要减小d

#endif // comment

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
                else slack[j] -= d;
        }
    }
}
