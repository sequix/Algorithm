// HUST No.1010 The Minimum Length (128ms 5544kb)
// 有一个字符串A，一次次的重写A，会得到一个新的字符串AAAAAAAA.....,
// 现在将这个字符串从中切去一部分得到一个字符串B，例如有一个字符串
// A="abcdefg".，复制几次之后得到abcdefgabcdefgabcdefgabcdefg....，
// 现在切去中间红色的部分，得到字符串B，现在只给出字符串B，
// 求出字符串A的长度
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 10;

char S[maxn];
int knext[maxn];

int main()
{
    int len, i, j;

    while(~scanf("%s", S)) {
        len = strlen(S);
        knext[0] = -1;
        i = 0, j = -1;

        while(i < len) {
            if(j == -1 || S[i] == S[j])
                knext[++i] = ++j;
            else
                j = knext[j];
        }
        printf("%d\n", len - knext[len]);
    }
}
