#if 0
1459 迷宫游戏
基准时间限制：1 秒 空间限制：131072 KB 分值: 0 难度：基础题
你来到一个迷宫前。该迷宫由若干个房间组成，每个房间都有一个得分，第一次进入这个房间，你就可以得到这个分数。还有若干双向道路连结这些房间，你沿着这些道路从一个房间走到另外一个房间需要一些时间。游戏规定了你的起点和终点房间，你首要目标是从起点尽快到达终点，在满足首要目标的前提下，使得你的得分总和尽可能大。现在问题来了，给定房间、道路、分数、起点和终点等全部信息，你能计算在尽快离开迷宫的前提下，你的最大得分是多少么？
Input

第一行4个整数n (<=500), m, start, end。n表示房间的个数，房间编号从0到(n - 1)，m表示道路数,任意两个房间之间最多只有一条道路，start和end表示起点和终点房间的编号。
第二行包含n个空格分隔的正整数(不超过600)，表示进入每个房间你的得分。
再接下来m行，每行3个空格分隔的整数x, y, z (0<z<=200)表示道路,表示从房间x到房间y(双向)的道路,注意，最多只有一条道路连结两个房间, 你需要的时间为z。
输入保证从start到end至少有一条路径。

Output

一行，两个空格分隔的整数，第一个表示你最少需要的时间，第二个表示你在最少时间前提下可以获得的最大得分。

Input示例

3 2 0 2
1 2 3
0 1 10
1 2 11

Output示例

21 6
#endif

#include <bits/stdc++.h>
using namespace std;
const int maxn = 550;
const int inf = 0x3f3f3f3f;

int n, m, ss, ee;

bool vis[maxn];
int dis0[maxn];
int dis1[maxn];
int pv[maxn];
int egc, head[maxn];
struct edge { int v, w, next; } eg[maxn*maxn];

void addedge(int u, int v, int w)
{
    eg[egc] = (edge){v, w, head[u]};
    head[u] = egc++;

    eg[egc] = (edge){u, w, head[v]};
    head[v] = egc++;
}

void dijkstra()
{
    memset(dis0, inf, sizeof(dis0));
    vis[ss] = 1;
    dis0[ss] = 0;
    dis1[ss] = pv[ss];

    for(int p = head[ss]; p != -1; p = eg[p].next) {
        edge &e = eg[p];
        dis0[e.v] = e.w;
        dis1[e.v] = dis1[ss] + pv[e.v];
    }

    for(int i = 1; i < n; ++i) {
        int minn = inf, u = -1;

        for(int j = 0; j < n; ++j) {
            if(!vis[j] && dis0[j] < minn) {
                minn = dis0[j];
                u = j;
            }
        }

        if(u == -1) break;
        vis[u] = 1;

        for(int p = head[u]; p != -1; p = eg[p].next) {
            edge &e = eg[p];
            if(vis[e.v]) continue;
            if(dis0[e.v] > dis0[u] + e.w) {
                dis0[e.v] = dis0[u] + e.w;
                dis1[e.v] = dis1[u] + pv[e.v];
            } else if(dis0[e.v] == dis0[u] + e.w) {
                if(dis1[e.v] < dis1[u] + pv[e.v])
                    dis1[e.v] = dis1[u] + pv[e.v];
            }
        }
    }
}

int main()
{
    int u, v, w;
    memset(head, -1, sizeof(head));
    scanf("%d%d%d%d", &n, &m, &ss, &ee);
    for(int i = 0; i < n; ++i)
        scanf("%d", &pv[i]);
    for(int i = 0; i < m; ++i) {
        scanf("%d%d%d", &u, &v, &w);
        addedge(u, v, w);
    }
    dijkstra();
    printf("%d %d\n", dis0[ee], dis1[ee]);
}
