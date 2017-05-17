// HDU No.2185 Milking Grid (KMP) (1216K 485MS)
// 找最小子矩阵，其可拼成大矩阵，求其面积
// 求面积即求长宽，即矩阵的行数和列数
// 对于列数可以求最小每行的重复子串数来获得
// 而对于行数，考虑到大矩阵拼成了小矩阵，即小矩阵循环出现
// 而求最小的矩阵，就可以对应求最小循环节
// 将每一行当成一个字符，所有行当成一个字符串，求next数组
// 长即为r - next[r]
#include <cstdio>
#include <cstring>
using namespace std;
const int maxr = 1e4 + 10;
const int maxc = 80;

int r, c;
int cnt[maxr];      // cnt[i] 长度为i的子串在多少行内出现
int next[maxr];
char buf[maxc];
char m[maxr][maxc];

int main()
{
    int i, j, x, y, w, h;
    scanf("%d%d", &r, &c);
    for(int i = 0; i < r; ++i) scanf("%s", m[i]);

    // 求最小子矩阵列数w，即最小重复子串
    for(i = 0; i < r; ++i) {
        strcpy(buf, m[i]);
        for(j = c; j >= 1; --j) {
            buf[j] = 0;
            for(x=0, y=0; m[i][y]; ++y, ++x) {
                if(!buf[x]) x = 0;
                if(m[i][y] != buf[x]) break;
            }
            if(!m[i][y]) ++cnt[j];
        }
    }
    for(int i = 1; i <= c; ++i)
        if(cnt[i] == r) { w = i; break; }

    // 求行数h，即以行为单位的循环节长度
    for(i = 0; i < r; ++i)  // 不要忘记将多余列去掉
        m[i][w] = 0;
    next[0] = -1;
    i = 0, j = -1;

    while(i < r) {
        if(j == -1 || !strcmp(m[i], m[j]))
            next[++i] = ++j;
        else
            j = next[j];
    }
    h = r - next[r];
    printf("%d\n", w * h);
}
