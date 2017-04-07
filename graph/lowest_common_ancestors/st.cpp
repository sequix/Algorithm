// 倍增法在线求LCA，初始化(NlogN)，查询O(logH)
// N		节点数，编号从1到N
// MAX_N	最大节点数
struct Edge { int to; Edge *next; };

int ind[MAX_N+5];	// 入度表，为找树的根
int dep[MAX_N+5];	// 每个节点的深度
// anc[i][j] i点的2^j倍祖先，i的父是其1倍祖先，父的父为2倍，...
int anc[MAX_N+5][floor(log(MAX_N)) + 1];

// O(N) 深搜预处理出dep和anc[i][0]
void dfs(int u)
{
	for(Edge *p = T[u]; p; p = p->next) {
		if(dep[p->to] == 0) {
			dep[p->to] = dep[u] + 1;
			anc[p->to][0] = u;
			dfs(p->to);
		}
	}
}

// O(NlogN) 初始化anc[][]
void init()
{
	for(int i = 1; i <= N; ++i)
		if(ind[i] == 0) { dfs(i); break; }
	for(int j = 1; (1 << j) <= N; ++j) {
		for(int i = 1; i <= N; ++i)
			if(anc[i][j-1] != 0)
				anc[i][j] = anc[anc[i][j-1]][j-1];
	}
}

// O(logH) 查询一对节点的LCA，H为树高
int lca(int a, int b)
{
	int i, j;
	if(dep[a] < dep[b]) swap(a, b);
	for(i = 0; (1 << i) < dep[a]; ++i);

	// 将较深节点a上升到与b同层
	for(j = i; j >= 0; --j)
		if(dep[anc[a][j]] >= dep[b])
			a = anc[a][j];
	if(a == b) return a;

	// 每次向上进2^j深度，找最近公共祖先的子结点
	for(j = i; j >= 0; --j)
		if(anc[a][j] != 0 && anc[a][j] != anc[b][j])
			a = anc[a][j], b = anc[b][j];
	return anc[a][0];
}
