// 这里实现出边表

// maxn 最大点数
// maxm 最大边数

// 边数
int egc;

// 邻接表的表头
int head[maxn];

struct edge {
    int v;      // 该条边指向哪点
    int w;      // 该条边的权值
    int next;   // 指向邻接表下一条边
} eg[maxm];

void init()
{
    egc = 0;
    memset(head, ~0, sizeof(head));
}

void iterate(int u)
{
    for(int p = head[u]; ~p; p = eg[p].next)
        printf("%d---(%d)--->%d\n", u, eg[p].w, eg[p].v);
}

// 同样地，对二分图，邻接表也仅保存从x到y的边
