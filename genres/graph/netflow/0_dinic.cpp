// Dinic 求最大流 O(V^2 * E)
// 通过BFS在残留网络上建立层次网络，再用DFS增广，
// 每次DFS又通过回溯可实现一次DFS调用，增广多条增广路
// 循环执行以上两步，直到无增广路，即无连通源汇点的层次网络为止

// 邻接表写法 + 当前弧优化
/*
 * 当前弧优化是记录当前访问弧，下次访问直接从此处开始。
 * 多路增广只不过是没有记录，直接一气呵成罢了。
 * 两个都是同一剪枝思路。
 */
int s, t;               // 源汇点
int lv[maxn];           // 点的层次
int cur[maxn];          // 当前弧优化
int egc, head[maxn];    // 邻接表
int qf, qb, que[maxn];
struct edge { int v, c, next; } eg[maxm];

void add(int u, int v, int c)
{
    eg[egc] = (edge){v, c, head[u]}; head[u] = egc++;
    eg[egc] = (edge){u, 0, head[v]}; head[v] = egc++;
}

int bfs()
{
    qf = qb = 0;
    memset(lv, -1, sizeof(lv));
    lv[s] = 0;
    que[qb++] = s;
    while(qf < qb && lv[t] == -1) {
        int u = que[qf++];
        for(int p = head[u]; p != -1; p = eg[p].next)
            if(lv[eg[p].v] == -1 && eg[p].c > 0)
                lv[eg[p].v] = lv[u]+1, que[qb++] = eg[p].v;
    }
    return lv[t] != -1;
}

int dfs(int u, int low)
{
    int a;
    if(u == t) return low;
    for(int &p = cur[u]; p != -1; p = eg[p].next) { // 当前弧优化
        int v = eg[p].v, c = eg[p].c;
        if(lv[v]==lv[u]+1 && c > 0 && (a=dfs(v, min(low,c)))) {
            eg[p].c -= a, eg[p^1].c += a;
            return a;
        }
    }
    return 0;
}

int dinic()
{
    int tmp, ans = 0;
    while(bfs()) {
        memcpy(cur, head, sizeof(head));
        while(tmp = dfs(s, inf))
            ans += tmp;
    }
    return ans;
}
