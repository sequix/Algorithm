// POJ No.2828 Buy Tickets (线段树) (10564K 3766MS)
#include <cstdio>
using namespace std;

struct node {
	int a, b, emptys;	// 表示该区间还有几个空位
	node *left, *right;
	int mid() const { return (a+b)/2; }
};

int nodecnt = 0;
node tree[800000];
int nths[200005], vals[200005], ans[200005];

void build(node *p, int a, int b)
{
	p->a = a, p->b = b;
	p->emptys = b - a + 1;
	if(a == b) return;
	++nodecnt; p->left  = tree + nodecnt;
	++nodecnt; p->right = tree + nodecnt;
	build(p->left, a, p->mid());
	build(p->right, p->mid()+1, b);
}

void update(node *p, int nth, int val)
{
	if(p->a == p->b) {
		ans[p->a] = val;
		p->emptys = 0;
		return;
	}
	if(p->left->emptys >= nth)
		update(p->left, nth, val);
	else
		// 左边已经有p->left->emptys的空位，所以到
		// 到右子树时，第nth个变为第nth-p->left->emptys个
		// 注意这里nth必须从1开始才可行
		update(p->right, nth - p->left->emptys, val);
	p->emptys = p->left->emptys + p->right->emptys;
}

int main()
{
	int n;

	while(scanf("%d", &n) != EOF) {
		nodecnt = 0;
		build(tree, 1, n);
		for(int i = 1; i <= n; ++i)
			scanf("%d%d", &nths[i], &vals[i]);
		for(int i = n; i >= 1; --i)
			update(tree, nths[i]+1, vals[i]);
		printf("%d", ans[1]);
		for(int i = 2; i <= n; ++i)
			printf(" %d", ans[i]);
		putchar('\n');
	}
	return 0;
}
