// tyvj No.1716 二维fenwick的矩形修改和矩形查询
#include <cstdio>
using namespace std;
const int maxn = 2049;
#define lowbit(x) ((x) & -(x))

int n, m;
int a[maxn][maxn];
int b[maxn][maxn];  // b[i][j] == i * a[i][j]
int c[maxn][maxn];  // c[i][j] == j * a[i][j]
int d[maxn][maxn];  // d[i][j] == i * j * a[i][j]

inline void add(int C[maxn][maxn], int x, int y, int w)
{
    for(int i = x; i <= n; i += lowbit(i))
        for(int j = y; j <= m; j += lowbit(j))
            C[i][j] += w;
}

inline int sum(int C[maxn][maxn], int x, int y)
{
    int r = 0;
    for(int i = x; i > 0; i -= lowbit(i))
        for(int j = y; j > 0; j -= lowbit(j))
            r += C[i][j];
    return r;
}

inline void update(int x1, int y1, int x2, int y2, int w)
{
    add(a, x1, y1, w);
    add(a, x1, y2+1, -w);
    add(a, x2+1, y1, -w);
    add(a, x2+1, y2+1, w);

    add(b, x1, y1, x1*w);
    add(b, x1, y2+1, -x1*w);
    add(b, x2+1, y1, -(x2+1)*w);
    add(b, x2+1, y2+1, (x2+1)*w);

    add(c, x1, y1, y1*w);
    add(c, x1, y2+1, -(y2+1)*w);
    add(c, x2+1, y1, -y1*w);
    add(c, x2+1, y2+1, (y2+1)*w);

    add(d, x1, y1, x1*y1*w);
    add(d, x1, y2+1, -x1*(y2+1)*w);
    add(d, x2+1, y1, -(x2+1)*y1*w);
    add(d, x2+1, y2+1, (x2+1)*(y2+1)*w);
}

inline int query(int x, int y)
{
    return (x+1)*(y+1)*sum(a, x, y) - (y+1)*sum(b, x, y)
        - (x+1)*sum(c, x, y) + sum(d, x, y);
}

int main()
{
    char c, cmd[2];
    int x1, x2, y1, y2, w;

    scanf("%*s%d%d", &n, &m);
    while(scanf("%s", cmd) != EOF) {
        if(cmd[0] == 'L') {
            scanf("%d%d%d%d%d", &x1, &y1, &x2, &y2, &w);
            update(x1, y1, x2, y2, w);
        } else {
            scanf("%d%d%d%d%d", &x1, &y1, &x2, &y2);
            printf("%d\n", query(x2, y2) - query(x1-1, y2)
                    - query(x2, y1-1) + query(x1-1, y1-1));
        }
    }
}
