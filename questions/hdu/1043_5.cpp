// HDU No.1043 Eight (单向BFS打表+map判重及索引+getchar) (608MS 14728K)
#include <map>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
int goalStatus = 123456780;
const int MAX_N = 400000;

struct Node {
	char move;
	int status, pre;
	Node(int s=0, int p=-1, char m=0): status(s), pre(p), move(m) {}
} queue[MAX_N];

map<int, int> myhash;	// 将一个状态映射到queue中的一个下标
int qtail, qhead;

int isMovable(int status, char move)
{
	char buf[64];
	sprintf(buf, "%09d", status);
	int pos = find(buf, buf+9, '0') - buf;

	switch(move) {
		case 'u':
			if(pos <= 2) return -1;
			swap(buf[pos], buf[pos-3]);
			break;
		case 'd':
			if(pos >= 6) return -1;
			swap(buf[pos], buf[pos+3]);
			break;
		case 'l':
			if(pos % 3 == 0) return -1;
			swap(buf[pos], buf[pos-1]);
			break;
		case 'r':
			if(pos % 3 == 2) return -1;
			swap(buf[pos], buf[pos+1]);
			break;
	}
	return atoi(buf);
}

void init()
{
	const char moves[] = "udlr";
	const char rmoves[] = "durl";
	queue[qtail] = Node(goalStatus);
	myhash[goalStatus] = qtail++;

	while(qtail != qhead) {
		Node &p = queue[qhead];
		for(int i = 0; i < 4; ++i) {
			int newStatus = isMovable(p.status, moves[i]);
			if(newStatus == -1) continue;
			if(newStatus==goalStatus || myhash[newStatus]!=0) continue;
			queue[qtail] = Node(newStatus, qhead, rmoves[i]);
			myhash[newStatus] = qtail++;
		}
		++qhead;
	}
}

int reverseCnt(char *str)
{
	int ret = 0;
	for(int i = 0; str[i] != '\0'; ++i) {
		if(str[i] == '0') continue;
		for(int j = 0; j < i; ++j)
			if(str[j] != '0' && str[j] > str[i])
				++ret;
	}
	return ret;
}

bool getNext(char *buf)
{
	char c;
	int cnt = 0;
	while((c = getchar()) != EOF && c != '\n') {
		if('0' <= c&&c <= '9')
			buf[cnt++] = c;
		else if(c == 'x')
			buf[cnt++] = '0';
	}
	buf[cnt] = '\0';
	return c != EOF;
}

int main()
{
	char buf[64];

	init();
	while(getNext(buf)) {
		if(reverseCnt(buf) % 2 != 0) {
			puts("unsolvable");
			continue;
		}
		for(int i=myhash[atoi(buf)]; queue[i].pre != -1; i = queue[i].pre)
			putchar(queue[i].move);
		putchar('\n');
	}
	return 0;
}
