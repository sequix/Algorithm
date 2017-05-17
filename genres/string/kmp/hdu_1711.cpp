// HDU No.1711 Number Sequence (1154MS 5560K)
// 在A中找P第一次出现位置
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 10;
const int maxm = 1e4 + 10;

int n, m;
int A[maxn];
int P[maxm];
int knext[maxm];

void init()
{
    knext[0] = -1;
    int i = 0, j = -1; 

    while(i < m) {
        if(j == -1 || P[i] == P[j])
            knext[i] = (P[++i] == P[++j]) ? knext[j] : j;
        else
            j = knext[j];
    }
}

int kmp()
{
    int i = 0, j = 0;
    if(m > n) return -1;

    while(i < n && j < m) {
        if(j == -1 || A[i] == P[j]) {
            ++i, ++j;
            if(j == m) return i - m + 1;
        } else {
            j = knext[j];
        }
    }
    return -1;
}

int main()
{
    int T;
    for(scanf("%d", &T); T; --T) {
        scanf("%d%d", &n, &m);
        for(int i = 0; i < n; ++i) scanf("%d", &A[i]);
        for(int i = 0; i < m; ++i) scanf("%d", &P[i]);
        init();
        printf("%d\n", kmp());
    }
}
