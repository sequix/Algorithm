// POJ No.2516 最小费用流 (692K 375MS)
#include <queue>
#include <cstdio>
#include <cstring>
using namespace std;
const int maxn = 110;
const int inf = 0x3f3f3f3f;

int N, M, K, s, t;
int suply[51][51];
int order[51][51];
int dis[maxn];
int aug[maxn];
int pre[maxn];
int cap[maxn][maxn];
int cost[maxn][maxn];

int spfa()
{
    queue<int> que;
    bool inq[maxn] = {0};
    for(int i = s; i <= t; ++i) dis[i] = inf;

    que.push(s);
    inq[s] = 1;
    dis[s] = 0;
    pre[s] = -1;
    aug[s] = inf;
    aug[t] = 0;

    while(!que.empty()) {
        int u = que.front(); que.pop();
        inq[u] = 0;
        for(int v = s; v <= t; ++v) {
            if(cap[u][v] > 0 && dis[v] > dis[u] + cost[u][v]) {
                dis[v] = dis[u] + cost[u][v];
                pre[v] = u;
                aug[v] = min(aug[u], cap[u][v]);
                if(!inq[v]) que.push(v), inq[v] = 1;
            }
        }
    }
    return aug[t];
}

int mcf()
{
    int a, ans = 0;

    while(a = spfa()) {
        ans += a * dis[t];
        for(int p = t; ~p; p = pre[p])
            cap[pre[p]][p] -= a, cap[p][pre[p]] += a;
    }
    return ans;
}

int main()
{
    int valid, ans;

    while(scanf("%d%d%d", &N, &M, &K)==3 && N+M+K) {
        ans = 0;
        valid = 1;
        s = 0;
        t = N + M + 1;

        for(int i = 1; i <= N; ++i)
            for(int j = 1; j <= K; ++j)
                scanf("%d", &order[i][j]);

        for(int i = 1; i <= M; ++i)
            for(int j = 1; j <= K; ++j)
                scanf("%d", &suply[i][j]);

        for(int i = 1; i <= K; ++i) {
            int s = 0, o = 0;
            for(int j = 1; j <= N; ++j) o += order[j][i];
            for(int j = 1; j <= M; ++j) s += suply[j][i];
            if(s < o) { valid = 0; break; }
        }

        // 对每个物品都求一次最小费用流
        for(int k = 1; k <= K; ++k) {
            if(valid) {
                for(int i = s; i <= t; ++i)
                    for(int j = s; j <= t; ++j)
                        cost[i][j] = cap[i][j] = 0;
            }

            for(int i = M+1; i <= N+M; ++i) {
                for(int j = 1; j <= M; ++j) {
                    scanf("%d", &cost[j][i]);
                    if(valid) {
                        cap[j][i] = inf;
                        cost[i][j] = -cost[j][i];
                    }
                }
            }
            if(!valid) continue;
            for(int i = 1; i <= M; ++i)
                cap[s][i] = suply[i][k];
            for(int i = M+1; i <= M+N; ++i)
                cap[i][t] = order[i-M][k];
            ans += mcf();
        }

        printf("%d\n", valid ? ans : -1);
    }
}
