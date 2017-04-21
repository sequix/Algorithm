// POJ No.1043 在补图（也一个二分图）上找完美匹配的边 (396K 47MS)
// 如果按log顺序处理，每发出一条信息，
// 连接在hideout中的name与信息显示的id，当有人离开发现矛盾再
// 删除边这样的策略的话，可能被漏掉的情况很多，
// 因为有人可能没有发出信息，即有的id不会显示在log中。
// 所以在最初以完全二分图开始，逐步删除不合理的边，得到其补图
//
// 因为id与name是一一对应的，其实也就是说图应该有唯一的完全匹配，
// 匹配数为n。确定每个name对于的id的方法是：
// 遍历与name相接的每条边，如果去掉该条边，
// 剩余图的最大匹配数小于n，说明这条边一定是唯一完全匹配中的，
// 即与该name匹配的id可以确定，否则无法确定。
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 21;

int n, namecnt;
int ans[maxn];
int order[maxn];
char id[maxn][maxn];
char name[maxn][maxn];
bool in_hideout[maxn];

int cx[maxn];
int cy[maxn];
bool vis[maxn];
bool G[maxn][maxn];

int dfs(int x)
{
    for(int y = 0; y < n; ++y) {
        if(G[x][y] && !vis[y]) {
            vis[y] = 1;
            if(cy[y] == -1 || dfs(cy[y])) {
                cx[x] = y, cy[y] = x;
                return 1;
            }
        }
    }
    return 0;
}

int maxmatch()
{
    int ans = 0;
    memset(cx, -1, sizeof(cx));
    memset(cy, -1, sizeof(cy));
    for(int x = 0; x < n; ++x) {
        if(cx[x] == -1) {
            memset(vis, 0, sizeof(vis));
            ans += dfs(x);
        }
    }
    return ans;
}

bool cmp(int a, int b)
{
    return strcmp(name[a], name[b]) <= 0;
}

int main()
{
    int x, y;
    char cmd, buf[maxn];
    memset(ans, -1, sizeof(ans));
    memset(G, 1, sizeof(G));

    scanf("%d", &n);
    for(int i = 0; i < n; ++i)
        scanf("%s", &id[i]);
    while(scanf(" %c", &cmd) != EOF && cmd != 'Q') {
        if(cmd == 'E') {
            scanf("%s", &buf);
            for(x = 0; x < namecnt && strcmp(buf, name[x]); ++x);
            if(x == namecnt) strcpy(name[namecnt++], buf);
            in_hideout[x] = 1;
        } else if(cmd == 'L') {
            scanf("%s", &buf);
            for(x = 0; strcmp(buf, name[x]); ++x);
            in_hideout[x] = 0;
        } else {
            scanf("%s", &buf);
            for(y = 0; strcmp(buf, id[y]); ++y);
            for(int x = 0; x < n; ++x)
                if(!in_hideout[x]) G[x][y] = 0;
        }
    }

    for(x = 0; x < n; ++x) {
        for(y = 0; y < n; ++y) {
            if(G[x][y]) {
                G[x][y] = 0;
                if(maxmatch() < n) {
                    G[x][y] = 1;
                    ans[x] = y;
                    break;
                }
                G[x][y] = 1;
            }
        }
    }

    // 按字典序输出，且避免复制的技巧
    for(int i = 0; i < n; ++i) order[i] = i;
    sort(order, order + n, cmp);

    for(int i = 0; i < n; ++i) {
        printf("%s:", name[order[i]]);
        if(ans[order[i]] == -1)
            puts("???");
        else
            printf("%s\n", id[ans[order[i]]]);
    }
}
