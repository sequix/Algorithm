// POJ No.1190 生日蛋糕 (DFS+剪枝) (720K 32MS)
#include <cmath>
#include <iostream>
using namespace std;

int N, M;
int area;		// 正在构建的蛋糕面积
int minArea;	// 最小面积
int minV[21];	// n层蛋糕的最小体积
int minA[21];	// n层蛋糕的最小面积

int maxVforNRH(int n, int r, int h)
{
	int v = 0;
	for(int i = 0; i < n; ++i)
		v += (r - i) * (r - i) * (h - i);
	return v;
}

// 用n层蛋糕凑体积v，底层半径不超r，高度不超h
void dfs(int v, int n, int r, int h)
{
	if(n == 0) {
		if(v == 0) minArea = min(minArea, area);
		return;
	}
	if(area + minA[n] >= minArea) return;	// 保证最优
	if(n > r || n > h) return;	// 高度和半径无法安置
	if(minV[n] > v) return;		// 体积多了
	if(maxVforNRH(n, r, h) < v) return;	// 体积少了

	for(int rr = r; rr >= n; --rr) {
		if(n == M) area = rr * rr;
		for(int hh = h; hh >= n; --hh) {
			area += 2 * rr * hh;
			dfs(v-rr*rr*hh, n-1, rr-1, hh-1);
			area -= 2 * rr * hh;
		}
	}
}

int main()
{
	cin >> N >> M;

	for(int i = 1; i <= M; ++i) {
		minV[i] = minV[i-1] + i * i * i;
		minA[i] = minA[i-1] + 2 * i * i;
	}
	int maxH = (N - minV[M])/(M*M) + 1;
	int maxR = sqrt(double(N - minV[M])/M) + 1;
	area = 0;
	minArea = 0x3f3f3f3f;
	dfs(N, M, maxR, maxH);
	if(minArea == 0x3f3f3f3f)
		cout << 0 << endl;
	else
		cout << minArea << endl;
	return 0;
}
