#include <bits/stdc++.h>
using namespace std;
const int maxn = 300;

char str[maxn], ans[maxn];

int main()
{
    char *p = ans;
    scanf("%s", str);
    for(int i = 0; str[i]; ++i) {
        if(strchr("aoyeui", tolower(str[i])))
            continue;
        else
            *p++ = '.', *p++ = tolower(str[i]);
    }
    *p = 0;
    puts(ans);
}
