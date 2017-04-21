// POJ No.1459 Ombrophobic Bovines Dinic (432K 79MS)
#include <cstdio>
#include <cstring>
using namespace std;
const int maxn = 110;
const int inf = 0x3f3f3f3f;
#define min(a, b) ((a) < (b) ? (a) : (b))

int s, t;
int n, np, nc, m;
int cur[maxn];
int lv[maxn];
int r[maxn][maxn];
int qf, qb, que[maxn];

int bfs()
{
    qf = qb = 0;
    memset(lv, -1, sizeof(lv));
    lv[s] = 0;
    que[qb++] = s;
    while(qf < qb && lv[t] == -1) {
        int u = que[qf++];
        for(int i = 0; i <= t; ++i)
            if(lv[i] == -1 && r[u][i] > 0)
                lv[i] = lv[u] + 1, que[qb++] = i;
    }
    return lv[t] != -1;
}

int dfs(int u, int low)
{
    int a;
    if(u == t) return low;
    for(int &i = cur[u]; i <= t; ++i)
        if(r[u][i]>0 && lv[i]==lv[u]+1 && (a=dfs(i, min(low,r[u][i])))) {
            r[u][i] -= a, r[i][u] += a;
            return a;
        }
    return 0;
}

int dinic()
{
    int tmp, ans = 0;
    while(bfs()) {
        memset(cur, 0, sizeof(cur));
        while(tmp = dfs(s, inf))
            ans += tmp;
    }
    return ans;
}

int main()
{
    int u, v, w;

    while(~scanf("%d%d%d%d", &n, &np, &nc, &m)) {
        s = 0, t = n + 1;
        memset(r, 0, sizeof(r));
        for(int i = 0; i < m; ++i) {
            // 格式前要有一个空格，这样才会跳过之前的空白符号
            scanf(" (%d,%d)%d", &u, &v, &w);    
            r[++u][++v] = w;
        }
        for(int i = 0; i < np; ++i) {
            scanf(" (%d)%d", &u, &w);
            r[s][++u] = w;
        }
        for(int i = 0; i < nc; ++i) {
            scanf(" (%d)%d", &u, &w);
            r[++u][t] = w;
        }
        printf("%d\n", dinic());
    }
}
