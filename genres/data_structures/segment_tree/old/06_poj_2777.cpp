// POJ No.2777 Count Color (线段树+状态压缩) (5088K 375MS)
#include <cstdio>
#include <cctype>
#include <algorithm>
using namespace std;

struct Node {
	int a, b, c;
	bool covered;	// 标记当前区间是否被某种颜色完全覆盖
	Node *left, *right;
	int mid() const { return (a+b)/2; }
} tree[400000];

int L, T, O, Nodecnt = 0;

int bitcnt(int x)
{
	int cnt = 0;
	for(; x != 0; x &= x-1)
		++cnt;
	return cnt;
}

void build(Node *p, int a, int b)
{
	p->a = a, p->b = b;
	p->c = 1, p->covered = false;
	if(a == b) return;
	++Nodecnt; p->left = tree + Nodecnt;
	++Nodecnt; p->right = tree + Nodecnt;
	build(p->left, a, p->mid());
	build(p->right, p->mid()+1, b);
}

void change(Node *p, int a, int b, int c)
{
	if(p->a == a && p->b == b) {
		p->c = 1 << (c-1);
		p->covered = true;
		return;
	}
	if(p->covered) {
		p->left->c = p->c;
		p->right->c = p->c;
		p->covered = false;
		p->left->covered = true;
		p->right->covered = true;
	}
	if(b <= p->mid())
		change(p->left, a, b, c);
	else if(a > p->mid())
		change(p->right, a, b, c);
	else {
		change(p->left, a, p->mid(), c);
		change(p->right, p->mid()+1, b, c);
	}
	p->c = p->left->c | p->right->c;
}

int query(Node *p, int a, int b)
{
	if(p->covered || (p->a == a && p->b == b))
		return p->c;
	if(b <= p->mid())
		return query(p->left, a, b);
	else if(a > p->mid())
		return query(p->right, a, b);
	else
		return query(p->left, a, p->mid()) | query(p->right, p->mid()+1, b);
}

int main()
{
	scanf("%d%d%d", &L, &T, &O);
	build(tree, 1, L);
	while(O--) {
		char cmd;
		int a, b, c;
		while(!isupper(cmd = getchar()));
		if(cmd == 'C') {
			scanf("%d%d%d", &a, &b, &c);
			if(a > b) swap(a, b);
			change(tree, a, b, c);
		} else {
			scanf("%d%d%d", &a, &b);
			if(a > b) swap(a, b);
			printf("%d\n", bitcnt(query(tree, a, b)));
		}
	}
	return 0;
}
