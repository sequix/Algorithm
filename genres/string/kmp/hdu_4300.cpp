// HDU No.4300 Clairewd’s message (exkmp) (78MS 2544K)
// 给字母对应表，表示"第i个字母写为table[i]"，和一串密文+明文的串
// 且密文完整，但明文不一定完整。要最小的密文+完整明文串
// 将S全部当密文，用c2a解密得P，发现S的后缀为P的前缀
// 为求最小的串，需求S[i...n-1]与P[0...n-1]最长公共前缀，即exkmp
// 其实将两个串连在一起求朴素kmp的next，即最长公共前后缀亦可
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10;

int len;
char a2c[27];   // alpha to cryptographic letter
char c2a[27];   // cryptographic letter to alpha
char S[maxn], P[maxn];
int knext[maxn], ex[maxn];

void getnext()
{
    int i, j, p = 1;
    knext[0] = len;
    for(i = 0; P[i]==P[i+1] && i+1<len; ++i);
    knext[1] = i;

    for(i = 2; i < len; ++i) {
        if(i + knext[i-p] < p + knext[p]) {
            knext[i] = knext[i-p];
        } else {
            j = p + knext[p] - i;
            if(j < 0) j = 0;
            while(i+j<len && P[j]==P[i+j]) ++j;
            knext[i] = j, p = i;
        }
    }
}

void exkmp()
{
    int i, j, p = 0;
    getnext();
    for(i = 0; S[i]==P[i] && i<len; ++i);
    ex[0] = i;

    for(i = 1; i < len; ++i) {
        if(i + knext[i-p] < p + ex[p]) {
            ex[i] = knext[i-p];
        } else {
            j = p + ex[p] - i;
            if(j < 0) j = 0;
            while(j<len && P[j]==S[i+j]) ++j;
            ex[i] = j, p = i;
        }
    }
}

int main()
{
    int T;

    for(scanf("%d", &T); T; --T) {
        scanf("%s%s", &a2c, &S);
        len = strlen(S);

        for(int i = 0; i < 26; ++i)
            c2a[a2c[i]-'a'] = i + 'a';
        for(int i = 0; i < len; ++i)
            P[i] = c2a[S[i]-'a'];
        P[len] = 0;
        
        exkmp();
        int infoLen = len;
        for(int i = 0; i < len; ++i)
            //if(i + ex[i] >= len)  // 保证使用整个提供的字符串
            //if(i >= ex[i])    // 保证密文长度 >= 明文长度
            if(i + ex[i] >= len && i >= ex[i])
                { infoLen = i; break; }
        for(int i = 0; i < infoLen; ++i)
            putchar(S[i]);
        for(int i = 0; i < infoLen; ++i)
            putchar(c2a[S[i]-'a']);
        putchar(10);
    }
}
