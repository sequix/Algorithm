// 中缀转后缀 (假设表达式正确)
#include <bits/stdc++.h>
using namespace std;

int len;
char str[4096]; // 表达式
char pri[128];  // 运算符优先级

bool isDigit(int i)
{
    if(isdigit(str[i]))
        return 1;
    if((str[i]=='-' || str[i]=='+') && (i==0 || str[i-1]=='('))
        return 1;
    return 0;
}

void mid2suf()
{
    stack<char> op;

    for(int i = 0; i < len; ++i) {
        if(isDigit(i)) {
            printf("%g ", atof(str+i));
            if(str[i] == '-' || str[i] == '+') ++i;
            while(isdigit(str[i+1])) ++i;
            if(str[i+1]=='.') for(++i; isdigit(str[i+1]); ++i);
        } else if(str[i] == '(') {
            op.push('(');
        } else if(str[i] == ')') {
            while(!op.empty() && op.top() != '(')
                printf("%c ", op.top()), op.pop();
            op.pop();
        } else {
            while(!op.empty() && pri[op.top()] >= pri[str[i]])
                printf("%c ", op.top()), op.pop();
            op.push(str[i]);
        }
    }
    while(!op.empty())
        printf("%c ", op.top()), op.pop();
    putchar(10);
}

int main()
{
    pri['*'] = pri['/'] = 2;
    pri['+'] = pri['-'] = 1;

    while(fgets(str, sizeof(str), stdin)) {
        len = 0;
        for(int i = 0; str[i]; ++i)
            if(!isspace(str[i])) str[len++] = str[i];
        str[len] = 0;
        mid2suf();
    }
}
