// POJ No.1151 (矩形面积并) (460K 16MS)
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 210;

int n, cnt, kase = 0;
bool covered[maxn][maxn];
double s[maxn][4], x[maxn], y[maxn];

int main()
{
    while(~scanf("%d", &n) && n) {
        cnt = 0;
        memset(covered, 0, sizeof(covered));

        for(int i = 0; i < n; ++i) {
            scanf("%lf%lf%lf%lf", &s[i][0], &s[i][1], &s[i][2], &s[i][3]);
            x[cnt] = s[i][0], y[cnt++] = s[i][1];
            x[cnt] = s[i][2], y[cnt++] = s[i][3];
        }
        x[cnt] = 0, y[cnt++] = 0;
        sort(x, x + cnt);
        sort(y, y + cnt);

        for(int i = 0; i < n; ++i) {
            int x1 = lower_bound(x, x + cnt, s[i][0]) - x;
            int y1 = lower_bound(y, y + cnt, s[i][1]) - y;
            int x2 = lower_bound(x, x + cnt, s[i][2]) - x;
            int y2 = lower_bound(y, y + cnt, s[i][3]) - y;
            for(int i = x1; i < x2; ++i)
                for(int j = y1; j < y2; ++j)
                        covered[i][j] = 1;
        }

        double ans = 0;
        for(int i = 0; i < cnt; ++i)
            for(int j = 0; j < cnt; ++j)
                if(covered[i][j])
                    ans += (x[i+1]-x[i]) * (y[j+1]-y[j]);
        printf("Test case #%d\n", ++kase);
        printf("Total explored area: %.2f\n\n", ans);
    }
}
