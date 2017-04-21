// POJ No.1324 Holedox Moving (A* & BFS确定上界) (10236K 1110MS)
#include <queue>
#include <cstdio>
#include <cstring>
using namespace std;
#define abs(x) ((x) < 0 ? -(x) : (x))
const char dir[][2] = {{-1,0}, {0,1}, {1,0}, {0,-1}};

struct P {
    int r, c, step;
    P(int r=0, int c=0, int s=0): r(r), c(c), step(s) {}
};

struct Node {
    int hr, hc, status, g, h;
    Node(): hr(0), hc(0), status(0), g(0), h(0) {}
    Node(int r, int c, int s, int st, int h):
        hr(r), hc(c), status(s), g(st), h(h) {}
    bool operator > (const Node &n) const { return g + h > n.g + n.h; }
};

int R, C, L, K, maxstep;
bool inq[21][21][1<<14];
char M[21][21], M2[21][21];

// 返回由(r, c)到(1, 1)的曼哈顿距离作为启发函数值
int heuristic(int r, int c)
{
    return abs(1 - r) + abs(1 - c);
}

// 由n是否能向dir方向移动
bool ismovable(const Node &n, int d)
{
    int lr = n.hr, lc = n.hc;
    int r = n.hr + dir[d][0], c = n.hc + dir[d][1];

    if(r < 1 || r > R || c < 1 || c > C || M[r][c] == 1)
        return false;

    for(int i = 0; i < L-1; ++i) {
        int nd = (n.status >> (i * 2)) & 0x3;
        int nr = lr + dir[nd][0], nc = lc + dir[nd][1];
        if(nr == r && nc == c) return false;
        lr = nr, lc = nc;
    }
    return true;
}

// 返回向d方向移动后的新status
int getstatus(const Node &n, int d)
{
    int ns = (n.status << 2) & 0x3fff;
    if(d == 0) ns |= 0x2;
    else if(d == 2) ns |= 0x0;
    else if(d == 1) ns |= 0x3;
    else if(d == 3) ns |= 0x1;
    return ns;
}

// 将最初的身躯作为墙，再加上原有的墙，求头到(1, 1)的bfs距离
int BFS(int r, int c, char M[][21])
{
    queue<P> que;
    bool used[21][21] = {0};

    que.push(P(r, c, 0));
    used[r][c] = true;

    while(!que.empty()) {
        P p = que.front(); que.pop();
        if(p.r == 1 && p.c == 1) return p.step;
        for(int i = 0; i < 4; ++i) {
            int nr = p.r + dir[i][0], nc = p.c + dir[i][1];
            if(1 <= nr && nr <= R && 1 <= nc && nc <= C
                    && M[nr][nc] != 1 && !used[nr][nc]) {
                used[nr][nc] = true;
                que.push(P(nr, nc, p.step+1));
            }
        }
    }
    // 当BFS到不了终点的时，不代表真的到不了
    // 因为蛇的身体是会动的，即地图是会改变的
    // 所以返回了一个很大的值作为上界
    return 0x7fffffff;
}

int AStar(const Node &src)
{
    priority_queue<Node, vector<Node>, greater<Node> > que;
    que.push(src);
    memset(inq, 0, sizeof(inq));
    inq[src.hr][src.hc][src.status] = true;

    while(!que.empty()) {
        Node n = que.top(); que.pop();

        if(n.hr == 1 && n.hc == 1)
            return n.g;

        for(int i = 0; i < 4; ++i) {
            if(!ismovable(n, i)) continue;

            int ns = getstatus(n, i);
            int nr = n.hr + dir[i][0], nc = n.hc + dir[i][1];
            if(inq[nr][nc][ns]) continue;

            int f = n.g + 1 + heuristic(nr, nc);
            if(f > maxstep) continue;

            inq[nr][nc][ns] = true;
            que.push(Node(nr, nc, ns, n.g+1, heuristic(nr, nc)));
        }
    }
    return -1;
}

int main()
{
    int r, c, kase = 1;

    while(scanf("%d%d%d", &R, &C, &L) != EOF && R+C+L != 0) {
        Node src;
        memset(M, 0, sizeof(M));
        memset(M2, 0, sizeof(M2));
        scanf("%d%d", &src.hr, &src.hc);
        int lr = src.hr, lc = src.hc;
        src.h = heuristic(src.hr, src.hc);
        for(int i = 0; i < L-1; ++i) {
            scanf("%d%d", &r, &c);
            M2[r][c] = 1;
            if(r == lr) {
                if(c + 1 == lc) // 新在旧左
                    src.status |= (0x3 << (i * 2));
                else            // 新在旧右
                    src.status |= (0x1 << (i * 2));
            } else {
                if(r + 1 == lr) // 新在旧上
                    src.status |= (0x0 << (i * 2));
                else            // 新在旧下
                    src.status |= (0x2 << (i * 2));
            }
            lr = r, lc = c;
        }

        scanf("%d", &K);
        for(int i = 0; i < K; ++i) {
            scanf("%d%d", &r, &c);
            M[r][c] = M2[r][c] = 1;
        }

        maxstep = BFS(src.hr, src.hc, M2);
        printf("Case %d: %d\n", kase++, AStar(src));
    }
}
