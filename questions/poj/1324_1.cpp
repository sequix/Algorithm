// POJ No.1324 Holedox Moving (A*) (13304K 1110MS)
#include <queue>
#include <cstring>
#include <iostream>
using namespace std;
#define abs(x) ((x) < 0 ? -(x) : (x))
const char dir[][2] = {{-1,0}, {0,1}, {1,0}, {0,-1}};

struct Node {
    int hr, hc, status, g, f;
    Node(): hr(0), hc(0), status(0), g(0), f(0) {}
    Node(int r, int c, int s, int st, int f):
        hr(r), hc(c), status(s), g(st), f(f) {}
    bool operator > (const Node &n) const { return f > n.f; }
};

int R, C, L, K;
char M[25][25];
bool inq[25][25][1<<14];

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
    if(r < 1 || r > R || c < 1 || c > C) return false;

    for(int i = 0; i < L-1; ++i) {
        int nd = (n.status >> (i * 2)) & 0x3;
        int nr = lr + dir[nd][0], nc = lc + dir[nd][1];
        if(nr == r && nc == c) return false;
        lr = nr, lc = nc;
    }
    return M[r][c] == 0;
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
            inq[nr][nc][ns] = true;
            que.push(Node(nr, nc, ns, n.g+1, n.g+1+heuristic(nr, nc)));
        }
    }
    return -1;
}

int main()
{
    int r, c, kase = 1;

    while(cin >> R >> C >> L && R + C + L != 0) {
        Node src;
        cin >> src.hr >> src.hc;
        int lr = src.hr, lc = src.hc;
        src.f = heuristic(src.hr, src.hc);
        for(int i = 0; i < L-1; ++i) {
            cin >> r >> c;
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

        cin >> K;
        memset(M, 0, sizeof(M));
        for(int i = 0; i < K; ++i) {
            cin >> r >> c;
            M[r][c] = 1;
        }
        cout << "Case " << kase++ << ": " << AStar(src) << endl;
    }
}
