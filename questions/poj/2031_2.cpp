// POJ No.2031 Building a Space Station (prim+不加堆) (812K 188MS)
#include <cmath>
#include <queue>
#include <cstdio>
#include <iostream>
using namespace std;
const int MAX_V = 100;
const double INF = 1e12;

int V;
double mincost[MAX_V+5];
double G[MAX_V+5][MAX_V+5];
double x[MAX_V+5], y[MAX_V+5], z[MAX_V+5], r[MAX_V+5];

double dis(double x1, double y1, double z1, double x2, double y2, double z2)
{
	double dx = x2 - x1, dy = y2 - y1, dz = z2 - z1;
	return sqrt(dx*dx + dy*dy + dz*dz);
}

double prim(int src)
{
	double sumweight = 0;

	for(int i = 0; i < V; ++i)
		mincost[i] = G[src][i];
	mincost[src] = -1;

	for(int i = 1; i < V; ++i) {
		int v = -1;
		double minc = INF;
		for(int j = 0; j < V; ++j)
			if(mincost[j] != -1 && mincost[j] < minc)
				minc = mincost[j], v = j;
		if(v != -1) {
			sumweight += minc;
			mincost[v] = -1;
			for(int j = 0; j < V; ++j)
				if(mincost[j] != -1 && G[v][j] < mincost[j])
					mincost[j] = G[v][j];
		}
	}
	return sumweight;
}

int main()
{
	while(cin >> V && V != 0) {
		for(int i = 0; i < V; ++i)
			cin >> x[i] >> y[i] >> z[i] >> r[i];
		for(int i = 0; i < V; ++i) {
			for(int j = i+1; j < V; ++j) {
				double d = dis(x[i], y[i], z[i], x[j], y[j], z[j]);
				if(d > r[i] + r[j])
					G[i][j] = G[j][i] = d - r[i] - r[j];
				else
					G[i][j] = G[j][i] = 0;
			}
		}
		printf("%.3f\n", prim(0));
	}
}
