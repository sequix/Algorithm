// 表达式树建立 (操作数以小写字母表示)
#include <bits/stdc++.h>
using namespace std;

struct node {
    union { char var; char op; };
    node *left, *right;
};

int len;
double var[256];
char str[4096]; // 表达式
char pri[128];  // 运算符优先级

void pushOperator(stack<char> &op, stack<node*> &stk)
{
    node *p = new node;
    p->op = op.top(); op.pop();
    p->right = stk.top(); stk.pop();
    p->left = stk.top(); stk.pop();
    stk.push(p);
}

node *build()
{
    stack<char> op;
    stack<node*> stk;

    for(int i = 0; i < len; ++i) {
        if(islower(str[i])) {
            node *p = new node;
            p->var = str[i];
            p->left = p->right = NULL;
            stk.push(p);
        } else if(str[i] == '(') {
            op.push('(');
        } else if(str[i] == ')') {
            while(!op.empty() && op.top() != '(')
                pushOperator(op, stk);
            op.pop();
        } else {
            while(!op.empty() && pri[op.top()] >= pri[str[i]])
                pushOperator(op, stk);
            op.push(str[i]);
        }
    }
    while(!op.empty()) pushOperator(op, stk);
    return stk.top();
}

double calc(node *p)
{
    if(!p->left && !p->right)
        return var[p->var];
    double op1 = calc(p->left);
    double op2 = calc(p->right);
    switch(p->op) {
        case '+': return op1 + op2;
        case '-': return op1 - op2;
        case '*': return op1 * op2;
        case '/': return op1 / op2;
    }
}

int main()
{
    int n;
    char v; double val;
    pri['*'] = pri['/'] = 2;
    pri['+'] = pri['-'] = 1;

    fgets(str, sizeof(str), stdin);
    len = 0;
    for(int i = 0; str[i]; ++i)
        if(!isspace(str[i])) str[len++] = str[i];
    str[len] = 0;
    node *root = build();

    while(scanf("%d", &n) != EOF) {
        for(int i = 0; i < n; ++i) {
            while(isspace(v = getchar()));
            scanf("%lf", &val);
            var[v] = val;
        }
        printf("%g\n", calc(root));
    }
}
