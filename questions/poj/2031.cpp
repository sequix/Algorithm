// POJ No.2031 Building a Space Station (prim) (1240K 204MS)
#include <cmath>
#include <queue>
#include <cstdio>
#include <iostream>
using namespace std;
const int MAX_V = 100;
typedef pair<double, int> P;

int V;
double G[MAX_V+5][MAX_V+5];
double x[MAX_V+5], y[MAX_V+5], z[MAX_V+5], r[MAX_V+5];

double dis(double x1, double y1, double z1, double x2, double y2, double z2)
{
	double dx = x2 - x1, dy = y2 - y1, dz = z2 - z1;
	return sqrt(dx*dx + dy*dy + dz*dz);
}

double prim(int src)
{
	int cnt = 0;
	double sumweight = 0;
	bool used[MAX_V+5] = {0};
	priority_queue<P, vector<P>, greater<P> > que;

	que.push(P(0, src));

	while(cnt < V && !que.empty()) {
		P p = que.top(); que.pop();
		int u = p.second;
		if(used[u]) continue;
		++cnt;
		used[u] = true;
		sumweight += p.first;
		for(int i = 0; i < V; ++i)
			if(i != u) que.push(P(G[u][i], i));
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
