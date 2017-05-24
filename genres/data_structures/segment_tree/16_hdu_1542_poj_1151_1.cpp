// HDU No.1542 & POJ No.1151 (矩形面积并) (0MS 1576K)
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 110;
const int maxnode = maxn << 3;
#define lc(x) ((x)<<1)
#define rc(x) ((x)<<1|1)

int n;
double ys[maxn<<1];

struct VLine {  // 代表每条垂直的线段
    bool left;  // 该线段是否为一个矩形的左侧边
    double x, y1, y2;
    bool operator < (const VLine &vl) const { return x < vl.x; }
} lines[maxn<<1];

struct {
    int covers[maxnode]; // 该区间被多少个矩形完全覆盖
    double len[maxnode]; // 该区间被覆盖的长度

    void update(int o, int L, int R, int qT, int qL, int qR) {
        if(qL == L && qR == R) {
            if(qT == 'I') {
                ++covers[o];
                // 这里需要的不是区间编号，而是第几个纵坐标，所以qR+1
                len[o] = ys[qR+1] - ys[qL];
            } else {
                if(--covers[o] == 0) {
                    if(L == R) len[o] = 0;
                    else len[o] = len[lc(o)] + len[rc(o)];
                }
            }
        } else {
            int M = (L + R) >> 1;
            if(qR <= M) {
                update(lc(o), L, M, qT, qL, qR);
            } else if(qL > M) {
                update(rc(o), M+1, R, qT, qL, qR);
            } else {
                update(lc(o), L, M, qT, qL, M);
                update(rc(o), M+1, R, qT, M+1, qR);
            }
            if(covers[o] == 0)
                len[o] = len[lc(o)] + len[rc(o)];
        }
    }
} seg;

int main()
{
    int kase = 1;
    double x1, y1, x2, y2;

    while(~scanf("%d", &n) && n) {
        int cys = 0, cls = 0;
        for(int i = 0; i < n; ++i) {
            scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
            ys[cys++] = y1, ys[cys++] = y2;
            lines[cls].x = x1;
            lines[cls].y1 = y1, lines[cls].y2 = y2;
            lines[cls++].left = 1;
            lines[cls].x = x2;
            lines[cls].y1 = y1, lines[cls].y2 = y2;
            lines[cls++].left = 0;
        }
        sort(ys, ys+cys);
        cys = unique(ys, ys+cys) - ys;
        memset(&seg, 0, sizeof(seg));
        // cys-1条线，分出cys-1个区间，编号为从0到cys-2
        sort(lines, lines + cls);

        double ans = 0.0;
        for(int i = 0; i < cls-1; ++i) {
            int dy1 = lower_bound(ys, ys+cys, lines[i].y1) - ys;
            int dy2 = lower_bound(ys, ys+cys, lines[i].y2) - ys;
            if(lines[i].left) {
                // 注意这里需要区间编号，所以以每个区间的左端点
                // 为其编号，即以dy2-1为其编号
                seg.update(1, 0, cys-2, 'I', dy1, dy2-1);
            } else {
                seg.update(1, 0, cys-2, 'R', dy1, dy2-1);
            }
            ans += (lines[i+1].x - lines[i].x) * seg.len[1];
        }
        printf("Test case #%d\n", kase++);
        printf("Total explored area: %.2f\n\n", ans);
    }
}
