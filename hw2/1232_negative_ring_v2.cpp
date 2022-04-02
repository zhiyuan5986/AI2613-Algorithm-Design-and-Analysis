//注意有重边，用known可以避免重边现象。

#include <iostream>
#include <string.h>
using namespace std;
 
const int MAXN = 3001;
const int MAXE = 5001;
 
int map[MAXN][MAXN];
bool known[MAXN][MAXN];
int dis[MAXN];
 
struct e
{
	int s;
	int e;
}e[MAXE];
bool bellman_ford(int start, int end, int n, int m)
{
	memset(dis,10002,sizeof(dis)); //初始化无穷大
	dis[start] = 0;
	for(int i=0; i<n-1; i++) //n-1次松弛
	{
        bool flag = false;
		for(int j=0; j<m; j++)
		{
			if(dis[e[j].s] + map[e[j].s][e[j].e] < dis[e[j].e])
			{
				dis[e[j].e] = dis[e[j].s] + map[e[j].s][e[j].e];
                flag = true;
			}
		}
        if (!flag) break;
	}
	//判断是否能继续松弛
	for(int i=0; i<m; i++)
	{
		if(dis[e[i].s] + map[e[i].s][e[i].e] < dis[e[i].e])
		{
            return true;
		}
	}
    return false;
}


int main()
{
	memset(known,0,MAXN*MAXN);
    int n, m;
    cin >> n >> m; //node e
    int start, end, weight;
    for (int i=0;i<m;++i) {
        cin >> start >> end >> weight;
		if (!known[start][end] || known[start][end] && map[start][end] > weight) {
			known[start][end]=1;
        	map[start][end]=weight;
        	e[i].s=start;
        	e[i].e=end;
		}
    } 
    bool flag = bellman_ford(1,n,n,m);
    if (flag) cout << "Yes";
    else cout << "No";
    return 0;
}