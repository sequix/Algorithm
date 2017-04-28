// SGU No.106 The Equation
// 求ax + by + c = 0满足 x1<=x<=x2, y1<=y<=y2的根的个数。
// 通过根的通解来确定x，和y所属的集合，求两个集合的交集即为答案
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

LL exgcd(LL a, LL b, LL &x, LL &y)
{
    if(b == 0) { x = 1, y = 0; return a; }
    LL d = exgcd(b, a%b, y, x);
    y -= a / b * x;
    return d;
}

int main()
{
    LL lx, rx, ly, ry, lt, rt;
    LL a, b, c, x1, x2, y1, y2, x, y, dx, dy;

    cin >> a >> b >> c >> x1 >> x2 >> y1 >> y2;
    c = -c;

    LL d = exgcd(a, b, x, y);
    if(c % d != 0) { cout << "0" << endl;; return 0; }

    x *= c / d, y *= c / d;
    dx = b / d, dy = - a / d;

    if(dx < 0) { 
        lx = ceil((double)(x2 - x) / dx);
        rx = floor((double)(x1 - x) / dx);
    } else {
        lx = ceil((double)(x1 - x) / dx);
        rx = floor((double)(x2 - x) / dx);
    }
    if(dy < 0) { 
        ly = ceil((double)(y2 - y) / dy);
        ry = floor((double)(y1 - y) / dy);
    } else {
        ly = ceil((double)(y1 - y) / dy);
        ry = floor((double)(y2 - y) / dy);
    }
    lt = max(lx, ly), rt = min(rx, ry);

    if(rx < ly || ry < lx || rt < lt) {
        cout << "0" << endl;
    } else {
        cout << rt - lt + 1 << endl;
    }
}
