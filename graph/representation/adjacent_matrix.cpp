// graph[i][j] 代表点i和点j是否连通
bool graph[maxn][maxn];

// graph[i][j] 代表边<i,j>权值
int graph[maxn][maxn];

// 对二分图，bipartite_graph[][]仅保存从x到y的边
// 且x和y的编号可以重复
int bipartite_graph[maxx][maxy]
