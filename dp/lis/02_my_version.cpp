// Longest Increasing Subsequence O(nlogn) 
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10;

int n;
int A[maxn];    // 原串
int m[maxn];    // m[i] 长度为i的LIS的末个元素在A中的下标，从1开始
int p[maxn];    // p[i] LIS中A[i]前驱
int L[maxn];    // LIS

int main()
{
    while(cin >> n) {
        for(int i = 0; i < n; ++i)
            cin >> A[i];
        
        // 求LIS
        int len = 0;
        for(int i = 0; i < n; ++i) {
            // 这里的二分答案会落在[left, right]
            int left = 1, right = len+1;
            while(left < right) {
                int mid = (left + right) >> 1;
                if(A[m[mid]] < A[i]) left = mid + 1;
                else right = mid;
            }
            m[left] = i;    // left == new_len
            p[i] = m[left-1];
            if(left > len) len = left;
        }
        // 重构LIS
        int k = m[len];
        for(int i = len-1; i >= 0; --i) {
            L[i] = A[k];
            k = p[k];
        }

        for(int i = 0; i < len; ++i)
            printf("%d ", L[i]);
        putchar(10);
    }
}
