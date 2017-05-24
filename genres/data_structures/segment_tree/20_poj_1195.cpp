// POJ So.1195 (二维线段树单点更新) (24824K 1516MS)
#include <cstdio>
using namespace std;
const int maxn = 1100;
const int maxnode = maxn * 3;
#define lc(x) (((x)<<1)+1)
#define rc(x) (((x)<<1)+2)

int S;

struct {
    int oy;
    int sum[maxnode][maxnode];

    void addY(int o, int L, int R, int x, int y, int a) {
        oy = o; addX(0, 0, S-1, x, a);
        if(L == R) return;
        int M = (L + R) >> 1;
        if(y <= M)
            addY(lc(o), L, M, x, y, a);
        else
            addY(rc(o), M+1, R, x, y, a);
    }
    void addX(int o, int L, int R, int x, int a) {
        sum[oy][o] += a;
        if(L == R) return;
        int M = (L + R) >> 1;
        if(x <= M)
            addX(lc(o), L, M, x, a);
        else
            addX(rc(o), M+1, R, x, a);
    }
    int queryY(int o, int L, int R, int y1, int y2, int x1, int x2) {
        oy = o;
        if(y1 == L && R == y2) {
            return queryX(0, 0, S-1, x1, x2);
        } else {
            int M = (L + R) >> 1;
            if(y2 <= M) {
                return queryY(lc(o), L, M, y1, y2, x1, x2);
            } else if(y1 > M) {
                return queryY(rc(o), M+1, R, y1, y2, x1, x2);
            } else {
                int s1 = queryY(lc(o), L, M, y1, M, x1, x2);
                int s2 = queryY(rc(o), M+1, R, M+1, y2, x1, x2);
                return s1 + s2;
            }
        }
    }
    int queryX(int o, int L, int R, int x1, int x2) {
        if(x1 == L && R == x2) {
            return sum[oy][o];
        } else {
            int M = (L + R) >> 1;
            if(x2 <= M) {
                return queryX(lc(o), L, M, x1, x2);
            } else if(x1 > M) {
                return queryX(rc(o), M+1, R, x1, x2);
            } else {
                int s1 = queryX(lc(o), L, M, x1, M);
                int s2 = queryX(rc(o), M+1, R, M+1, x2);
                return s1 + s2;
            }
        }
    }
} seg;

int main()
{
    int cmd, a, b, c, d, sum;

    while(scanf("%d", &cmd) != EOF) {
        switch(cmd) {
            case 0:
                scanf("%d", &S);
                break;
            case 1:
                scanf("%d%d%d", &a, &b, &c);
                seg.addY(0, 0, S-1, a, b, c);
                break;
            case 2:
                scanf("%d%d%d%d", &a, &b, &c, &d);
                sum = seg.queryY(0, 0, S-1, b, d, a, c);
                printf("%d\n", sum);
                break;
            case 3:
                return 0;
        }
    }
}
