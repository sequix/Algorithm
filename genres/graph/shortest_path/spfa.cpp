// spfa: 单源最短路 + 负环判断

int egc, head[maxn];
struct edge { int v, w, next; } eg[maxm];

int n;
int d[maxn];
int cnt[maxn];
bool inq[maxn];

// 存在负环返回1，不存在0
bool spfa(int s)
{
    queue<int> que;

    memset(d, inf, sizeof(d));
    d[s] = 0;
    que.push(s);
    inq[s] = 1;

    while(!que.empty()) {
        int u = que.front();
        que.pop();

        inq[u] = 0;
        if(++cnt[u] >= V)
            return 1;

        for(int p = head[u]; p != -1; p = eg[p].next) {
            edge &e = eg[p];
            if(d[e.v] > d[u] + e.w) {
                d[e.v] = d[u] + e.w;
                if(!inq[e.v]) que.push(e.v), inq[e.v] = 1;
            }
        }
    }
    return 0;
}
