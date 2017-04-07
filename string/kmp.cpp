// 预处理O(M) 匹配O(N)
int lenp, lens, next[MAXN];
char text[MAXN], pattern[MAXN];

void kmpinit(char *p)
{
    next[0] = -1;
    int i = 0, j = -1;

    while(i < lenp) {
        if(j == -1 || p[i] == p[j]) {
            next[++i] = ++j;
            // 优化连续重复字符的情况的写法
            //++i, ++j;
            //if(p[i] == p[j])
            //    next[i] = next[j];
            //else
            //    next[i] = j;
        } else {
            j = next[j];
        }
    }
}

// 输出所有p在s中出现的下标
void kmp(char *s, char *p)
{
    int i = 0, j = 0;
    if(lenp > lens) return;

    while(i < lens) {
        if(j == -1 || s[i] == p[j]) {
            ++i, ++j;
            if(j == lenp) {
                printf("%d ", i - lenp);
                j = next[lenp];
            }
        } else {
            j = next[j];
        }
    }
    putchar('\n');
}
