// HDU No.4979 A simple math problem.
#include <bits/stdc++.h>
using namespace std;

int T, N, M, R;
int ans[10][10][10] = {
    {
        {0}
    },
    {
        {0},
        {0, 1}
    },
    {
        {0},
        {0, 2},
        {0, 1, 1}
    },
    {
        {0},
        {0, 3},
        {0, 2, 3},
        {0, 1, 1, 1}
    },
    {
        {0},
        {0, 4},
        {0, 2, 6},
        {0, 2, 3, 4},
        {0, 1, 1, 1, 1}
    },
    {
        {0},
        {0, 5},
        {0, 3, 10},
        {0, 2, 4, 10},
        {0, 2, 3, 4, 5},
        {0, 1, 1, 1, 1, 1}
    },
    {
        {0},
        {0, 6},
        {0, 3, 15},
        {0, 2, 6, 20},
        {0, 2, 3, 6, 15},
        {0, 2, 3, 4, 5, 6},
        {0, 1, 1, 1, 1, 1, 1}
    },
    {
        {0},
        {0, 7},
        {0, 4, 21},
        {0, 3, 7, 35},
        {0, 2, 5, 12, 35},
        {0, 2, 3, 5, 9, 21},
        {0, 2, 3, 4, 5, 6, 7},
        {0, 1, 1, 1, 1, 1, 1, 1}
    },
    {
        {0},
        {0, 8},
        {0, 4, 28},
        {0, 3, 11, 56},
        {0, 2, 6, 14, 70},
        {0, 2, 4, 8, 20, 56},
        {0, 2, 3, 4, 7, 12, 28},
        {0, 2, 3, 4, 5, 6, 7, 8},
        {0, 1, 1, 1, 1, 1, 1, 1, 1}
    }
};

int main()
{
    scanf("%d", %T);
    for(int kase = 1; kase <= T; ++kase) {
        scanf("%d%d%d", &N, &M, &R);
        printf("Case #%d: %d\n", kase, ans[N][M][R]);
    }
}
