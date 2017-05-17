// HDU No.3335 Divisibility (二分图的点独立数) (0MS 1604K)
// 选仅可能多的整数，满足每两个之间不能整除。
// 对每对整除关系间建边，相当与求最大点独立集
// 考虑到图中没有环，即该无向图为二分图
// 二分图中有：点独立 = 边覆盖
// 而对任一图又有：边独立(匹配) + 边覆盖 = 点数
// 所以答案即为点数 - 匹配数
// 注意这里对与无向图进行二分匹配时，仅需要match[]
// 不需要cx, cy
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 1e3 + 10;

int T, n;
LL A[maxn];
bool vis[maxn];
int match[maxn];
int egc, head[maxn];
struct edge { int v, next; } eg[maxn*maxn];

void addedge(int u, int v)
{
    eg[egc] = (edge){v, head[u]}, head[u] = egc++;
    eg[egc] = (edge){u, head[v]}, head[v] = egc++;
}

int dfs(int x)
{
    for(int p = head[x]; ~p; p = eg[p].next) {
        int y = eg[p].v;
        if(!vis[y]) {
            vis[y] = 1;
            if(match[y] == -1 || dfs(match[y])) {
                match[y] = x, match[x] = y;
                return 1;
            }
        }
    }
    return 0;
}

int maxmatch()
{
    int ans = 0;
    memset(match, -1, sizeof(match));
    for(int i = 0; i < n; ++i) {
        if(match[i] == -1) {
            memset(vis, 0, sizeof(vis));
            ans += dfs(i);
        }
    }
    return ans;
}

int main()
{
    for(scanf("%d", &T); T > 0; --T) {
        egc = 0;
        memset(head, -1, sizeof(head));

        scanf("%d", &n);
        for(int i = 0; i < n; ++i)
            scanf("%lld", &A[i]);

        sort(A, A + n);
        n = unique(A, A + n) - A;

        for(int i = 0; i < n; ++i)
            for(int j = i + 1; j < n; ++j)
                if(A[j] % A[i] == 0) addedge(i, j);
        printf("%d\n", n - maxmatch());
    }
}
