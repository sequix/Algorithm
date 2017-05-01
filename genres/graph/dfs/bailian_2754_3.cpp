// BaiLian No.2754 八皇后 (dfs) (136kb 1ms)
#include <bits/stdc++.h>
using namespace std;

int cnt;
int cur[8];
int ans[92][8];

bool placeTest(int n)
{
    for(int i = 0; i < n; ++i)
        if(cur[n] == cur[i] || abs(cur[i]-cur[n])==abs(n-i))
            return 0;
    return 1;
}

void dfs(int dep)
{
    if(dep == 8) {
        memcpy(&ans[cnt++], cur, sizeof(cur));
        return;
    }
    for(int i = 1; i <= 8; ++i) {
        cur[dep] = i;
        if(!placeTest(dep)) continue;
        dfs(dep+1);
    }
}

int main()
{
    int T, n;
    dfs(0);
    for(scanf("%d", &T); T > 0; --T) {
        scanf("%d", &n); --n;
        for(int i = 0; i < 8; ++i)
            printf("%d", ans[n][i]);
        putchar(10);
    }
}
