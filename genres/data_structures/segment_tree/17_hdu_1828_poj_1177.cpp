// POJ No.1177 & HDU No.1828 (矩形周长并) (1100K 16MS)
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 5e3 + 10;
const int maxnode = maxn << 3;
#define lc(x) ((x)<<1)
#define rc(x) ((x)<<1|1)

int n, ys[maxn<<1];

struct VLine {
    bool left;
    int x, y1, y2;
    bool operator < (const VLine &vl) const {
        return (x != vl.x) ? x < vl.x : left > vl.left;
    }
} lines[maxn<<1];

struct {
    bool lcovered[maxnode], rcovered[maxnode];
    int covers[maxnode], cnt[maxnode], len[maxnode];

    void pushup(int o) {
        len[o] = len[lc(o)] + len[rc(o)];
        cnt[o] = cnt[lc(o)] + cnt[rc(o)];
        lcovered[o] = lcovered[lc(o)];
        rcovered[o] = rcovered[rc(o)];
        if(rcovered[lc(o)] && lcovered[rc(o)]) --cnt[o];
    }
    void update(char T, int o, int L, int R, int qL, int qR) {
        if(qL == L && qR == R) {
            if(T == 'I') {
                cnt[o] = 1, ++covers[o];
                len[o] = ys[qR+1] - ys[qL];
                lcovered[o] = rcovered[o] = 1;
            } else {
                if(--covers[o] == 0) {
                    if(L == R) {
                        cnt[o] = len[o] = 0;
                        lcovered[o] = rcovered[o] = 0;
                    } else {
                        pushup(o);
                    }
                }
            }
        } else {
            int M = (L + R) >> 1;
            if(qR <= M) {
                update(T, lc(o), L, M, qL, qR);
            } else if(qL > M) {
                update(T, rc(o), M+1, R, qL, qR);
            } else {
                update(T, lc(o), L, M, qL, M);
                update(T, rc(o), M+1, R, M+1, qR);
            }
            if(covers[o] == 0) pushup(o);
        }
    }
} seg;

int main()
{
    int x1, y1, x2, y2;

    while(scanf("%d", &n) != EOF) {
        int cys = 0, cls = 0;
        for(int i = 0; i < n; ++i) {
            scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
            ys[cys++] = y1, ys[cys++] = y2;
            lines[cls++] = (VLine){1, x1, y1, y2};
            lines[cls++] = (VLine){0, x2, y1, y2};
        }
        sort(ys, ys+cys);
        cys = unique(ys, ys+cys) - ys;
        sort(lines, lines+cls);
        memset(&seg, 0, sizeof(seg));

        int ans = 0, lastlen = 0, lastcnt = 0;
        for(int i = 0; i < cls; ++i) {
            int dy1 = lower_bound(ys, ys+cys, lines[i].y1) - ys;
            int dy2 = lower_bound(ys, ys+cys, lines[i].y2) - ys;

            if(lines[i].left)
                seg.update('I', 1, 0, cys-2, dy1, dy2-1);
            else
                seg.update('R', 1, 0, cys-2, dy1, dy2-1);

            if(lastcnt > 0)
                ans += 2 * lastcnt * (lines[i].x - lines[i-1].x);
            ans += abs(lastlen - seg.len[1]);
            lastlen = seg.len[1], lastcnt = seg.cnt[1];
        }
        printf("%d\n", ans);
    }
}
