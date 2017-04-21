// POJ No.2243 Knight Moves (DBFS+根据size交替扩展)
#include <queue>
#include <cstring>
#include <cstdio>
using namespace std;
struct Point { int x, y; };
const char d[8][2]={{-2,1},{-2,-1},{-1,-2},{-1,2},{2,-1},{2,1},{1,-2},{1,2}}; Point s, e;
char ss[3], ee[3];
char color[8][8];
int dis[8][8];

bool in(Point p)
{
	if(p.x<0 || p.y<0 || p.x>7 || p.y>7)
		return false;
	return true;
}

int expand(queue<Point> &que, int col)
{
	Point p = que.front();
	que.pop();
	for(int i=0;i<8;++i) {
		Point t;
		t.x=p.x+d[i][0];
		t.y=p.y+d[i][1];
		if(in(t)) {
			if(color[t.x][t.y]==0) {
				dis[t.x][t.y]=dis[p.x][p.y]+1;
				color[t.x][t.y]=col;
				que.push(t);
			} else if(color[t.x][t.y]!=col) {
				return dis[p.x][p.y]+dis[t.x][t.y];
			}
		}
	}
	return -1;
}

int bfs()
{
	int ret;
	queue<Point> qf, qb;

	memset(dis, 0, sizeof(dis));
	memset(color, 0, sizeof(color));
	qf.push(s);
	qb.push(e);
	dis[s.x][s.y] = 0;
	dis[e.x][e.y] = 1;
	color[s.x][s.y] = 1;
	color[e.x][e.y] = 2;

	while(!qf.empty() && !qb.empty()) {
		if(qf.size() <= qb.size()) {
			if((ret = expand(qf, 1)) != -1) return ret;
		} else {
			if((ret = expand(qb, 2)) != -1) return ret;
		}
	}

	if(!qf.empty())
		while((ret = expand(qf, 1)) == -1) ;
	else
		while((ret = expand(qb, 2)) == -1) ;
	return ret;
}

int main()
{ 
	while(scanf("%s %s",ss,ee)==2)
	{
		s.x=ss[0]-'a';
		s.y=ss[1]-'1';
		e.x=ee[0]-'a';
		e.y=ee[1]-'1';
		if(s.x==e.x&&s.y==e.y)
			printf("To get from %s to %s takes 0 knight moves.\n",ss,ee);
		else
			printf("To get from %s to %s takes %d knight moves.\n",ss,ee,bfs());
	}
	return 0;
}
