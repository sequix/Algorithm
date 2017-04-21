// POJ No.1129 Channel Allocation (四色定理) (388K 0MS)
// 给一个无向图，问其染色数。
#include <cstdio>
#include <cstring>
using namespace std;
const int maxn = 30;

int n;
char used[maxn];    // 用以标记每个点的临界点已用的颜色
char col[maxn];     // 每个点的的颜色，颜色从1开始
char buf[maxn];
char G[maxn][maxn];

int main()
{
    int u, v;
    while(scanf("%d", &n) == 1 && n) {
        memset(G, 0, sizeof(G));
        memset(col, 0, sizeof(col));
        for(int j = 0; j < n; ++j) {
            scanf("%s", &buf);
            u = buf[0] - 'A'; 
            for(int i = 2; buf[i]; ++i) {
                v = buf[i] - 'A';
                G[u][v] = G[v][u] = 1;
            }
        }
        int ans = 0;
        for(int u = 0; u < n; ++u) {
            memset(used, 0, sizeof(used));
            for(int v = 0; v < n; ++v)
                if(G[u][v] && col[v]) used[col[v]] = 1;
            for(int i = 1; i <= maxn; ++i)
                if(!used[i]) { col[u] = i; break; }
            ans = col[u] > ans ? col[u] : ans;
            if(ans >= 4) break;
        }
        printf("%d channel%s needed.\n", ans, ans > 1 ? "s" : "");
    }
}
