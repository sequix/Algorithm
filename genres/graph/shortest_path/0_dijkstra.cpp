//// Dijkstra
int n;
int d[maxn];
int egc, head[maxn];
struct edge { int v, w, next; } eg[maxm];

void dijkstra(int s)
{
    typedef pair<int, int> P;
	priority_queue<P, vector<P>, greater<P> > que;

	memset(d, inf, sizeof(d));
	d[s] = 0;
	que.push(P(0, s));

	while(!que.empty()) {
		P p = que.top(); que.pop();
		int u = p.second;
		if(d[u] < p.first) continue;    // 某些已达最短路径的点会重复入队
        for(int p = head[u]; p != -1; p = eg[p].next) {
			edge &e = eg[p];
			if(d[e.v] > d[u] + e.w) {
				d[e.v] = d[u] + e.w;
				que.push(P(d[e.v], e.v));
			}
		}
	}
}

//// 最原始版，当程序复杂时，用这个
void dijkstra(int s)
{
    memset(d, -1, sizeof(d));
    d[s] = 0;

    for(int p = head[s]; p != -1; p = eg[p].next) {
        edge &e = eg[p];
        d[e.v] = e.w;
    }

    for(int i = 1; i < n; ++i) {
        int mind = inf, u = -1;

        for(int i = 0; i < n; ++i) {
            if(d[i] != -1 && d[i] < mind)
                mind = d[i], u = i;
        }

        for(int p = head[u]; p != -1; p = eg[p].next) {
            if(d[eg[p].v] > d[u] + eg[p].w)
                d[e.v] = d[u] + eg[p].w;
        }
    }
}
