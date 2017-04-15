// POJ No.3276 Face The Right (396K 329MS)
// 给01序列，对长度为k的连续序列取反，直至整个序列为1
// 求取反次数最少时的k值
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 5e3 + 10;

int n;
char f[maxn];       // f[i] i位置的牛是否需要被反向
char dir[maxn];     // dir[i] i位置牛的朝向F:1, B:0

bool isok(int k, int &cnt)
{
    int sum = 0;    // 包括当前位置的区间中被反向的区间的数量
    memset(f, 0, maxn);

    for(int i = 0; i+k <= n; ++i) {
// 当sum为奇数时，表示当前位置的牛为已经被反过向
//      若此时dir[i] == 0时，即实际其为1，不需要反向
//      若此时dir[i] == 1时，即实际其为0，需要反向
// 当sum为偶数时，表示当前位置的牛没有被反过向
//      若此时dir[i] == 0时，即实际也为0，需要反向
//      若此时dir[i] == 1时，即实际也为1，不需要反向
//  综上dir[i] + sum为偶数时，当前位置需要反向
        f[i] = ((dir[i] + sum) % 2 == 0);
        sum += f[i];
        cnt += f[i];
        if(i-k+1 >= 0) sum -= f[i-k+1];
    }

    for(int i = n-k+1; i < n; ++i) {
        if((dir[i] + sum) % 2 == 0) return 0;
        if(i-k+1 >= 0) sum -= f[i-k+1];
    }
    return 1;
}

int main()
{
    scanf("%d", &n);
    for(int i = 0; i < n; ++i) {
        while(isspace(dir[i] = getchar()));
        dir[i] = (dir[i] == 'F');
    }

    int m, K = n, M = n;
    for(int k = 1; k <= n; ++k) {
        m = 0;
        if(isok(k, m) && m < M)
            M = m, K = k;
    }
    printf("%d %d\n", K, M);
}
