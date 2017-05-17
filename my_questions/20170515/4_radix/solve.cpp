#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, m;

    while(~scanf("%d%d", &n, &m)) {
        int x, sum = 0;
        for(int i = 0; i < m; ++i) {
            scanf("%d", &x);
            sum += x;
        }
        printf("%d\n", sum % (n-1) == 0);
    }
}
