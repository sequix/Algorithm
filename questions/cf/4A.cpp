#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    bool isok = 0;

    cin >> n;
    for(int i = 2; i < n; i += 2)
        if((n - i) % 2 == 0) { isok = 1; break; }
    cout << (isok ? "YES" : "NO") << endl;
}
