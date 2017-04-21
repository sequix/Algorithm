// HDU No.3018 给一个图，问几笔可以将其画完 (140MS 3140K)
// 对一个连通图来说，所需笔画数 = 图中奇点数 / 2
#include <bits/stdc++.h>
using namespace std;
const int MAXV = 100005;

int V, E;
int vis[MAXV];      // vis[i] 是否已经加过i所在连通快的笔画数
int deg[MAXV];
int par[MAXV];
int oddcnt[MAXV];

void init()
{
    for(int i = 1; i <= V; ++i) {
        par[i] = i;
        vis[i] = deg[i] = oddcnt[i] = 0;
    }
}

int getpar(int x)
{
    if(x != par[x])
        par[x] = getpar(par[x]);
    return par[x];
}

int main()
{
    int u, v;

    while(~scanf("%d%d", &V, &E)) {
        init();

        for(int i = 0; i < E; ++i) {
            scanf("%d%d", &u, &v);
            ++deg[u], ++deg[v];
            par[getpar(u)] = getpar(v);
        }

        for(int i = 1; i <= V; ++i)
            if(deg[i] & 1) ++oddcnt[getpar(i)];

        int ans = 0;
        for(int i = 1; i <= V; ++i) {
            if(deg[i] == 0) continue;   // 排除孤立点
            if(vis[getpar(i)]) continue;
            if(oddcnt[getpar(i)] == 0)  // 没有奇点，代表有欧拉回路
                ++ans;
            else
                ans += oddcnt[getpar(i)] / 2;
            vis[getpar(i)] = 1;
        }
        printf("%d\n", ans);
    }
}
