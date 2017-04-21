// POJ No.1077 Eight (BFS+排列序数判重) (TLE)
#include <string>
#include <cstdio>
#include <bitset>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int MAX_N = 1000000;

struct Node {
	int status;		// 当前节点对应状态
	int pre;		// 指向父节点
	char premove;	// 父节点到当期节点所需的移动方式
};

Node que[MAX_N];
int qhead = 0, qtail = 0;
void inque(int status, int pre, char premove)
{
	que[qtail].status = status;
	que[qtail].pre = pre;
	que[qtail++].premove = premove;
}
int outque() { return qhead++; }
bool empty() { return qtail - qhead == 0; }

int ans_tail;					// 指向所求路径的尾
char anspath[MAX_N];			// 所求路径的逆序
string orig;					// 初始状态 (新第0个排列)
string dest = "123456780";		// 目标状态，是一个偶排列(0不算在排列中)
bitset<362880> flags;			// flags[i]标记（以orig为第0个的）第i个是否用过
int factorial[11];

char old2new[256];		// 以"012345678"为基准的字符串到以orig的映射表
char new2old[256];		// 上表的反

void init()
{
	factorial[0] = factorial[1] = 1;
	for(int i = 2; i <= 10; ++i)
		factorial[i] = i * factorial[i-1];

	for(int i = 0; i < orig.size(); ++i) {
		old2new[i + '0'] = orig[i];
		new2old[orig[i]] = i + '0';
	}
}

// 计算不包括0在内的str的逆序数
int reversecnt(const string &str)
{
	int cnt = 0;
	for(int i = 1; i < str.size(); ++i) {
		if(str[i] == '0') continue;
		for(int j = 0; j < i; ++j)
			if(str[j] != '0' && str[j] > str[i]) ++cnt;
	}
	return cnt;
}

// 给定字符串返回以orig为基准的排序序号
int str2index(const string &nstr)
{
	int ret = 0;
	bool used[10] = { false };
	string ostr(nstr.size(), ' ');

	for(int i = 0; i < nstr.size(); ++i)
		ostr[i] = new2old[nstr[i]];

	for(int i = 0; i < ostr.size(); ++i) {
		int cnt = 0;
		for(int j = 0; j < ostr[i]-'0'; ++j)
			if(!used[j]) ++cnt;
		ret += cnt * factorial[ostr.size()-i-1];
		used[ostr[i]-'0'] = true;
	}
	return ret;
}

// 给定序号返回以orig为基准的排序字符串
string index2str(int n)
{
	bool used[10] = { false };
	string ret(orig.size(), ' ');

	for(int i = 0; i < ret.size(); ++i) {
		int j;
		for(j = 0; j < 9; ++j) {
			if(!used[j]) {
				if(factorial[ret.size()-i-1] > n) break;
				else n -= factorial[ret.size()-i-1];
			}
		}
		ret[i] = j + '0';
		used[j] = true;
	}
	for(int i = 0; i < ret.size(); ++i)
		ret[i] = old2new[ret[i]];
	return ret;
}

// 根据所给status和移动方式，返回移动后的status，如果无法移动返回-1
int move(int status, char m)
{
	string str = index2str(status);
	int pos = str.find('0');

	switch(m) {
		case 'u':
			if(pos-3 < 0) return -1;
			swap(str[pos-3], str[pos]);
			break;
		case 'd':
			if(pos+3 >= str.size()) return -1;
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

void bfs()
{
	const char moves[] = "udlr";
	const int dest_status = str2index(dest);

	flags[0] = true;
	inque(0, -1, '\0');

	while(!empty()) {
		int p = outque();
		if(que[p].status == dest_status) {
			ans_tail = p;
			return;
		}
		for(int i = 0; i < 4; ++i) {
			int new_status = move(que[p].status, moves[i]);
			if(new_status == -1 || flags[new_status]) continue;
			inque(new_status, p, moves[i]);
			flags[new_status] = true;
		}
	}
} 

int main()
{
	//freopen("input", "r", stdin);

	getline(cin, orig);
	orig = string(orig.begin(), remove(orig.begin(), orig.end(), ' '));
	orig.replace(orig.find('x'), 1, "0");
	//printf("After Input: %s\n", orig.c_str());

	if(reversecnt(orig) % 2 != 0) {
		cout << "unsolvable" << endl;
		return 0;
	}

	init();
	//cout << str2index("234150768") << endl;
	//cout << str2index("234150786") << endl;
	//cout << str2index("234150678") << endl;
	//cout << index2str(1) << endl;
	//cout << index2str(2) << endl;
	//cout << index2str(3) << endl;

	bfs();

	int cnt = 0;
	for(int i = ans_tail; que[i].pre != -1; i = que[i].pre)
		anspath[cnt++] = que[i].premove;

	for(int i = cnt-1; i >= 0; --i)
		putchar(anspath[i]);
	putchar('\n');
	return 0;
}
