#include <bits/stdc++.h>
using namespace std;

int n, m;
int v[10][10];

int main()
{
    int x, y;
    scanf("%d%d", &n, &m);
    for(int i = 0; i < n; ++i) {
        scanf("%d%d", &x, &y);
        v[x+3][y+3] = 1;
    }
    for(int i = 0; i < m; ++i) {
        scanf("%d%d", &x, &y);
        v[x+3][y+3] = 0;
    }

    int ans = 0;

    if(v[0][0] && v[3][0] && v[6][0]) ++ans;
    if(v[1][1] && v[3][1] && v[5][1]) ++ans;
    if(v[2][2] && v[3][2] && v[4][2]) ++ans;
    if(v[2][4] && v[3][4] && v[4][4]) ++ans;
    if(v[1][5] && v[3][5] && v[6][5]) ++ans;
    if(v[0][6] && v[3][6] && v[6][6]) ++ans;

    if(v[0][0] && v[0][3] && v[0][6]) ++ans;
    if(v[1][1] && v[1][3] && v[1][5]) ++ans;
    if(v[2][2] && v[2][3] && v[2][4]) ++ans;
    if(v[4][2] && v[4][3] && v[4][4]) ++ans;
    if(v[5][1] && v[5][3] && v[5][5]) ++ans;
    if(v[6][0] && v[6][3] && v[6][6]) ++ans;

    if(v[4][3] && v[5][3] && v[6][3]) ++ans;
    if(v[3][4] && v[3][5] && v[3][6]) ++ans;
    if(v[2][3] && v[1][3] && v[0][3]) ++ans;
    if(v[3][2] && v[3][1] && v[3][0]) ++ans;

    printf("%d\n", ans);
}
