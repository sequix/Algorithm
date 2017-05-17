// HDU No.3974 Assign the task (312ms 3536kB)
// 给一棵树，每次可对一子树染色、询问某结点颜色。
// 以dfs给每个结点编号start[u]，并记录该结点能到达的结点
// 的编号end[u]，那么每次染色操作变为对[start[u], end[u]]的
// 区间操作，线段树解决
#include <cstdio>
#include <cstring>
using namespace std;
const int maxn = 5e4 + 10;
const int maxnode = maxn << 2;
#define lc(o) (((o)<<1)+1)
#define rc(o) (((o)<<1)+2)

struct {
    int qL, qR, qV, qP;
    int work[maxnode], setv[maxnode];
    int L[maxnode], R[maxnode], M[maxnode];

    void build(int o, int l, int r) {
        if(l == r) {
            work[o] = setv[o] = -1;
            M[o] = L[o] = R[o] = l;
            return;
        }
        L[o] = l, R[o] = r;
        M[o] = (l + r) >> 1;
        work[o] = setv[o] = -1;
        build(lc(o), l, M[o]);
        build(rc(o), M[o]+1, r);
    }
    void pushdown(int o) {
        if(setv[o] >= 0 && L[o] != R[o]) {
            setv[lc(o)] = setv[rc(o)] = setv[o];
            setv[o] = -1;
        }
    }
    void maintain(int o) {
        if(L[o] != R[o] && work[lc(o)] == work[rc(o)])
            work[o] = work[lc(o)];
        if(setv[o] >= 0)
            work[o] = setv[o];
    }
    void update(int o) {
        if(qL <= L[o] && R[o] <= qR) {
            setv[o] = qV;
        } else {
            pushdown(o);
            if(qL <= M[o]) update(lc(o)); else maintain(lc(o));
            if(qR > M[o]) update(rc(o)); else maintain(rc(o));
        }
        maintain(o);
    }
    int query(int o) {
        if(setv[o] >= 0) {
            return setv[o];
        } else if(L[o] == qP && qP == R[o]) {
            return work[o];
        } else {
            if(qP <= M[o]) return query(lc(o));
            else return query(rc(o));
        }
    }
} tree;

int n, m, dfscnt;
bool isroot[maxn];
int start[maxn], end[maxn];

int egc, head[maxn];
struct edge { int v, next; } eg[maxn];

void addedge(int u, int v)
{
    eg[egc] = (edge){ v, head[u] }; head[u] = egc++;
}

void dfs(int u)
{
    ++dfscnt;
    start[u] = dfscnt;
    for(int p = head[u]; ~p; p = eg[p].next)
        dfs(eg[p].v);
    end[u] = dfscnt;
}

int main()
{
    char c[2];
    int T, u, v;

    scanf("%d", &T);
    for(int kase = 1; kase <= T; ++kase) {
        printf("Case #%d:\n", kase);
        egc = 0;
        memset(head, -1, sizeof(head));
        memset(isroot, 1, sizeof(isroot));

        scanf("%d", &n);
        for(int i = 1; i < n; ++i) {
            scanf("%d%d", &v, &u);
            addedge(u, v);
            isroot[v] = 0;
        }

        dfscnt = 0;
        for(int i = 1; i <= n; ++i)
            if(isroot[i]) { dfs(i); break; }
        tree.build(0, 1, dfscnt);
        
        for(scanf("%d", &m); m; --m) {
            scanf("%s", c);
            if(c[0] == 'T') {
                scanf("%d%d", &u, &tree.qV);
                tree.qL = start[u], tree.qR = end[u];
                tree.update(0);
            } else {
                scanf("%d", &u);
                tree.qP = start[u];
                printf("%d\n", tree.query(0));
            }
        }
    }
}
