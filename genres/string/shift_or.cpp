// Bitap (shift-or, shift-and) algorithm
#include <bits/stdc++.h>
using namespace std;

int b[128];

// shift_or use 0 represents valid bit.
void shift_or(const string &t, const string &p)
{
    int shift = 1;
    memset(b, ~0, sizeof(b));
    for(int i = 0; i < p.size(); ++i) {
        b[p[i]] &= ~shift;
        shift <<= 1;
    }

    int d = ~0;
    int mask = ~(1 << (p.size() - 1));
    for(int i = 0; i < t.size(); ++i) {
        d = (d << 1) | b[t[i]];
        if(~(d | mask)) printf("%d ", i - p.size() + 1);
    }
    putchar(10);
}

int main()
{
    string text, pattern;
    while(cin >> text >> pattern)
        shift_or(text, pattern);
}
