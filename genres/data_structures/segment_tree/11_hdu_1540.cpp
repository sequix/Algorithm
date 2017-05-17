// HDU No.1540 & POJ No.2892 (set模拟) (436ms 1928kB)
#include <set>
#include <stack>
#include <cstdio>
using namespace std;

int n, m;
set<int> zs;
stack<int> stk;

int main()
{
    int p; char c[2];

    while(scanf("%d%d", &n, &m) != EOF) {
        zs.clear();
        zs.insert(0); zs.insert(n+1);

        for(int i = 0; i < m; ++i) {
            scanf("%s", c);
            if(c[0] == 'D') {
                scanf("%d", &p);
                zs.insert(p);
                stk.push(p);
            } else if(c[0] == 'Q') {
                scanf("%d", &p);
                set<int>::iterator r = zs.lower_bound(p);
                if(*r == p) {
                    puts("0");
                } else {
                    set<int>::iterator l = r;
                    --l;
                    printf("%d\n", *r - *l - 1);
                }
            } else if(!stk.empty()) {
                p = stk.top();
                stk.pop();
                zs.erase(p);
            }
        }
    }
}
