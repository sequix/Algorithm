// HDU No.1043 Eight (BFS+变进制hash+去除多余的复制+空间优化) (6424K 93MS)
#include <cstdio>
#include <bitset>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAX_N = 362880;

struct Node {
	char status[10];	// 整个局面
	int pre;			// 指向父节点
	char move;			// 当前节点到父节点的移动方式
};

Node que[MAX_N];
int qhead = 0, qtail = 0;
int inque(const char *status, int pre, char move)
{
	strcpy(que[qtail].status, status);
	que[qtail].pre = pre;
	que[qtail].move = move;
	return qtail++;
}
int outque() { return qhead++; }
bool empty() { return qtail - qhead == 0; }

int factorial[11];
int ans_heads[MAX_N];		// 指向所求路径的头
bitset<MAX_N> flags;		// flags[i]标记（以str为第0个的）第i个是否用过
char *cur_status = "123456780";
char next_status[10];

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

// 计算变进制myhash值
unsigned myhash(const char *str)
{
	unsigned hashval = 0;

	for(int i = 1; i < 9; ++i) {
		int cnt = 0;
		for(int k = 0; k < i; ++k)
			if(str[k] > str[i]) ++cnt;
		hashval += cnt * factorial[i];
	}
	return hashval;
}

bool movable(char m)
{
	int pos = find(cur_status, cur_status+9, '0')-cur_status;

	switch(m) {
		case 'u':
			if(pos-3 < 0) return false;
			strcpy(next_status, cur_status);
			swap(next_status[pos-3], next_status[pos]);
			break;
		case 'd':
			if(pos+3 >= 9) return false;
			strcpy(next_status, cur_status);
			swap(next_status[pos+3], next_status[pos]);
			break;
		case 'l':
			if(pos==0 || pos==3 || pos==6) return false;
			strcpy(next_status, cur_status);
			swap(next_status[pos-1], next_status[pos]);
			break;
		case 'r':
			if(pos==2 || pos==5 || pos==8) return false;
			strcpy(next_status, cur_status);
			swap(next_status[pos+1], next_status[pos]);
			break;
	}
	return true;
}

void init()
{
	factorial[0] = factorial[1] = 1;
	for(int i = 2; i <= 10; ++i)
		factorial[i] = i * factorial[i-1];

	const char moves[] = "udlr";
	const char reverse_moves[] = "durl";

	unsigned hashval = myhash(cur_status);
	flags[hashval] = true;
	ans_heads[hashval] = inque(cur_status, -1, '\0');

	while(!empty()) {
		int p = outque();
		cur_status = que[p].status;
		for(int i = 0; i < 4; ++i) {
			if(!movable(moves[i])) continue;
			hashval = myhash(next_status);
			if(flags[hashval]) continue;
			ans_heads[hashval] = inque(next_status, p, reverse_moves[i]);
			flags[hashval] = true;
		}
	}
} 

int main()
{
	init();
	char str[32];
	while(fgets(str, sizeof(str), stdin) != NULL) {
		str[remove(str, str+strlen(str), ' ')-str] = '\0';
		str[remove(str, str+strlen(str), '\n')-str] = '\0';
		replace(str, str+9, 'x', '0');

		if(reversecnt(str) % 2 != 0) {
			printf("unsolvable\n");
			continue;
		}

		for(int i = ans_heads[myhash(str)]; que[i].pre != -1; i = que[i].pre)
			putchar(que[i].move);
		putchar('\n');
	}
	return 0;
}
