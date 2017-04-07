// Longest Increasing Subsequence O(nlogn) 
#include <bits/stdc++.h>
using namespace std;

string str;
vector<int> m;  // m[i] 长度为i的LIS的最后一个元素在str中的下标
vector<int> p;  // p[i] LIS中str[i]前驱

int main()
{
    while(cin >> str) {
        m.clear();
        p.clear();

        m.resize(str.size() + 1);
        p.resize(str.size());

        int len = 0;    // 当前LIS长度
        for(int i = 0; i < str.size(); ++i) {
            int left = 1;
            int right = len;

            while(left <= right) {
                int mid = (left + right + 1) >> 1;
                if(str[m[mid]] < str[i])
                    left = mid + 1;
                else
                    right = mid - 1;
            }

            int new_len = left;

            p[i] = m[new_len-1];
            m[new_len] = i;

            if(new_len > len)
                len = new_len;
        }

        string lis(len, 0);        
        int k = m[len];
        for(int i = len-1; i >= 0; --i) {
            lis[i] = str[k];
            k = p[k];
        }

        cout << lis.size() << ": " << lis << endl;
    }
}
