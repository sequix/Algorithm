// BaiLian No.2754 八皇后 (穷举) (136kB 1ms)
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
    for(int c1 = 1; c1 <= 8; ++c1) {
        cur[0] = c1;
        for(int c2 = 1; c2 <= 8; ++c2) {
            cur[1] = c2;
            if(!placeTest(1)) continue;
            for(int c3 = 1; c3 <= 8; ++c3) {
                cur[2] = c3;
                if(!placeTest(2)) continue;
                for(int c4 = 1; c4 <= 8; ++c4) {
                    cur[3] = c4;
                    if(!placeTest(3)) continue;
                    for(int c5 = 1; c5 <= 8; ++c5) {
                        cur[4] = c5;
                        if(!placeTest(4)) continue;
                        for(int c6 = 1; c6 <= 8; ++c6) {
                            cur[5] = c6;
                            if(!placeTest(5)) continue;
                            for(int c7 = 1; c7 <= 8; ++c7) {
                                cur[6] = c7;
                                if(!placeTest(6)) continue;
                                for(int c8 = 1; c8 <= 8; ++c8) {
                                    cur[7] = c8;
                                    if(!placeTest(7)) continue;
                                    memcpy(&ans[cnt++], cur, sizeof(cur));
                                }
                            }
                        }
                    }
                }
            }
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
