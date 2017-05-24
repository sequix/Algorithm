// 计算中缀表达式值 (假设表达式正确)
#include <bits/stdc++.h>
using namespace std;

int len;
char str[4096]; // 表达式
char pri[128];  // 运算符优先级

void _calc(stack<char> &op, stack<double> &num)
{
    double op2 = num.top(); num.pop();
    double op1 = num.top(); num.pop();
    switch(op.top()) {
        case '+': num.push(op1 + op2); break;
        case '-': num.push(op1 - op2); break;
        case '*': num.push(op1 * op2); break;
        case '/': num.push(op1 / op2); break;
    }
    op.pop();
}

double calc()
{
    char last = 0;
    stack<char> op;
    stack<double> num;

    for(int i = 0; i < len; ++i) {
        if(isdigit(str[i])) {
            num.push(atof(str + i));
            while(isdigit(str[i+1])) ++i;
            if(str[i+1]=='.')
                for(++i; isdigit(str[i+1]); ++i);
            if(str[i+1]=='e' || str[i+1]=='E') {
                ++i;
                if(str[i+1] == '-' || str[i+1]=='+') ++i;
                while(isdigit(str[i+1])) ++i;
            }
        } else if(str[i]=='-' && (last==0 || last=='(')) {
            num.push(0.0);
            op.push('-');
        } else if(str[i]=='+' && (last==0 || last=='(')) {
            continue;
        } else if(str[i] == '(') {
            op.push('(');
        } else if(str[i] == ')') {
            while(!op.empty() && op.top() != '(')
                _calc(op, num);
            op.pop();
        } else {
            while(!op.empty() && pri[op.top()] >= pri[str[i]])
                _calc(op, num);
            op.push(str[i]);
        }
        last = str[i];
    }
    while(!op.empty()) _calc(op, num);
    return num.top();
}

int main()
{
    //pri['^'] = 3; // 由于^是右结合的，这里没有实现
    pri['*'] = pri['/'] = 2;
    pri['+'] = pri['-'] = 1;
    //pri['('] = 10;

    while(fgets(str, sizeof(str), stdin)) {
        len = 0;
        for(int i = 0; str[i]; ++i)
            if(!isspace(str[i])) str[len++] = str[i];
        str[len] = 0;
        printf("%.2f\n", calc());
    }
}
