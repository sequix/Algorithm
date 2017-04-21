// HDU No.1043 Eight (BFS+预处理) (5000K 296MS)
#include <cstdio>
#include <bitset>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAX_N = 400000;

struct Node {
	int status;		// 当前节点对应状态
	int pre;		// 指向父节点
	char move;		// 当前节点到父节点的移动方式
};

Node que[MAX_N];
int qhead = 0, qtail = 0;
int inque(int status, int pre, char move)
{
	que[qtail].status = status;
	que[qtail].pre = pre;
	que[qtail].move = move;
	return qtail++;
}
int outque() { return qhead++; }
bool empty() { return qtail - qhead == 0; }

int factorial[11];
int ans_heads[362880];			// 指向所求路径的头
char orig[32];					// 初始状态 (第0个排列)
char dest[] = "123456780";		// 目标状态，是一个偶排列(0不算在排列中)
bitset<362880> flags;			// flags[i]标记（以orig为第0个的）第i个是否用过

// 计算不包括0在内的str的逆序数
int reversecnt(char *str)
{
	int cnt = 0;
	for(int i = 1; i < 9; ++i) {
		if(str[i] == '0') continue;
		for(int j = 0; j < i; ++j)
			if(str[j] != '0' && str[j] > str[i]) ++cnt;
	}
	return cnt;
}

// 给定字符串返回其为第几个排列
int str2index(char *str)
{
	int ret = 0;
	bool used[10] = { false };

	for(int i = 0; i < 9; ++i) {
		int cnt = 0;
		for(int j = 0; j < str[i]-'0'; ++j)
			if(!used[j]) ++cnt;
		ret += cnt * factorial[9-i-1];
		used[str[i]-'0'] = true;
	}
	return ret;
}

// 给定序号n返回第n个排序字符串
void index2str(int n, char *ret)
{
	bool used[10] = { false };

	for(int i = 0; i < 9; ++i) {
		int j;
		for(j = 0; j <= 8; ++j) {
			if(!used[j]) {
				if(factorial[9-i-1] >= n+1) break;
				else n -= factorial[9-i-1];
			}
		}
		ret[i] = j + '0';
		used[j] = true;
	}
	ret[9] = '\0';
}

// 根据所给status和移动方式，返回移动后的status，如果无法移动返回-1
int move(int status, char m)
{
	char str[32];
	index2str(status, str);
	int pos = find(str, str+9, '0')-str;

	switch(m) {
		case 'u':
			if(pos-3 < 0) return -1;
			swap(str[pos-3], str[pos]);
			break;
		case 'd':
			if(pos+3 >= 9) return -1;
			swap(str[pos+3], str[pos]);
			break;
		case 'l':
			if(pos==0 || pos==3 || pos==6) return -1;
			swap(str[pos-1], str[pos]);
			break;
		case 'r':
			if(pos==2 || pos==5 || pos==8) return -1;
			swap(str[pos+1], str[pos]);
			break;
	}
	return str2index(str);
}

void init()
{
	factorial[0] = factorial[1] = 1;
	for(int i = 2; i <= 10; ++i)
		factorial[i] = i * factorial[i-1];

	const char moves[] = "udlr";
	const char reverse_moves[] = "durl";
	int dest_status = str2index(dest);

	flags[dest_status] = true;
	ans_heads[dest_status] = inque(dest_status, -1, '\0');

	while(!empty()) {
		int p = outque();
		for(int i = 0; i < 4; ++i) {
			int new_status = move(que[p].status, moves[i]);
			if(new_status == -1 || flags[new_status]) continue;
			ans_heads[new_status] = inque(new_status, p, reverse_moves[i]);
			flags[new_status] = true;
		}
	}
} 

int main()
{
	init();
	while(fgets(orig, sizeof(orig), stdin) != NULL) {
		orig[remove(orig, orig+strlen(orig), ' ')-orig] = '\0';
		replace(orig, orig+9, 'x', '0');

		if(reversecnt(orig) % 2 != 0) {
			printf("unsolvable\n");
			continue;
		}

		int status = str2index(orig);
		for(int i = ans_heads[status]; que[i].pre != -1; i = que[i].pre)
			putchar(que[i].move);
		putchar('\n');
	}
	return 0;
}
