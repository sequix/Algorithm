#include <bits/stdc++.h>
using namespace std;

int main()
{
    long long n, m, a;
    cin >> n >> m >> a;
    long long row = (m + a - 1) / a;
    long long col = (n + a - 1) / a;
    cout << row * col << endl;
}
