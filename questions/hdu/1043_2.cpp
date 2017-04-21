// HDU No.1043 Eight (BFS+变进制hash) (18848K 124MS)
#include <cstdio>
#include <bitset>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAX_N = 3628800;

struct Node {
	char status[32];	// 整个局面
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
int ans_heads[MAX_N];			// 指向所求路径的头
char orig[32];					// 初始状态 (第0个排列)
char dest[] = "123456780";		// 目标状态，是一个偶排列(0不算在排列中)
bitset<MAX_N> flags;			// flags[i]标记（以orig为第0个的）第i个是否用过

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

	for(int i = 0; i < 9; ++i) {
		int cnt = 0;
		for(int k = 0; k < i; ++k)
			if(str[k] > str[i]) ++cnt;
		hashval += cnt * factorial[i+1];
	}
	return hashval;
}

// 根据所给status和移动方式，返回移动后的status，如果无法移动返回-1
bool move(char *str, char m)
{
	int pos = find(str, str+9, '0')-str;

	switch(m) {
		case 'u':
			if(pos-3 < 0) return false;
			swap(str[pos-3], str[pos]);
			break;
		case 'd':
			if(pos+3 >= 9) return false;
			swap(str[pos+3], str[pos]);
			break;
		case 'l':
			if(pos==0 || pos==3 || pos==6) return false;
			swap(str[pos-1], str[pos]);
			break;
		case 'r':
			if(pos==2 || pos==5 || pos==8) return false;
			swap(str[pos+1], str[pos]);
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

	unsigned hashval = myhash(dest);
	flags[hashval] = true;
	ans_heads[hashval] = inque(dest, -1, '\0');

	while(!empty()) {
		int p = outque();
		for(int i = 0; i < 4; ++i) {
			char status[32];
			strcpy(status, que[p].status);
			bool movable = move(status, moves[i]);
			if(!movable) continue;
			hashval = myhash(status);
			if(flags[hashval]) continue;
			ans_heads[hashval] = inque(status, p, reverse_moves[i]);
			flags[hashval] = true;
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

		for(int i = ans_heads[myhash(orig)]; que[i].pre != -1; i = que[i].pre)
			putchar(que[i].move);
		putchar('\n');
	}
	return 0;
}
