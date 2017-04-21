// POJ No.1149 Edmonds-Karp 求最大流 (428K 0MS)
// 网络中流动的是猪（要求的也是猪的数量）
// 源点、汇点另建
// 网络中的点是顾客，猪流向顾客
#include <cstdio>
#include <cstring>
using namespace std;
const int maxm = 1005;
const int maxn = 105;
const int inf = 0x3f3f3f3f;
#define min(a, b) ((a) < (b) ? (a) : (b))

int n, m, s, t;
int pre[maxn];
int R[maxn][maxn];
int qf, qb, que[maxn];

void init()
{
    int num, k;             // 钥匙数，当前钥匙 
    int house[maxm] = {0};  // 每个猪圈的猪数
    int last[maxm] = {0};   // 每个猪圈前一个顾客的序号

    scanf("%d%d", &m, &n);
    s = 0, t = n + 1;
    for(int i = 1; i <= m; ++i)
        scanf("%d", &house[i]);
    for(int i = 1; i <= n; ++i) {
        scanf("%d", &num);
        for(int j = 0; j < num; ++j) {
            scanf("%d", &k);
            if(last[k] == 0)    // 第k个圈的第一个顾客
                R[s][i] += house[k];
            else    // 因为每次打开圈，都可以调整，所以流量无限制
                R[last[k]][i] = inf;
            last[k] = i;
        }
        scanf("%d", &R[i][t]);
    }
}

int bfs()
{
    qf = qb = 0;
    memset(pre, -1, sizeof(pre));

    pre[s] = s;
    que[qb++] = s;

    while(qf < qb) {
        int u = que[qf++];
        if(u == t) return 1;
        for(int i = 0; i <= t; ++i)
            if(R[u][i] > 0 && pre[i] == -1)
                pre[i] = u, que[qb++] = i;
    }
    return 0;
}

void solve()
{
    int maxflow = 0;

    while(bfs()) {
        int d = inf;
        for(int i = t; i != s; i = pre[i])
            d = min(d, R[pre[i]][i]);
        for(int i = t; i != s; i = pre[i])
            R[pre[i]][i] -= d, R[i][pre[i]] += d;
        maxflow += d;
    }
    printf("%d\n", maxflow);
}

int main()
{
    init();
    solve();
}
