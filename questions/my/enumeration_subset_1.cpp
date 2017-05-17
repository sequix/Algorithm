// 枚举大小为K的子集，全集有N元素
#include <bits/stdc++.h>
using namespace std;

int ksubset(int n, int k)
{
    int comb = (1 << k) - 1;
    while(comb < 1 << n) {
        int x = comb & -comb, y = comb + x;
        printf("0x%02X 0x%02X 0x%02X\n", comb, x, y);
        comb = ((comb & ~y) / x >> 1) | y;
// 1. 求最低为的1开始连续的1的区间 (comb & ~y)
// 2. 将该区间右移，直到1的个数减少1个 ((comb & ~y) / x >> 1)
// 3. 将该区间变为0，并将区间左侧的0变为1 (y == comb + lowbit[comb])
// 4. 将2、3步结果合并 (((comb & ~y) / x >> 1) | y)
    }
}

int main()
{
    int n, k;
    while(cin >> n >> k) ksubset(n, k);
}
