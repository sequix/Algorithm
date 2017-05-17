// POJ No.3294 Life Forms (后缀数组) (3124K 954MS)
// 求在超过半数的字符串中出现的公共子串
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 1e5 + 200;

int N, n, s[maxn];
int t1[maxn], t2[maxn], c[maxn];
int sa[maxn], height[maxn], srank[maxn];

int len[105];
bool vis[105];
int size, ans[maxn];

int getword(int *s)
{
    int cnt = 0;
    while(isspace(s[cnt] = getchar()));
    for(++cnt; !isspace(s[cnt] = getchar()); ++cnt);
    s[cnt] = 0;
    return cnt;
}

void buildSA(int m)
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

bool isok(int mid)
{
    size = 0;
    int cnt = 0;
    memset(vis, 0, sizeof(vis));

    for(int i = 1; i <= n; ++i) {
        if(height[i] >= mid) {
            for(int j = 1; j <= N; ++j) {
                if(len[j-1]<=sa[i]&&sa[i]<len[j] && !vis[j])
                    vis[j] = 1, ++cnt;
                if(len[j-1]<=sa[i-1]&&sa[i-1]<len[j] && !vis[j])
                    vis[j] = 1, ++cnt;
            }
        } else {
            if(cnt > N>>1) ans[++size] = sa[i-1];
            cnt = 0;
            memset(vis, 0, sizeof(vis));
        }
    }
    if(cnt > N>>1) ans[++size] = sa[n];
    if(size) { ans[0] = size; return 1; }
    return 0;
}

int main()
{
    bool fir = 1;
    while(scanf("%d", &N) == 1 && N) {
        if(fir) fir = 0; else putchar(10);

        n = 0;
        int sep = 127;
        for(int i = 1; i <= N; ++i) {
            n += getword(s + n);
            s[n++] = ++sep;
            len[i] = n;
        }
        buildSA(sep + 1);

        int l = 0, r = 1010;
        while(l < r) {
            int m = (l + r + 1) >> 1;
            if(isok(m)) l = m; else r = m - 1;
        }

        if(!l) {
            puts("?");
        } else {
            for(int i = 1; i <= ans[0]; ++i) {
                for(int j = ans[i]; j < ans[i]+l; ++j)
                    putchar(s[j]);
                putchar(10);
            }
        }
    }
}
