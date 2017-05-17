// HDU No.1686 Oulipo (140MS 2596K)
// 在T中找可重叠的P的出现次数
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 10;
const int maxm = 1e4 + 10;

int n, m;
int knext[maxn];
char T[maxn], P[maxm];

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
            if(j == m) ++ans, j = knext[j];
        } else {
            j = knext[j];
        }
    }
    return ans;
}

int main()
{
    int kase;
    for(scanf("%d", &kase); kase; --kase) {
        scanf("%s%s", P, T);
        n = strlen(T), m = strlen(P);
        printf("%d\n", kmp());
    }
}
