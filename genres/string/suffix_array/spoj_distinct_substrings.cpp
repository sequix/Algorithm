// SPOJ DISUBSTR - Distinct Substrings
// 求字符串不相同子串数量。
// 每个子串一定是某个后缀的前缀，
// 那么原问题等价于求所有后缀之间的不相同的前缀的个数。
// 而且可以发现每一个后缀Suffix[SA[i]]的贡献是Len - SA[i] + 1,
// 但是有子串算重复，重复的就是Heigh[i]个与前面相同的前缀，
// 那么减去就可以了。最后，
// 一个后缀Suffix[SA[i]]的贡献就是Len - SA[k] + 1 - Height[k]。
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e3 + 10;

char s[maxn];
int c[maxn], t1[maxn], t2[maxn];
int height[maxn], srank[maxn], sa[maxn];

void buildSA(int n, int m)
{
    int i, p, k, *x = t1, *y = t2;

    for(i = 0; i < m; ++i) c[i] = 0;
    for(i = 0; i < n; ++i) ++c[x[i]=s[i]];
    for(i = 1; i < m; ++i) c[i] += c[i-1];
    for(i = n-1; i >= 0; --i) sa[--c[x[i]]] = i;
    for(k = 1; k <= n; k <<= 1, m = p) {
        p = 0;
        for(i = n-k; i < n; ++i) y[p++] = i;
        for(i = 0; i < n; ++i) if(sa[i] >= k) y[p++] = sa[i]-k;
        for(i = 0; i < m; ++i) c[i] = 0;
        for(i = 0; i < n; ++i) ++c[x[y[i]]];
        for(i = 1; i < m; ++i) c[i] += c[i-1];
        for(i = n-1; i >= 0; --i) sa[--c[x[y[i]]]] = y[i];
        swap(x, y), p = 1, x[sa[0]] = 0;
        for(i = 1; i < n; ++i)
            x[sa[i]] = y[sa[i]]==y[sa[i-1]] &&
                y[sa[i]+k]==y[sa[i-1]+k] ? p-1 : p++;
        if(p >= n) break;
    }
    for(i = 0; i < n; ++i) srank[sa[i]] = i;
    for(k = 0, i = 0; i < n; ++i) {
        if(k) --k;
        if(!srank[i]) continue;
        int j = sa[srank[i]-1];
        while(s[i+k] == s[j+k]) ++k;
        height[srank[i]] = k;
    }
}

int main()
{
    int T;
    for(scanf("%d", &T); T; --T) {
        scanf(" %s", s);
        int len = strlen(s);
        buildSA(len+1, 128);

// 注意这里sa和rank从1开始，开始，因为字符串中加入了
// 一个极小字符'\0'，但sa和rank中的还是对应原下标的

        int ans = 0;
        for(int i = 1; i <= len; ++i)
            ans += len - sa[i] - height[i];
        printf("%d\n", ans);
    }
}
