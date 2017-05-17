#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, k, ans = 0;
    cin >> n >> k;
    vector<int> v(n);

    for(int i = 0; i < n; ++i)
        cin >> v[i];
    int lim = v[k-1];
    for(int i = 0; i < n; ++i) {
        if(v[i] >= 1 && v[i] >= lim)
            ++ans;
        else
            break;
    }
    cout << ans << endl;
}
