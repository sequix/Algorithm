// suffix array implementation
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e3 + 10;

void printArr(const char *s, int *arr, int n)
{
    printf("%s", s);
    for(int i = 0; i < n; ++i)
        printf(" %d", arr[i]);
    putchar(10);
}

struct {
    const char *s;
    int n, sa[maxn], rank[maxn], h[maxn];
    int c[maxn], t1[maxn], t2[maxn];

// n为字符串长加1，并且字符串尾为整个字符串中最小值
// sa[i] 排名为i的后缀是谁 (排名对应情况)
// rank[i] 后缀i排第几
// h[i] 排名i的后缀和其前一名后缀的LCP长度 (就是height)

    void init(const char *ss) {
        s = ss;
        n = strlen(s);
        build(*max_element(s, s+n) + 1);
    }
    void build(int m) {
        int i, p, k, *x = t1, *y = t2;
        for(i = 0; i < m; ++i) c[i] = 0;
        for(i = 0; i < n; ++i) ++c[x[i] = s[i]];
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
                x[sa[i]] = y[sa[i-1]]==y[sa[i]] &&
                    y[sa[i-1]+k]==y[sa[i]+k] ? p-1 : p++;
            if(p >= n) break;
        }
        for(int i = 0; i < n; ++i) rank[sa[i]] = i;
        for(k = 0, i = 0; i < n; ++i) {
            if(k) --k;
            if(rank[i] == 0) { h[0] = 0; continue; }
            int j = sa[rank[i]-1];
            while(s[i+k] == s[j+k]) ++k;
            h[rank[i]] = k;
        }
    }
    int find(const char *p) {
        int l = 0, r = n-1;
        int lenp = strlen(p);
        if(strncmp(p, s+sa[0], lenp) < 0) return -1;
        if(strncmp(p, s+sa[n-1], lenp) > 0) return -1;
        while(l < r) {
            int m = (l + r) >> 1;
            int res = strncmp(p, s+sa[m], lenp);
            if(!res) return m;
            if(res < 0) r = m-1; else l = m+1;
        }
        return -1;
    }
} SA;

int main()
{
    char buf[BUFSIZ];
    while(~scanf("%s", buf)) {
        SA.init(buf);
        int len = strlen(buf);
        printArr("rank:", SA.rank, len);
        printArr("sa:", SA.sa, len);
        printArr("h:", SA.h, len);
    }
}
