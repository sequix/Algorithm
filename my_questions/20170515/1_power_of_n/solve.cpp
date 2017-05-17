#include <bits/stdc++.h>
using namespace std;

int main()
{
    int T;
    long long A, B;

    for(scanf("%d", &T); T; --T) {
        scanf("%lld%lld", &A, &B);
        if(B == 0) { printf("%d\n", A == 0); continue; }
        if(A == 1 || A == 0) { printf("%lld\n", A); continue; }
        double r = (log(A) / log(B)) - floor(log(A) / log(B));
        printf("%d\n", r == 0.0);
    }
}
