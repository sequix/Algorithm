// ZOJ No.1610 (区间覆盖)
// 染色一维线段，问最后每种颜色的段各有几段？
#include <map>
#include <cstdio>
using namespace std;
const int maxn = 8e3 + 10;
const int maxnode = maxn << 2;
#define lc(o) (((o)<<1)+1)
#define rc(o) (((o)<<1)+2)
inline int max(int a, int b) { return a < b ? b : a; }

struct {
    map<int, int> cnt;
    int color[maxnode];   // 完全被同一种颜色覆盖区间的颜色
    bool coverd[maxnode]; // 区间是否被完全覆盖，可能为不同颜色
    int L[maxnode], R[maxnode], M[maxnode];

    void init(int o, int l, int r) {
        if(l == r) {
            L[o] = R[o] = l;
            coverd[o] = 0, color[o] = -1;
            return;
        }
        L[o] = l, R[o] = r;
        M[o] = (l + r) >> 1;
        coverd[o] = 0, color[o] = -1;
        init(lc(o), l, M[o]);
        init(rc(o), M[o]+1, r);
    }
    void dye(int o, int l, int r, int c) {
        if(coverd[o])
            return;
        if(l == L[o] && r == R[o]) {
            coverd[o] = 1, color[o] = c;
            return;
        }
        if(r <= M[o]) {
            dye(lc(o), l, r, c);
        } else if(l > M[o]) {
            dye(rc(o), l, r, c);
        } else {
            dye(lc(o), l, M[o], c);
            dye(rc(o), M[o]+1, r, c);
        }
        coverd[o] = coverd[lc(o)] && coverd[rc(o)];
        if(color[lc(o)] == color[rc(o)]) color[o] = color[lc(o)];
    }
    void dfs(int o) {
        if(color[o] != -1) { ++cnt[color[o]]; return; }
        if(L[o] == R[o]) return;
        dfs(lc(o)); dfs(rc(o));
    }
    void getcnt() { cnt.clear(); dfs(0); }
} tree;

int n;
int endL[maxn], endR[maxn], color[maxn];

int main()
{
    map<int, int>::iterator it;

    while(scanf("%d", &n) == 1) {
        int ne = 0;
        for(int i = 0; i < n; ++i) {
            scanf("%d%d%d", &endL[i], &endR[i], &color[i]);
            ne = max(ne, endR[i]);
        }

        // 这里给的是点的坐标，不是段的编号，
        // 以每一段的左端点为每一段编码，即相当与右端点减1
        tree.init(0, 0, ne-1);
        for(int i = n-1; i >= 0; --i)
            tree.dye(0, endL[i], endR[i]-1, color[i]);
        tree.getcnt();

        for(it = tree.cnt.begin(); it != tree.cnt.end(); ++it)
            printf("%d %d\n", it->first, it->second);
        putchar(10);
    }
}
