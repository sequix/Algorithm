//// Floyd-Warshall
// floyd本质是一个利用滚动二维数组的三维DP：
// A[k][i][j] 表示从i到j经过k条中间边的最小距离
// 则有状态转移方程：
// A[0][i][j] = G[i][j]
// A[k][i][j] = min(A[k-1][i][j], A[k-1][i][k] + A[k-1][j][k])
// 第二个方程中的min，常换成max、与、或之类表示其它含义的DP。

// d[u][v]: <u,v>边的权值(没有的边为inf,<u,u>为0)
// path[i][j]: 从i到j的最短路的第一步是由i向path[i][j]走
int n, d[maxn][maxn], path[maxn][maxn];

void floyd_warshall()
{
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < n; ++j)
            path[i][j] = j;

    for(int k = 0; k < n; ++k)
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < n; ++j)
                if(d[i][j] > d[i][k] + d[k][j]) {
                    d[i][j] = d[i][k] + d[k][j];
                    path[i][j] = path[i][k];
                }
}

void output_path(int u, int v)
{
    for(int p = u; p != v; p = path[p][v])
        printf("%d ", p);
    printf("%d\n", v);
}
