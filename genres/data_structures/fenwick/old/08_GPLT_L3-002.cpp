// https://www.patest.cn/contests/gplt/L3-002
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10;
#define lowbit(x) ((x) & (-(x)))

int top;
int stk[maxn];
int C[maxn];
char buf[1024];

void add(int i, int x)
{
    for(; i < maxn; i += lowbit(i))
        C[i] += x;
}

int kth(int k)
{
    int ans = 0, cnt = 0;

    for(int i = 17; i >= 0; --i) {
        ans |= (1 << i);
        if(ans > maxn || cnt + C[ans] >= k)
            ans &= ~(1 << i);
        else
            cnt += C[ans];
    }
    return ans + 1;
}

int main()
{
    int n, x;

    for(scanf("%d", &n); n > 0; --n) {
        scanf("%s", &buf);
        if(!strcmp(buf, "Pop")) {
            if(top == 0) {
                puts("Invalid");
            } else {
                x = stk[--top];
                add(x, -1);
                printf("%d\n", x);
            }
        } else if(!strcmp(buf, "Push")) {
            scanf("%d", &x);
            stk[top++] = x;
            add(x, 1);
        } else {
            if(top == 0) {
                puts("Invalid");
            } else if(top & 1) {
                printf("%d\n", kth((top + 1) >> 1));
            } else {
                printf("%d\n", kth(top >> 1));
            }
        }
    }
}
