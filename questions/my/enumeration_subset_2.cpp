// 枚举一个给定集合的所有子集，集合以二进制表示
#include <bits/stdc++.h>
using namespace std;

int main()
{
    int U;
    while(scanf("%x", &U) != EOF) {
        for(int S = U; S; S = (S-1) & U)
            printf("0x%08X\n", S);
    }
}
