// HDU No.2087 剪花布条 (31MS 1564K)
// 在T中找不重叠的P的出现次数
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e3 + 10;

int n, m;
int knext[maxn];
char T[maxn], P[maxn];

int kmp()
{
    if(m > n) return 0;

    knext[0] = -1;
    int ans = 0, i = 0, j = -1; 

    while(i < m) {
        if(j == -1 || P[i] == P[j])
            knext[i] = (P[++i] == P[++j]) ? knext[j] : j;
        else
            j = knext[j];
    }
    
    i = j = 0;
    while(i < n) {
        if(j == -1 || T[i] == P[j]) {
            ++i, ++j;
            if(j == m) ++ans, j = 0;
        } else {
            j = knext[j];
        }
    }
    return ans;
}

int main()
{
    while(~scanf("%s", T) && T[0] != '#') {
        scanf("%s", &P);
        n = strlen(T), m = strlen(P);
        printf("%d\n", kmp());
    }
}
