#include <bits/stdc++.h>
using namespace std;

int n, m;
int v[10][10];

int hjudge(int from, int to, int row)
{
    for(int i = from; i <= to; ++i) {
        int cnt = 0;
        for(int j = i; j < i+3; ++j)
            if(v[row][j] == 1) ++cnt;
        if(cnt == 3) return 1;
    }
    return 0;
}

int vjudge(int from, int to, int col)
{
    for(int i = from; i <= to; ++i) {
        int cnt = 0;
        for(int j = i; j < i + 3; ++j)
            if(v[j][col] == 1) ++cnt;
        if(cnt == 3) return 1;
    }
    return 0;
}

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
        v[x+3][y+3] = 2;
    }

    int ans = 0;
    ans += hjudge(0, 4, 0);
    ans += hjudge(1, 3, 1);
    ans += hjudge(2, 2, 2);
    ans += hjudge(2, 2, 4);
    ans += hjudge(1, 3, 5);
    ans += hjudge(0, 4, 6);

    ans += vjudge(0, 4, 0);
    ans += vjudge(1, 3, 1);
    ans += vjudge(2, 2, 2);
    ans += vjudge(2, 2, 4);
    ans += vjudge(1, 3, 5);
    ans += vjudge(0, 4, 6);

    if(v[4][3]==1 && v[5][3]==1 && v[6][3]==1) ++ans;
    if(v[3][4]==1 && v[3][5]==1 && v[3][6]==1) ++ans;
    if(v[2][3]==1 && v[1][3]==1 && v[0][3]==1) ++ans;
    if(v[3][2]==1 && v[3][1]==1 && v[3][0]==1) ++ans;

    printf("%d\n", ans);
}
