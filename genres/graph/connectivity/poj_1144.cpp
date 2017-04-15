// POJ No.1144 Network (Tarjan求割点个数) (1396K 16MS)
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 110;

int egc, head[maxn];
struct edge { int v, next; } eg[maxn*maxn];

void addedge(int u, int v)
{
    eg[egc] = (edge){v, head[u]}, head[u] = egc++;
    eg[egc] = (edge){u, head[v]}, head[v] = egc++;
}

int n, root;
char buf[BUFSIZ];
bool vis[maxn];
bool is_cut_vertex[maxn];
int dfn[maxn], low[maxn];

void dfs(int u, int f, int dep)
{
    int ns = 0;
    vis[u] = 1;
    low[u] = dfn[u] = dep;

    for(int p = head[u]; ~p; p = eg[p].next) {
        int v = eg[p].v;
        if(!vis[v]) {
            ++ns;
            dfs(v, u, dep+1);
            low[u] = min(low[u], low[v]);
            if((u==root && ns>1) || (u!=root && low[v]>=dfn[u]))
                is_cut_vertex[u] = 1;
        } else if(v != f) {
            low[u] = min(low[u], dfn[v]);
        }
    }
}

int main()
{
    int nn, u, v, c, ans;

    while(scanf("%d", &n) == 1 && n) {
        egc = 0;
        memset(head, -1, sizeof(head));
        memset(vis, 0, sizeof(vis));
        memset(is_cut_vertex, 0, sizeof(is_cut_vertex));

        while(1) {
            while(isspace(c = getchar()));
            ungetc(c, stdin);
            fgets(buf, sizeof(buf), stdin);
            sscanf(buf, "%d", &u);
            if(u == 0) break;

            char *p = strtok(buf, " ");
            p = strtok(NULL, " ");
            while(p) {
                sscanf(p, "%d", &v);
                addedge(u, v);
                p = strtok(NULL, " ");
            }
        }

        root = 1;
        dfs(1, -1, 0);
        ans = count(is_cut_vertex+1, is_cut_vertex+n+1, 1);
        printf("%d\n", ans);
    }
}
