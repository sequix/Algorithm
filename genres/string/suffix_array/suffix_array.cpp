// suffix array implementation
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e3 + 10;

int n;  // 字符串在s[0...n-1]范围内，有n个字符，且s[n-1] == '\0'
        // 即n == strlen(s) + 1;

char s[maxn];   // 原字符串，常用int数组代替
int c[maxn];    // 基数排序中的计数数组
int t1[maxn], t2[maxn]; // *x, *y指向的缓冲区

// x[i] 基数排序中第i个元素中的基数
// y[i] 第二个关键字排名数组

int height[maxn]; // height[i] 排第i的后缀和排第i-1的后缀的LCP长度
int srank[maxn]; // srank[i] 第i个后缀的排名，i从1开始，其值从0开始
int sa[maxn]; // sa[i] 排第i的后缀是第几个后缀，i从1开始，其值从0开始

void printArr(const char *s, int *arr, int n)
{
    printf("%s", s);
    for(int i = 0; i < n; ++i)
        printf(" %d", arr[i]);
    putchar(10);
}

// s[]中的所有字符应该在[0, m)中，即m == *max_element(s, s+n) + 1
// 每次执行前要对t1[], t2[]清零
void buildSA(int m)
{
    int i, k, p = 0, *x = t1, *y = t2;
    for(i = 0; i < m; ++i) c[i] = 0;
    for(i = 0; i < n; ++i) ++c[x[i]=s[i]];
    for(i = 1; i < m; ++i) c[i] += c[i-1];
    for(i = n-1; i >= 0; --i) sa[--c[x[i]]] = i;
    for(k = 1; p < n; k <<= 1, m = p) {
        for(p = 0, i = n-k; i < n; ++i) y[p++] = i;
        for(i = 0; i < n; ++i) if(sa[i] >= k) y[p++] = sa[i]-k;
        for(i = 0; i < m; ++i) c[i] = 0;
        for(i = 0; i < n; ++i) ++c[x[y[i]]];
        for(i = 1; i < m; ++i) c[i] += c[i-1];
        for(i = n-1; i >= 0; --i) sa[--c[x[y[i]]]] = y[i];
        swap(x, y), p = 1, x[sa[0]] = 0;
        // sa[i]+k会大于n，所以要保证t1[],t2[]足够大
        // 且后方元素均为0
        for(i = 1; i < n; ++i) x[sa[i]] = y[sa[i]]==y[sa[i-1]] &&
            y[sa[i]+k]==y[sa[i-1]+k] ? p-1 : p++;
    }
    for(i = 0; i < n; ++i) srank[sa[i]] = i;
    for(k = 0, i = 0; i < n; ++i) {
        if(k) --k;
        if(!srank[i]) continue;
        p = sa[srank[i]-1];
        while(s[i+k] == s[p+k]) ++k;
        height[srank[i]] = k;
    }
}

int main()
{
    while(scanf("%s", s) == 1) {
        n = strlen(s) + 1;
        buildSA(*max_element(s, s+n) + 1);
        printArr("rank:", srank, n);
        printArr("sa:", sa, n);
        printArr("height:", height, n);
    }
}
