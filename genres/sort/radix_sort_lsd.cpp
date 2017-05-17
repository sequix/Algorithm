// radix sort LSD
#include <bits/stdc++.h>
using namespace std;
const int BASE = 10;
const int N = 10;
const int MIN = 10;
const int MAX = 20;
#define pow2(x) (x)*(x)
#define pow3(x) pow2(x)*(x)
#define pow4(x) pow3(x)*(x)
#define pow5(x) pow4(x)*(x)
#define pow6(x) pow5(x)*(x)
#define pow7(x) pow6(x)*(x)
#define pow8(x) pow7(x)*(x)
#define pow9(x) pow8(x)*(x)

int A[N];

void init()
{
    srand(time(0));
    for(int i = 0; i < N; ++i)
        A[i] = (int)((double)rand() / RAND_MAX * (MAX-MIN+1)) + MIN;
}

void print(int *arr, int n)
{
    for(int i = 0; i < n; ++i)
        printf("%d ", arr[i]);
    putchar(10);
}

int cnt[BASE];
int bucket[N];  // 桶

int getdigit(int x, int d)
{
    static const int pow_base[] = {1, BASE, pow2(BASE), pow3(BASE),
        pow4(BASE), pow5(BASE), pow6(BASE), pow7(BASE), pow8(BASE), 
        pow9(BASE)};
    return x / pow_base[d] % BASE;
}

// 将arr[left...right]排序的从右到左d位排序
void radix_sort(int *arr, int left, int right, int d)
{
    for(int k = 0; k < d; ++k) {
        memset(cnt, 0, sizeof(cnt));

        // 统计每个桶中元素数
        for(int i = left; i <= right; ++i)
            ++cnt[getdigit(arr[i], k)];

        // 统计每个桶的右边界的下一个位置
        for(int i = 1; i < BASE; ++i)
            cnt[i] += cnt[i-1];

        // 入桶，因为cnt表示右边界下一个位置
        // 所以为保证稳定性这里从右向左遍历
        for(int i = right; i >= left; --i) {
            int j = getdigit(arr[i], k);
            bucket[cnt[j]-1] = arr[i];
            --cnt[j];
        }

        // 出桶
        for(int i = left, j = 0; i <= right; ++i, ++j)
            arr[i] = bucket[j];
    }
}

int main()
{
    init();
    print(A, N);
    radix_sort(A, 0, N-1, floor(log(MAX) / log(10)) + 1);
    print(A, N);
}
