// POJ No.1556 The Doors (计算几何+最短路) (884K 16MS)
#include <queue>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const double INF = 1e12;

typedef struct Vector {
	double x, y;
	Vector(double x=0, double y=0): x(x), y(y) {}
	friend Vector operator - (const Vector &v1, const Vector &v2) {
		return Vector(v1.x-v2.x, v1.y-v2.y);
	}
	friend double operator ^ (const Vector &v1, const Vector &v2) {
		return (v1.x * v2.y) - (v1.y * v2.x);
	}
} Point;

struct Edge {
	int from, to;
	double weight;
	Edge(int f=0, int t=0, double w=0): from(f), to(t), weight(w) {}
} edges[10000];

int N;				// 墙数
double wX[20];		// 墙的x坐标，升序
double wY[20][4];	// 第i堵墙的4个y坐标，升序
Point p[100];		// 起点，终点和墙的端点
int pcnt;			// 点的数量
int ecnt;			// 边的数量

double dis(const Point &p1, const Point &p2)
{
	double dx = p2.x - p1.x, dy = p2.y - p1.y;
	return sqrt(dx*dx + dy*dy);
}

// A与B间是否可以连成一条线，而不被其它墙阻隔
bool isok(const Point &A, const Point &B)
{
	int i = 0;
	bool flag = true;
	Vector AB = B - A;
	if(A.x >= B.x) return false;

	while(wX[i] <= A.x && i < N)
		++i;
	while(wX[i] < B.x && i < N && flag) {
		Vector AP1 = Vector(wX[i], 0.0) - A;
		Vector AP2 = Vector(wX[i], wY[i][0]) - A;
		if((AB ^ AP1) * (AB ^ AP2) < 0) { flag = false; break; }

		AP1 = Vector(wX[i], wY[i][1]) - A;
		AP2 = Vector(wX[i], wY[i][2]) - A;
		if((AB ^ AP1) * (AB ^ AP2) < 0) { flag = false; break; }

		AP1 = Vector(wX[i], wY[i][3]) - A;
		AP2 = Vector(wX[i], 10.0) - A;
		if((AB ^ AP1) * (AB ^ AP2) < 0) { flag = false; break; }

		++i;
	}
	return flag;
}

double bellmanford(int beg, int end)
{
	double dis[200];

	for(int i = 0; i < pcnt; ++i)
		dis[i] = INF;
	dis[beg] = 0;

	for(int i = 0; i < pcnt; ++i) {
		bool update = false;
		for(int j = 0; j < ecnt; ++j) {
			Edge &e = edges[j];
			if(dis[e.to] > dis[e.from] + e.weight) {
				dis[e.to] = dis[e.from] + e.weight;
				update = true;
			}
		}
		if(!update) break;
	}
	return dis[end];
}

int main()
{
	while(cin >> N && N != -1) {
		p[0] = Point(0, 5);
		pcnt = 1;
		for(int i = 0; i < N; ++i) {
			cin >> wX[i];
			for(int j = 0; j < 4; ++j) {
				cin >> wY[i][j];
				p[pcnt++] = Point(wX[i], wY[i][j]);
			}
		}
		p[pcnt++] = Point(10, 5);

		ecnt = 0;
		for(int i = 0; i < pcnt; ++i)
			for(int j = i+1; j < pcnt; ++j)
				if(isok(p[i], p[j]))
					edges[ecnt++] = Edge(i, j, dis(p[i], p[j]));
		printf("%.2lf\n", bellmanford(0, pcnt-1));
	}
}
