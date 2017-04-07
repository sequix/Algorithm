// prim 不加堆适合稠密图，加堆适合稀疏图（加堆常和邻接表一起使用）


// 稠密图：邻接阵 O(V^2) (理解用模板)
int V, E;
int mincost[MAX_V];	// mincost[i] MST到不在MST中顶点i的最短距离
int nearvex[MAX_V];	// nearvex[i] 离不在MST中顶点i中最近的MST中顶点
int G[MAX_V][MAX_V];

int prim(int src)
{
	int sumweight = 0;

	for(int i = 0; i < V; ++i) {
		mincost[i] = G[src][i];
		nearvex[i] = src;
	}
	nearvex[src] = -1;	// -1 表示该顶点已在MST中

	for(int i = 1; i < V; ++i) {	// 一共需要V个顶点，src已入树所以i = 1
		int minc = INF, v = -1;
		// 找不在MST中，距当前MST权值最小的顶点
		for(int j = 0; j < V; ++j)
			if(nearvex[j] != -1 && mincost[j] < minc)
				minc = mincost[j], v = j;
		if(v != -1) {	// v==-1 则没找到权值最小边，即图不联通
			printf("%d --%d--> %d\n", nearvex[v], minc, v);
			nearvex[v] = -1;
			sumweight += minc;
			// 更新新添加顶点的相邻顶点
			for(int j = 0; j < V; ++j) {
				if(nearvex[j] != -1 && G[v][j] < mincost[j]) {
					mincost[j] = G[v][j];
					nearvex[j] = v;
				}
			}
		}
	}
	return sumweight;
}

// 仅求树权：去掉nearvex，mincost[i]为-1表示顶点i已在树中
int prim(int src)
{
	int sumweight = 0;

	for(int i = 0; i < V; ++i)
		mincost[i] = G[src][i];
	mincost[src] = -1;

	for(int i = 1; i < V; ++i) {

		int minc = INF, v = -1;
		for(int j = 0; j < V; ++j)
			if(mincost[j] != -1 && mincost[j] < minc)
				minc = mincost[j], v = j;

		if(v != -1) {
			mincost[v] = -1;
			sumweight += minc;
			for(int j = 0; j < V; ++j)
				if(mincost[j] != -1 && G[v][j] < mincost[j])
					mincost[j] = G[v][j];
		}
	}
	return sumweight;
}


// 稀疏图：邻接表+堆 O(ElgV)
// 假设图是联通的，并且仅求树权
struct P {
	int from, to, weight;
	P(int f=0, int t=0, int w=0): from(f), to(t), weight(w) {}
	bool operator > (const P &p) const { return weight > p.weight; }
};
struct Edge { int to, cost; };

int V;
vector<Edge> G[MAX_V];

int prim(int src)
{
	int cnt = 0;			// 已在MST中的顶点数
	int sumweight = 0;		// 总权值
	bool used[MAX_V] = {0};	// used[i] 顶点i是否已经在树中
	priority_queue<P, vector<P>, greater<P> > que;

	que.push(P(src, src, 0));

	while(cnt < V && !que.empty()) {
		P p = que.top(); que.pop();
		if(used[p.to]) continue;
		if(p.from != p.to)
			printf("%d --%d--> %d\n", p.from, p.weight, p.to);
		++cnt;
		used[p.to] = true;
		sumweight += p.weight;
		for(int i = 0; i < G[p.to].size(); ++i)
			que.push(P(p.to, G[p.to][i].to, G[p.to][i].cost));
	}
	return sumweight;
}

// 仅求树权
typedef pair<int, int> P;	// first表示当前MST距second点权值 second表示节点编号

int prim(int src)
{
	int cnt = 0;			// 已在MST中的顶点数
	int sumweight = 0;		// 总权值
	bool used[MAX_V] = {0};	// used[i] 顶点i是否已经在树中
	priority_queue<P, vector<P>, greater<P> > que;

	que.push(P(0, src));

	while(cnt < V && !que.empty()) {
		P p = que.top(); que.pop();
		int u = p.second;
		if(used[u]) continue;
		++cnt;
		used[u] = true;
		sumweight += p.first;
		for(int i = 0; i < G[u].size(); ++i)
			que.push(P(G[u][i].cost, G[u][i].to));
	}
	return sumweight;
}
