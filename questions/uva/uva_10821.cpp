// UVA No.10821 Constructing BST
// 以[1,n]构成不大于h层BST，输出字典序最小解
// 贪心地尽量将结点放入右子树，最终得到最小解
#include <bits/stdc++.h>
using namespace std;

int pow2[33];

void dfs(int left, int right, int h)
{
    if(right < left) return;
    int root = max(right - pow2[h-1] + 1, left);
    printf(" %d", root);
    dfs(left, root-1, h-1);
    dfs(root+1, right, h-1);
}

int main()
{
    int n, h, kase = 1;

    pow2[0] = 1;
    for(int i = 1; i <= 32; ++i)
        pow2[i] = pow2[i-1] << 1;

    while(scanf("%d%d", &n, &h) == 2 && n+h) {
        printf("Case %d:", kase++);
        if(n > pow2[h]-1)
            printf(" Impossible.");
        else
            dfs(1, n, h);
        putchar(10);
    }
}
