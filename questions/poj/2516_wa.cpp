// POJ No.2516 最小费用流
// 建图错误，以供给物品和索要物品建2k个点，会造成大量平行边而
// 临近阵无法表示平行边
#include <queue>
#include <cstdio>
#include <cstring>
using namespace std;
const int maxn = 150;
const int inf = 0x3f3f3f3f;

int n, m, k, s, t;
int ksuply[51];
int korder[51];
int suply[51][51];
int h[maxn];
int dis[maxn];
int aug[maxn];
int pre[maxn];
int cap[maxn][maxn];
int cost[maxn][maxn];

void add(int u, int v, int r, int c)
{
    cap[u][v] = r, cost[u][v] = c;
    cap[v][u] = 0, cost[v][u] = -c;
}

int dijkstra()
{
    typedef pair<int, int> P;
    priority_queue<P, vector<P>, greater<P> > que;
    for(int i = s; i <= t; ++i) dis[i] = inf;

    que.push(P(0, s));
    dis[s] = 0;
    aug[s] = inf;
    aug[t] = 0;
    pre[s] = -1;

    while(!que.empty()) {
        P p = que.top(); que.pop();
        int u = p.second;
        if(dis[u] < p.first) continue;
        for(int v = s; v <= t; ++v) {
            if(cap[u][v] <= 0) continue;
            if(dis[v] > dis[u] + cost[u][v] + h[u] - h[v]) {
                dis[v] = dis[u] + cost[u][v] + h[u] - h[v];
                pre[v] = u;
                aug[v] = min(aug[u], cap[u][v]);
                que.push(P(dis[v], v));
            }
        }
    }
    for(int i = s; i <= t; ++i)
        h[i] += dis[i];
    return aug[t];
}

int mcf(int total_order)
{
    int a;
    int f = 0;
    int ans = 0;
    memset(h, 0, sizeof(h));

    while(a = dijkstra()) {
        f += a;
        ans += a * dis[t];
        for(int p = t; ~p; p = pre[p])
            cap[pre[p]][p] -= a, cap[p][pre[p]] += a;
        if(f >= total_order) break;
    }
    return f >= total_order ? ans : -1;
}

int main()
{
    int x, total_order, valid;

    while(scanf("%d%d%d", &n, &m, &k)==3 && n+m+k) {
        memset(suply, 0, sizeof(suply));
        memset(ksuply, 0, sizeof(ksuply));
        memset(korder, 0, sizeof(korder));

        valid = 1;
        s = 0;
        t = 2 * k + 1;
        total_order = 0;

        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < k; ++j) {
                scanf("%d", &x);
                korder[j] += x;
                total_order += x;
            }
        }
        for(int i = 0; i < m; ++i) {
            for(int j = 0; j < k; ++j) {
                scanf("%d", &suply[i][j]);
                ksuply[j] += suply[i][j];
            }
        }

        for(int i = 0; i < k; ++i)
            if(ksuply[i] < korder[i]) { valid = 0; break; }

        for(int l = 0; l < k; ++l) {
            for(int i = 0; i < n; ++i) {
                for(int j = 0; j < m; ++j) {
                    scanf("%d", &x);
                    if(!valid) continue;
                    add(l+1, k+l+1, suply[j][l], x);
                    printf("%d %d %d %d\n", l+1, k+l+1, suply[j][l], x);
                }
            }
        }

        if(valid) {
            for(int i = 0; i < k; ++i) {
                add(s, i+1, ksuply[i], 0);
                printf("%d %d %d %d\n", s, i+1, ksuply[i], 0);
                add(k+i+1, t, korder[i], 0);
                printf("%d %d %d %d\n", k+i+1, t, korder[i], 0);
            }
            printf("%d\n", mcf(total_order));
        } else {
            puts("-1");
        }
    }
}
