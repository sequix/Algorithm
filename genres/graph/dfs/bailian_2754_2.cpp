// BaiLian No.2754 八皇后 (回溯) (136kb 1ms)
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

void init()
{
    int dep = 0;
    memset(cur, 0, sizeof(cur));

    while(dep >= 0) {
        for(++cur[dep]; cur[dep] <= 8; ++cur[dep])
            if(placeTest(dep)) break;
        if(cur[dep] <= 8) { // 找到可行摆法
            if(dep == 7) {
                memcpy(&ans[cnt++], cur, sizeof(cur));
            } else {
                cur[++dep] = 0;
            }
        } else {    // 没有找到回溯
            --dep;
        }
    }
}

int main()
{
    int T, n;
    init();
    for(scanf("%d", &T); T > 0; --T) {
        scanf("%d", &n); --n;
        for(int i = 0; i < 8; ++i)
            printf("%d", ans[n][i]);
        putchar(10);
    }
}
